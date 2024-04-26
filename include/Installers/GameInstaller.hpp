#pragma once

#include "CustomTypes/SaberModelContainer.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "UnityEngine/Transform.hpp"

#include "Zenject/Installer.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, GameInstaller, ::Zenject::Installer,
                      DECLARE_INSTANCE_FIELD_PRIVATE(SaberModelContainer*, _saberModelContainer);
                      DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::GameplayCoreSceneSetupData*, _gameplayCoreSceneSetupData);
                      DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::GameObject*, saberWrapper);

                      DECLARE_OVERRIDE_METHOD_MATCH(void, InstallBindings, &::Zenject::Installer::InstallBindings);
                      DECLARE_CTOR(ctor, SaberModelContainer* saberModelContainer, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetupData);

                      static constexpr const int DECORATION_PRIORITY = 300;

)
