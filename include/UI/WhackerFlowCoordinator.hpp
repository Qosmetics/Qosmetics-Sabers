#pragma once

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "PreviewViewController.hpp"
#include "SelectionViewController.hpp"
#include "SettingsViewController.hpp"

#include "bsml/shared/BSML/Components/TextGradientUpdater.hpp"
#include "qosmetics-core/shared/UI/QosmeticsBaseFlowCoordinator.hpp"

DECLARE_CLASS_CUSTOM(Qosmetics::Sabers, WhackerFlowCoordinator, Qosmetics::Core::QosmeticsBaseFlowCoordinator,
                     DECLARE_INSTANCE_FIELD_PRIVATE(HMUI::ViewController*, settingsViewController);
                     DECLARE_INSTANCE_FIELD_PRIVATE(HMUI::ViewController*, selectionViewController);
                     DECLARE_INSTANCE_FIELD_PRIVATE(HMUI::ViewController*, previewViewController);
                     DECLARE_INSTANCE_FIELD(BSML::TextGradientUpdater*, titleGradientUpdater);

                     DECLARE_INJECT_METHOD(void, Inject, PreviewViewController* previewViewController, SelectionViewController* selectionViewController, SettingsViewController* settingsViewController);

                     DECLARE_INSTANCE_METHOD(void, DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
                     DECLARE_INSTANCE_METHOD(void, Awake);
                     DECLARE_OVERRIDE_METHOD_MATCH(void, BackButtonWasPressed, &HMUI::FlowCoordinator::BackButtonWasPressed, HMUI::ViewController* topViewController);
                     DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::FlowCoordinator::DidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);
                     DECLARE_CTOR(ctor);

)
