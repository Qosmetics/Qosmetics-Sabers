#include "UI/PreviewViewController.hpp"
#include "CustomTypes/SaberModelContainer.hpp"
#include "assets.hpp"
#include "config.hpp"
#include "logging.hpp"
#include "qosmetics-core/shared/Utils/DateUtils.hpp"
#include "qosmetics-core/shared/Utils/RainbowUtils.hpp"
#include "qosmetics-core/shared/Utils/UIUtils.hpp"
#include "sombrero/shared/FastColor.hpp"
#include "sombrero/shared/FastVector3.hpp"

#include "UnityEngine/UI/LayoutElement.hpp"

#include "HMUI/CurvedCanvasSettingsHelper.hpp"
#include "HMUI/ImageView.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/Backgroundable.hpp"

DEFINE_TYPE(Qosmetics::Sabers, PreviewViewController);

namespace Qosmetics::Sabers
{
    bool PreviewViewController::justChangedProfile = false;

    void PreviewViewController::Inject(SaberModelContainer* saberModelContainer, GlobalNamespace::PlayerDataModel* playerDataModel)
    {
        this->saberModelContainer = saberModelContainer;
        this->playerDataModel = playerDataModel;
    }

    void PreviewViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
    {
        if (currentPrefab)
            currentPrefab->SetActive(false);
    }

    bool PreviewViewController::get_gay()
    {
        return Qosmetics::Core::DateUtils::isMonth(6);
    }

    void PreviewViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            auto parser = BSML::parse_and_construct(IncludedAssets::PreviewView_bsml, get_transform(), this);
            auto params = parser->parserParams.get();
            auto objectBG = params->GetObjectsWithTag("objectBG").at(0)->GetComponent<BSML::Backgroundable*>();
            auto imageView = objectBG->background;
            imageView->skew = 0;
            imageView->set_gradient(true);
            imageView->gradientDirection = 1;
            imageView->set_color(Sombrero::FastColor::white());
            auto color = Sombrero::FastColor::get_black();
            color.a = 0.3f;
            imageView->set_color0(color);
            color.a = 0.7f;
            imageView->set_color1(color);
            imageView->curvedCanvasSettingsHelper->Reset();

            ShowLoading(true);
            UpdatePreview(true);
        }
        else
        {
            if (currentPrefab)
                currentPrefab->SetActive(true);
            DEBUG("Reactivating preview view controller with justChangedProfile: {}", justChangedProfile ? "true" : "false");
            UpdatePreview(justChangedProfile);

            justChangedProfile = false;
        }
    }

    void PreviewViewController::SetTitleText(StringW text)
    {
        if (!(title && title->m_CachedPtr.m_value))
            return;

        if (Qosmetics::Core::DateUtils::isMonth(6))
        {
            text = "<i>" + Qosmetics::Core::RainbowUtils::gayify(static_cast<std::string>(text)) + "</i>";
            title->set_text(text);
        }
        else
            title->set_text(u"<i>" + text + u"</i>");
    }

    void PreviewViewController::ShowLoading(bool isLoading)
    {
        if (!(loadingIndicator && loadingIndicator->m_CachedPtr.m_value))
            return;

        loadingIndicator->get_gameObject()->SetActive(isLoading);
        if (isLoading)
            SetTitleText("Loading...");
    }
    void PreviewViewController::UpdatePreview(bool reinstantiate)
    {
        if (!currentPrefab || reinstantiate)
        {
            DEBUG("Reinstantiating prefab");
            ClearPrefab();
            InstantiatePrefab();
        }

        ShowLoading(false);
        if (!currentPrefab)
        {
            DEBUG("No prefab found, must be default!");
            SetTitleText("Default Whacker (no preview)");
            return;
        }

        DEBUG("Getting variables");
        auto config = saberModelContainer->GetSaberConfig();
        auto& globalConfig = Config::get_config();

        auto& descriptor = saberModelContainer->GetDescriptor();
        auto name = descriptor.get_name();
        SetTitleText(name);

        auto t = currentPrefab->get_transform();
        for (int i = 0; i < t->get_childCount(); i++)
        {
            auto child = t->GetChild(i);

            if (child && !child->get_name().ends_with("Saber"))
                Object::DestroyImmediate(child->get_gameObject());
        }

        auto leftSaber = t->Find("LeftSaber");
        auto rightSaber = t->Find("RightSaber");

        Sombrero::FastVector3 saberSize(globalConfig.saberWidth, globalConfig.saberWidth, globalConfig.saberLength);
        saberSize *= 2;
        leftSaber->set_localPosition({0.0f, .25f, -0.5f});
        rightSaber->set_localPosition({0.0f, -.25f, -0.5f});

        leftSaber->set_localScale(saberSize);
        rightSaber->set_localScale(saberSize);
    }
    void PreviewViewController::InstantiatePrefab()
    {
        if (saberModelContainer->currentSaberObject)
        {
            DEBUG("Found a new saber object, instantiating it! name: {}", saberModelContainer->currentSaberObject->get_name());
            currentPrefab = UnityEngine::Object::Instantiate(saberModelContainer->currentSaberObject, get_transform());
            currentPrefab->SetActive(true);
            auto t = currentPrefab->get_transform();
            auto s = get_transform()->get_lossyScale();
            DEBUG("LossyScale: {}, {}, {}", s.x, s.y, s.z);
            t->set_localScale(Sombrero::FastVector3::one() / 0.03f);
            t->set_localPosition(Sombrero::FastVector3(-30.0f, 2.5f, -85.0f));
            t->set_localEulerAngles(Sombrero::FastVector3(0.0f, -30.0f, 0.0f));
            DEBUG("Instantiated and inited new prefab!");
        }
        else
        {
            ERROR("saberModelContainer->currentSaberObject was null but we tried using it!");
        }
    }

    void PreviewViewController::ClearPrefab()
    {
        DEBUG("Clearing Prefab...");
        if (currentPrefab)
        {
            DEBUG("Prefab existed!");
            UnityEngine::Object::DestroyImmediate(currentPrefab);
        }
        currentPrefab = nullptr;
    }

}