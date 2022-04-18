#include "UI/SettingsViewController.hpp"
#include "config.hpp"
#include "diglett/shared/Localization.hpp"
#include "diglett/shared/Util.hpp"
#include "qosmetics-core/shared/ConfigRegister.hpp"
#include "qosmetics-core/shared/Utils/UIUtils.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "sombrero/shared/FastColor.hpp"
#include "sombrero/shared/FastVector2.hpp"

#include "UnityEngine/RectTransform.hpp"

DEFINE_TYPE(Qosmetics::Sabers, SettingsViewController);

using namespace QuestUI::BeatSaberUI;

namespace QuestUI::BeatSaberUI
{
    HMUI::SimpleTextDropdown* CreateDropdownInternal(UnityEngine::Transform* parent, StringW dropdownName, int selectedIndex, List<StringW>* values, std::function<void(HMUI::SimpleTextDropdown*, int)> onValueChange);
}

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

    void SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        auto& globalConfig = Config::get_config();
        if (firstActivation)
        {
            auto localization = Diglett::Localization::get_instance();
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
            TOGGLE(enableMenuPointer, "QosmeticsWhackers:Settings:EnableMenuPointer");

            SLIDER(menuPointerSize, "QosmeticsWhackers:Settings:MenuPointerSize", 0.05f, globalConfig.trailWidth, 0.05f, 2.0f, 0.2f);

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
        }
        else if (justChangedProfile)
        {
            justChangedProfile = false;
            saberLengthSlider->set_value(globalConfig.saberLength);
            saberWidthSlider->set_value(globalConfig.saberWidth);
            enableMenuPointerToggle->set_isOn(globalConfig.enableMenuPointer);
            menuPointerSizeSlider->set_value(globalConfig.menuPointerSize);
            overrideTrailLengthToggle->set_isOn(globalConfig.overrideTrailLength);
            trailLengthSlider->set_value(globalConfig.trailLength);
            whiteTrailToggle->set_isOn(globalConfig.whiteTrail);
            overrideWhiteStepToggle->set_isOn(globalConfig.overrideWhiteStep);
            whiteStepSlider->set_value(globalConfig.whiteStep);
            overrideTrailWidthToggle->set_isOn(globalConfig.overrideTrailWidth);
            trailWidthSlider->set_value(globalConfig.trailWidth);
            trailTypeDropdown->set_selectedIndex((int)globalConfig.trailType);
        }
    }

    void SettingsViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
    {
    }
}