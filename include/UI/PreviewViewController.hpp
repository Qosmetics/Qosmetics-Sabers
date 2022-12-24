#pragma once

#include "CustomTypes/SaberModelContainer.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/ViewController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/GameObject.hpp"

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

#include "private_field.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, PreviewViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_PRIVATE_FIELD(SaberModelContainer*, saberModelContainer);
                      DECLARE_INSTANCE_PRIVATE_FIELD(GlobalNamespace::PlayerDataModel*, playerDataModel);
                      DECLARE_INSTANCE_PRIVATE_FIELD(TMPro::TextMeshProUGUI*, title);
                      DECLARE_INSTANCE_PRIVATE_FIELD(HMUI::ImageView*, loadingIndicator);
                      DECLARE_INSTANCE_PRIVATE_FIELD(UnityEngine::GameObject*, currentPrefab);
                      DECLARE_INSTANCE_METHOD(void, SetTitleText, StringW text);

                      DECLARE_INSTANCE_METHOD(bool, get_gay);
                      DECLARE_INJECT_METHOD(void, Inject, SaberModelContainer* saberModelContainer, GlobalNamespace::PlayerDataModel* playerDataModel);
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
