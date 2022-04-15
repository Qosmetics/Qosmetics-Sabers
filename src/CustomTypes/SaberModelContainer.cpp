#include "CustomTypes/SaberModelContainer.hpp"
#include "config.hpp"
#include "logging.hpp"
#include "qosmetics-core/shared/Utils/BundleUtils.hpp"
#include "qosmetics-core/shared/Utils/FileUtils.hpp"
#include "qosmetics-core/shared/Utils/ZipUtils.hpp"
#include "static-defines.hpp"

#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/TextAsset.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/Text.hpp"

#include "ConstStrings.hpp"

#include "CustomTypes/TrailHandler.hpp"
#include "CustomTypes/TrailTransform.hpp"
#include "CustomTypes/WhackerColorHandler.hpp"
#include "CustomTypes/WhackerHandler.hpp"
#include "Trail/TrailPoint.hpp"

#include "MaterialUtils.hpp"
#include "QsaberConversion.hpp"

DEFINE_TYPE(Qosmetics::Sabers, SaberModelContainer);

std::string JsonValueToString(const rapidjson::Value& val)
{
    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    val.Accept(writer);

    return std::string(buffer.GetString(), buffer.GetLength());
}

void SetLayerRecursively(UnityEngine::Transform* obj, int layer)
{
    obj->get_gameObject()->set_layer(layer);
    int childCount = obj->get_childCount();
    for (int i = 0; i < childCount; i++)
        SetLayerRecursively(obj->GetChild(i), layer);
}

void LegacyTrailFixups(UnityEngine::GameObject* loadedObject, const std::vector<Qosmetics::Sabers::QsaberConversion::LegacyTrail>& leftTrailConfigs, const std::vector<Qosmetics::Sabers::QsaberConversion::LegacyTrail>& rightTrailConfigs)
{
    using namespace Qosmetics::Sabers;
    auto t = loadedObject->get_transform();
    auto leftSaber = t->Find("LeftSaber");
    auto rightSaber = t->Find("RightSaber");

    int trailId = 0;
    for (const auto& trail : leftTrailConfigs)
    {
        auto trailT = leftSaber->Find(trail.name);
        auto top = trailT->Find("TrailEnd");
        auto bot = trailT->Find("TrailStart");

        TrailData trailData(trailId, trail);
        TrailPoint topPoint(trailId, true);
        TrailPoint bottomPoint(trailId, false);
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();

        auto trailText = trailT->get_gameObject()->AddComponent<UnityEngine::UI::Text*>();
        trailText->set_text(JsonValueToString(trailData.ToJson(allocator)));
        auto topText = top->get_gameObject()->AddComponent<UnityEngine::UI::Text*>();
        topText->set_text(JsonValueToString(topPoint.ToJson(allocator)));
        auto botText = bot->get_gameObject()->AddComponent<UnityEngine::UI::Text*>();
        botText->set_text(JsonValueToString(bottomPoint.ToJson(allocator)));

        trailId++;
    }

    for (const auto& trail : rightTrailConfigs)
    {
        auto trailT = rightSaber->Find(trail.name);
        auto top = trailT->Find("TrailEnd");
        auto bot = trailT->Find("TrailStart");

        TrailData trailData(trailId, trail);
        TrailPoint topPoint(trailId, true);
        TrailPoint bottomPoint(trailId, false);
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();

        auto trailText = trailT->get_gameObject()->AddComponent<UnityEngine::UI::Text*>();
        trailText->set_text(JsonValueToString(trailData.ToJson(allocator)));
        auto topText = top->get_gameObject()->AddComponent<UnityEngine::UI::Text*>();
        topText->set_text(JsonValueToString(topPoint.ToJson(allocator)));
        auto botText = bot->get_gameObject()->AddComponent<UnityEngine::UI::Text*>();
        botText->set_text(JsonValueToString(bottomPoint.ToJson(allocator)));

        trailId++;
    }
}

void LegacyFixups(UnityEngine::GameObject* loadedObject)
{
    // TODO: do this
}

void AddHandlers(UnityEngine::GameObject* loadedObject)
{
    auto t = loadedObject->get_transform();
    auto leftSaber = t->Find(ConstStrings::LeftSaber());
    auto rightSaber = t->Find(ConstStrings::LeftSaber());

    leftSaber->get_gameObject()->AddComponent<Qosmetics::Sabers::WhackerHandler*>();
    leftSaber->get_gameObject()->AddComponent<Qosmetics::Sabers::WhackerColorHandler*>();
    rightSaber->get_gameObject()->AddComponent<Qosmetics::Sabers::WhackerHandler*>();
    rightSaber->get_gameObject()->AddComponent<Qosmetics::Sabers::WhackerColorHandler*>();

    auto textObjects = loadedObject->GetComponentsInChildren<UnityEngine::UI::Text*>(true);
    for (auto obj : textObjects)
    {
        auto nameView = static_cast<std::u16string_view>(obj->get_text());
        DEBUG("Got trail text object: {}", obj->get_text());
        /// this assumes it's gonna be json, is this the format we want
        if (nameView.find(u"\"trailId\":") != std::u16string::npos)
        {
            if (nameView.find(u"\"isTop\":") != std::u16string::npos)
                obj->get_gameObject()->AddComponent<Qosmetics::Sabers::TrailTransform*>();
            else
            {
                obj->get_gameObject()->AddComponent<Qosmetics::Sabers::TrailHandler*>();
                obj->get_gameObject()->AddComponent<Qosmetics::Sabers::TrailComponent*>();
            }
        }
    }
    // TODO: do this
}
namespace Qosmetics::Sabers
{
    SaberModelContainer* SaberModelContainer::instance = nullptr;
    SaberModelContainer* SaberModelContainer::get_instance()
    {
        if (instance)
            return instance;
        auto go = UnityEngine::GameObject::New_ctor(StringW(___TypeRegistration::get()->name()));
        UnityEngine::Object::DontDestroyOnLoad(go);
        return go->AddComponent<SaberModelContainer*>();
    }

    void SaberModelContainer::ctor()
    {
        DEBUG("Created SaberModelContainer instance: {}", fmt::ptr(this));
        instance = this;
        bundle = nullptr;
        isLoading = false;
        currentSaberObject = nullptr;
        currentManifest = Qosmetics::Core::Manifest<Qosmetics::Sabers::SaberObjectConfig>();
    }

    void SaberModelContainer::Start()
    {
        auto lastUsedWhacker = Qosmetics::Sabers::Config::get_config().lastUsedWhacker;
        if (lastUsedWhacker == "" || lastUsedWhacker == "Default")
            return;

        std::string filePath = fmt::format("{}/{}.whacker", whacker_path, lastUsedWhacker);
        if (!fileexists(filePath))
            return;
        currentManifest = Qosmetics::Core::Manifest<SaberObjectConfig>(filePath);
        currentManifest.get_descriptor();
        INFO("Loading Saber Object {}", currentManifest.get_descriptor().get_name());
        StartCoroutine(custom_types::Helpers::CoroutineHelper::New(LoadBundleRoutine(nullptr)));
    }

    bool SaberModelContainer::LoadObject(const Qosmetics::Core::Manifest<Qosmetics::Sabers::SaberObjectConfig>& manifest, std::function<void(SaberModelContainer*)> onFinished)
    {
        if (isLoading)
            return false;
        if (manifest.get_filePath() == currentManifest.get_filePath())
            return false;
        currentManifest = manifest;
        StartCoroutine(custom_types::Helpers::CoroutineHelper::New(LoadBundleRoutine(onFinished)));
        return true;
    }

    bool SaberModelContainer::LoadObject(const Qosmetics::Core::Descriptor& descriptor, std::function<void(SaberModelContainer*)> onFinished)
    {
        if (isLoading)
            return false;
        if (descriptor.get_filePath() == currentManifest.get_filePath())
            return false;
        INFO("Loading Saber Object {}", descriptor.get_name());
        currentManifest = Qosmetics::Core::Manifest<SaberObjectConfig>(descriptor.get_filePath());
        StartCoroutine(custom_types::Helpers::CoroutineHelper::New(LoadBundleRoutine(onFinished)));
        return true;
    }

    const SaberObjectConfig& SaberModelContainer::GetSaberConfig()
    {
        return currentManifest.get_config();
    }

    const Qosmetics::Core::Descriptor& SaberModelContainer::GetDescriptor()
    {
        return currentManifest.get_descriptor();
    }

    custom_types::Helpers::Coroutine SaberModelContainer::LoadBundleRoutine(std::function<void(SaberModelContainer*)> onFinished)
    {
        isLoading = true;
        if (currentSaberObject)
            Object::DestroyImmediate(currentSaberObject);
        if (bundle)
            bundle->Unload(true);

        DEBUG("Loading file {} from whacker {}", currentManifest.get_fileName(), currentManifest.get_filePath());
        co_yield custom_types::Helpers::CoroutineHelper::New(Qosmetics::Core::BundleUtils::LoadBundleFromZipAsync(currentManifest.get_filePath(), currentManifest.get_fileName(), bundle));

        bool isLegacy = currentManifest.get_config().get_isLegacy();
        DEBUG("Loading {}Whacker", isLegacy ? "legacy " : "");
        co_yield custom_types::Helpers::CoroutineHelper::New(Qosmetics::Core::BundleUtils::LoadAssetFromBundleAsync<UnityEngine::GameObject*>(bundle, isLegacy ? "_CustomSaber" : "_Whacker", currentSaberObject));

        if (!currentSaberObject)
            ERROR("Failed to load whacker from bundle!");
        auto name = currentSaberObject->get_name();
        currentSaberObject = UnityEngine::Object::Instantiate(currentSaberObject, get_transform());
        // TODO: find correct layer
        SetLayerRecursively(currentSaberObject->get_transform(), 8);
        currentSaberObject->set_name(name);
        currentSaberObject->SetActive(false);

        // Prewarm all shaders
        MaterialUtils::PrewarmAllShadersOnObject(currentSaberObject);

        /// TODO: check, Do we need to preload shaders here?
        if (isLegacy)
        {
            DEBUG("Executing legacy object fixups");
            LegacyFixups(currentSaberObject);

            if (currentManifest.get_config().get_hasTrail())
            {
                DEBUG("Object used to have trails, going to load config for that");
                UnityEngine::TextAsset* configText = nullptr;
                co_yield custom_types::Helpers::CoroutineHelper::New(Qosmetics::Core::BundleUtils::LoadAssetFromBundleAsync<UnityEngine::TextAsset*>(bundle, "config", configText));
                if (configText)
                {
                    DEBUG("Got config text, parsing and fixing up trails");
                    rapidjson::Document doc;
                    doc.Parse(static_cast<std::string>(configText->get_text()));
                    Qosmetics::Sabers::QsaberConversion::LegacyConfig config(doc);
                    LegacyTrailFixups(currentSaberObject, config.leftTrails, config.rightTrails);
                }
            }
        }

        DEBUG("Adding handlers to object");
        AddHandlers(currentSaberObject);

        isLoading = false;
        if (onFinished)
            onFinished(this);

        co_return;
    }

    bool SaberModelContainer::Default()
    {
        if (isLoading)
            return false;
        if (currentSaberObject)
        {
            Object::DestroyImmediate(currentSaberObject);
            currentSaberObject = nullptr;
        }
        if (bundle)
        {
            bundle->Unload(true);
            bundle = nullptr;
        }

        currentManifest = decltype(currentManifest)();
        return true;
    }

    void SaberModelContainer::OnDestroy()
    {
        instance = nullptr;
        UnloadBundle();
    }

    void SaberModelContainer::UnloadBundle()
    {
        if (bundle)
            bundle->Unload(false);
        bundle = nullptr;
    }

    void SaberModelContainer::OnGameRestart()
    {
        if (currentSaberObject)
        {
            Object::DestroyImmediate(currentSaberObject);
            currentSaberObject = nullptr;
        }
        if (bundle)
        {
            bundle->Unload(true);
            bundle = nullptr;
        }

        instance = nullptr;
        UnityEngine::Object::DestroyImmediate(this->get_gameObject());
    }
}