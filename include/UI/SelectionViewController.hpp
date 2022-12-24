#pragma once

#include "HMUI/ViewController.hpp"
#include "UI/PreviewViewController.hpp"
#include "custom-types/shared/macros.hpp"

#include "bsml/shared/BSML/Components/CustomListTableData.hpp"
#include "qosmetics-core/shared/UI/Components/DeletionConfirmationModal.hpp"
#include "qosmetics-core/shared/UI/Components/QosmeticObjectTableCell.hpp"
#include "qosmetics-core/shared/UI/Components/QosmeticObjectTableData.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

#include "private_field.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, SelectionViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_PRIVATE_FIELD(SaberModelContainer*, saberModelContainer);
                      DECLARE_INSTANCE_PRIVATE_FIELD(PreviewViewController*, previewViewController);
                      DECLARE_INSTANCE_PRIVATE_FIELD(BSML::CustomListTableData*, descriptorListTableData);
                      DECLARE_INSTANCE_PRIVATE_FIELD(Qosmetics::Core::QosmeticObjectTableData*, descriptorList);
                      DECLARE_INSTANCE_PRIVATE_FIELD(Qosmetics::Core::DeletionConfirmationModal*, deletionConfirmationModal);

                      DECLARE_INJECT_METHOD(void, Inject, PreviewViewController* previewViewController, SaberModelContainer* saberModelContainer);
                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
                      DECLARE_INSTANCE_METHOD(void, Refresh);
                      DECLARE_INSTANCE_METHOD(void, PostParse);
                      DECLARE_INSTANCE_METHOD(void, Default);
                      DECLARE_INSTANCE_METHOD(int, GetSelectedCellIdx);

                      public
                      :

                      void OnDeleteCell(Qosmetics::Core::QosmeticObjectTableCell* cell);
                      void OnSelectDescriptor(Qosmetics::Core::QosmeticObjectTableCell* cell);
                      void ReloadDescriptorList();
                      void OnObjectLoadFinished();
                      void RefreshAfterSaberConversion();

)