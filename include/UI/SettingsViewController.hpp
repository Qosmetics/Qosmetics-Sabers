#pragma once

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/SimpleTextDropdown.hpp"
#include "HMUI/ViewController.hpp"
#include "UI/PreviewViewController.hpp"
#include "UnityEngine/UI/Toggle.hpp"

#include "beatsaber-hook/shared/utils/typedefs.h"
#include <initializer_list>

#include "bsml/shared/macros.hpp"
#include "custom-types/shared/macros.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

#include "private_field.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, SettingsViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_PRIVATE_FIELD(PreviewViewController*, previewViewController);

                      DECLARE_INJECT_METHOD(void, Inject, PreviewViewController* previewViewController);
                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
                      DECLARE_INSTANCE_METHOD(bool, get_gay);

                      DECLARE_BSML_PROPERTY(float, saberLength);
                      DECLARE_BSML_PROPERTY(float, saberWidth);
                      DECLARE_BSML_PROPERTY(bool, overrideTrailLength);
                      DECLARE_BSML_PROPERTY(float, trailLength);
                      DECLARE_BSML_PROPERTY(bool, whiteTrail);
                      DECLARE_BSML_PROPERTY(bool, overrideWhiteStep);
                      DECLARE_BSML_PROPERTY(float, whiteStep);
                      DECLARE_BSML_PROPERTY(bool, overrideTrailWidth);
                      DECLARE_BSML_PROPERTY(float, trailWidth);
                      DECLARE_BSML_PROPERTY(StringW, trailType);

                      BSML_OPTIONS_LIST_OBJECT(trailTypes, "Custom", "Base Game", "None");
                      public
                      :

                      static bool justChangedProfile;

)