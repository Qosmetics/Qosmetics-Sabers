#pragma once

#include "HMUI/ViewController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/GameObject.hpp"
#include "custom-types/shared/macros.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, PreviewViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, title);
                      DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, loadingIndicator);
                      DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, currentPrefab);
                      DECLARE_INSTANCE_METHOD(void, SetTitleText, StringW text);

                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::ViewController::DidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);

                      public
                      :

                      static bool justChangedProfile;

                      void ShowLoading(bool isLoading = true);
                      void UpdatePreview(bool reinstantiate = false);
                      void InstantiatePrefab();
                      void ClearPrefab();

)
