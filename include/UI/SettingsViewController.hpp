#pragma once

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/SimpleTextDropdown.hpp"
#include "HMUI/ViewController.hpp"
#include "UI/PreviewViewController.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "custom-types/shared/macros.hpp"
#include "questui/shared/CustomTypes/Components/Settings/SliderSetting.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, SettingsViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_FIELD(PreviewViewController*, previewViewController);

                      DECLARE_INSTANCE_FIELD(QuestUI::SliderSetting*, saberLengthSlider);
                      DECLARE_INSTANCE_FIELD(QuestUI::SliderSetting*, saberWidthSlider);
                      DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, overrideTrailLengthToggle);
                      DECLARE_INSTANCE_FIELD(QuestUI::SliderSetting*, trailLengthSlider);
                      DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, whiteTrailToggle);
                      DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, overrideWhiteStepToggle);
                      DECLARE_INSTANCE_FIELD(QuestUI::SliderSetting*, whiteStepSlider);
                      DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, overrideTrailWidthToggle);
                      DECLARE_INSTANCE_FIELD(QuestUI::SliderSetting*, trailWidthSlider);
                      DECLARE_INSTANCE_FIELD(HMUI::SimpleTextDropdown*, trailTypeDropdown);

                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::ViewController::DidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);

                      public
                      :

                      static bool justChangedProfile;

)