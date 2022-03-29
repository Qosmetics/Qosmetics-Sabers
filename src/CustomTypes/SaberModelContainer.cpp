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
#include "UnityEngine/Transform.hpp"

DEFINE_TYPE(Qosmetics::Sabers, SaberModelContainer);

void SetLayerRecursively(UnityEngine::Transform* obj, int layer)
{
    obj->get_gameObject()->set_layer(layer);
    int childCount = obj->get_childCount();
    for (int i = 0; i < childCount; i++)
        SetLayerRecursively(obj->GetChild(i), layer);
}

void LegacyFixups(UnityEngine::GameObject* loadedObject)
{
    // TODO: do this
}

void AddHandlers(UnityEngine::GameObject* loadedObject)
{
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

        auto name = currentSaberObject->get_name();
        currentSaberObject = UnityEngine::Object::Instantiate(currentSaberObject, get_transform());
        // TODO: find correct layer
        SetLayerRecursively(currentSaberObject->get_transform(), 8);
        currentSaberObject->set_name(name);
        currentSaberObject->SetActive(false);

        if (isLegacy)
        {
            DEBUG("Executing legacy object fixups");
            LegacyFixups(currentSaberObject);
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