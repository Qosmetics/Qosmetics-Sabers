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

#define TOGGLE(name, key)                                                              \
    name##Toggle = CreateToggle(containerT, localization->get(key), globalConfig.name, \
                                [&](auto v)                                            \
                                {                                                      \
                                    Config::get_config().name = v;                     \
                                    Qosmetics::Core::Config::SaveConfig();             \
                                    previewViewController->UpdatePreview(false);       \
                                });                                                    \
    AddHoverHint(name##Toggle, localization->get(key "HoverHint"))

#define SLIDER(name, key, ...)                                                                             \
    name##Slider = CreateSliderSetting(containerT, localization->get(key), __VA_ARGS__, globalConfig.name, \
                                       [&](auto v)                                                         \
                                       {                                                                   \
                                           Config::get_config().name = v;                                  \
                                           Qosmetics::Core::Config::SaveConfig();                          \
                                           previewViewController->UpdatePreview(false);                    \
                                       });                                                                 \
    name##Slider->FormatString = [](auto v) -> std::string { return std::to_string(v).substr(0, 4); };     \
    AddHoverHint(name##Slider, localization->get(key "HoverHint"))

const char* localizationKeys[] = {
    "QosmeticsWhackers:Settings:TrailType:CUSTOM",
    "QosmeticsWhackers:Settings:TrailType:BASEGAME",
    "QosmeticsWhackers:Settings:TrailType:NONE"};

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
        {
            BSML::parse_and_construct(IncludedAssets::SettingsView_bsml, get_transform(), this);
            /*
            auto localization = Diglett::Localization::get_instance();
            if (Qosmetics::Core::DateUtils::isMonth(6))
            {
                Qosmetics::Core::UIUtils::AddHeader(get_transform(), Qosmetics::Core::RainbowUtils::gayify(static_cast<std::string>(localization->get("QosmeticsWhackers:Settings:Settings"))), Sombrero::FastColor::red());
            }
            else
                Qosmetics::Core::UIUtils::AddHeader(get_transform(), localization->get("QosmeticsWhackers:Settings:Settings"), Sombrero::FastColor::red());

            auto container = CreateScrollableSettingsContainer(this);

            auto externalComponents = container->GetComponent<QuestUI::ExternalComponents*>();
            auto scrollTransform = externalComponents->Get<UnityEngine::RectTransform*>();
            scrollTransform->set_sizeDelta(Sombrero::FastVector2::zero());

            auto containerT = container->get_transform();
            auto wText = CreateText(containerT, localization->get("QosmeticsWhackers:Settings:WhackerSpecificSettings"));
            wText->set_alignment(TMPro::TextAlignmentOptions::Center);
            SLIDER(saberLength, "QosmeticsWhackers:Settings:SaberLength", 0.05f, globalConfig.saberLength, 0.05f, 2.0f, 0.2f);
            SLIDER(saberWidth, "QosmeticsWhackers:Settings:SaberWidth", 0.05f, globalConfig.saberWidth, 0.05f, 2.0f, 0.2f);
            CreateText(containerT, localization->get("QosmeticsWhackers:Settings:RemovedMenuPointers"));

            auto tText = CreateText(containerT, localization->get("QosmeticsWhackers:Settings:TrailSpecificSettings"));
            tText->set_alignment(TMPro::TextAlignmentOptions::Center);
            TOGGLE(overrideTrailLength, "QosmeticsWhackers:Settings:OverrideTrailLength");
            SLIDER(trailLength, "QosmeticsWhackers:Settings:TrailLength", 1.0f, globalConfig.trailLength, 0.0f, 50.0f, 0.2f);
            trailLengthSlider->FormatString = [](auto v) -> std::string
            { return std::to_string((int)v); };

            TOGGLE(whiteTrail, "QosmeticsWhackers:Settings:WhiteTrail");
            TOGGLE(overrideWhiteStep, "QosmeticsWhackers:Settings:OverrideWhiteStep");
            SLIDER(whiteStep, "QosmeticsWhackers:Settings:WhiteStep", 0.05f, globalConfig.whiteStep, 0.0f, 1.0f, 0.2f);
            TOGGLE(overrideTrailWidth, "QosmeticsWhackers:Settings:OverrideTrailWidth");
            SLIDER(trailWidth, "QosmeticsWhackers:Settings:TrailWidth", 0.05f, globalConfig.trailWidth, 0.0f, 1.0f, 0.2f);

            auto list = List<StringW>::New_ctor();
            list->Add(localization->get(localizationKeys[0]));
            list->Add(localization->get(localizationKeys[1]));
            list->Add(localization->get(localizationKeys[2]));

            trailTypeDropdown = CreateDropdownInternal(containerT, localization->get("QosmeticsWhackers:Settings:TrailType"), globalConfig.trailType, list, [&](auto _, int index)
                                                       {
                Config::get_config().trailType = (Config::TrailType)index;
                Qosmetics::Core::Config::SaveConfig();
                previewViewController->UpdatePreview(false); });

            AddHoverHint(trailTypeDropdown, localization->get("QosmeticsWhackers:Settings:TrailTypeHoverHint"));
            */
        }
        else if (justChangedProfile)
        {
            justChangedProfile = false;

            auto settings = GetComponentsInChildren<BSML::BaseSetting*>(true);

            for (auto setting : settings)
            {
                il2cpp_utils::RunMethod(setting, "ReceiveValue");
            }
        }
    }

    bool SettingsViewController::get_gay()
    {
        return Qosmetics::Core::DateUtils::isMonth(6);
    }

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

    float SettingsViewController::get_trailLength() { return Config::get_config().trailLength; }
    void SettingsViewController::set_trailLength(float value)
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