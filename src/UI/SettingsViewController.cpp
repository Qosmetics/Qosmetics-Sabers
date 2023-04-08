#include "UI/SettingsViewController.hpp"
#include "assets.hpp"
#include "config.hpp"
#include "qosmetics-core/shared/ConfigRegister.hpp"
#include "qosmetics-core/shared/Utils/DateUtils.hpp"
#include "qosmetics-core/shared/Utils/RainbowUtils.hpp"
#include "qosmetics-core/shared/Utils/UIUtils.hpp"
#include "sombrero/shared/FastColor.hpp"
#include "sombrero/shared/FastVector2.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/Settings/BaseSetting.hpp"

DEFINE_TYPE(Qosmetics::Sabers, SettingsViewController);

namespace Qosmetics::Sabers
{
    bool SettingsViewController::justChangedProfile = false;

    void SettingsViewController::Inject(PreviewViewController* previewViewController)
    {
        this->previewViewController = previewViewController;
    }

    void SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
            BSML::parse_and_construct(IncludedAssets::SettingsView_bsml, get_transform(), this);
        else if (justChangedProfile)
        {
            justChangedProfile = false;

            auto settings = GetComponentsInChildren<BSML::BaseSetting*>(true);

            for (auto setting : settings)
                il2cpp_utils::RunMethod(setting, "ReceiveValue");
        }
    }

    StringW SettingsViewController::get_gaydient() { return Qosmetics::Core::RainbowUtils::randomGradient(); }
    bool SettingsViewController::get_gay() { return Qosmetics::Core::DateUtils::isMonth(6); }

    float SettingsViewController::get_saberLength() { return Config::get_config().saberLength; }
    void SettingsViewController::set_saberLength(float value)
    {
        Config::get_config().saberLength = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    float SettingsViewController::get_saberWidth() { return Config::get_config().saberWidth; }
    void SettingsViewController::set_saberWidth(float value)
    {
        Config::get_config().saberWidth = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    bool SettingsViewController::get_overrideTrailLength() { return Config::get_config().overrideTrailLength; }
    void SettingsViewController::set_overrideTrailLength(bool value)
    {
        Config::get_config().overrideTrailLength = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    int SettingsViewController::get_trailLength() { return Config::get_config().trailLength; }
    void SettingsViewController::set_trailLength(int value)
    {
        Config::get_config().trailLength = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    bool SettingsViewController::get_whiteTrail() { return Config::get_config().whiteTrail; }
    void SettingsViewController::set_whiteTrail(bool value)
    {
        Config::get_config().whiteTrail = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    bool SettingsViewController::get_overrideWhiteStep() { return Config::get_config().overrideWhiteStep; }
    void SettingsViewController::set_overrideWhiteStep(bool value)
    {
        Config::get_config().overrideWhiteStep = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    float SettingsViewController::get_whiteStep() { return Config::get_config().whiteStep; }
    void SettingsViewController::set_whiteStep(float value)
    {
        Config::get_config().whiteStep = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    bool SettingsViewController::get_overrideTrailWidth() { return Config::get_config().overrideTrailWidth; }
    void SettingsViewController::set_overrideTrailWidth(bool value)
    {
        Config::get_config().overrideTrailWidth = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    float SettingsViewController::get_trailWidth() { return Config::get_config().trailWidth; }
    void SettingsViewController::set_trailWidth(float value)
    {
        Config::get_config().trailWidth = value;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

    StringW SettingsViewController::get_trailType()
    {
        switch (Config::get_config().trailType)
        {
        case Config::BASEGAME:
            return "Base Game";
        case Config::CUSTOM:
            return "Custom";
        default:
        case Config::NONE:
            return "None";
        }
    }
    void SettingsViewController::set_trailType(StringW value)
    {
        if (value == "Base Game")
            Config::get_config().trailType = Config::BASEGAME;
        else if (value == "None")
            Config::get_config().trailType = Config::NONE;
        else
            Config::get_config().trailType = Config::CUSTOM;
        Qosmetics::Core::Config::SaveConfig();
        previewViewController->UpdatePreview(false);
    }

}