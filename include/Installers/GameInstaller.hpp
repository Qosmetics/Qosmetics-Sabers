#pragma once

#include "CustomTypes/SaberModelContainer.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "UnityEngine/Transform.hpp"

#include "Zenject/Installer.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "private_field.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, GameInstaller, ::Zenject::Installer,
                      DECLARE_INSTANCE_PRIVATE_FIELD(SaberModelContainer*, _saberModelContainer);
                      DECLARE_INSTANCE_PRIVATE_FIELD(GlobalNamespace::GameplayCoreSceneSetupData*, _gameplayCoreSceneSetupData);
                      DECLARE_INSTANCE_PRIVATE_FIELD(UnityEngine::GameObject*, saberWrapper);

                      DECLARE_OVERRIDE_METHOD(void, InstallBindings, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::Installer::InstallBindings>::get());
                      DECLARE_CTOR(ctor, SaberModelContainer* saberModelContainer, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetupData);

                      static constexpr const int DECORATION_PRIORITY = 300;

)