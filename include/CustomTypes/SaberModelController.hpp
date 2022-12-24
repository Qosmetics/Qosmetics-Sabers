#pragma once

#include "CustomTypes/SaberModelContainer.hpp"
#include "CustomTypes/WhackerHandler.hpp"
#include "GlobalNamespace/ColorManager.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "UnityEngine/Transform.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "lapiz/shared/sabers/SaberModelProvider.hpp"

#include "private_field.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, SaberModelController, GlobalNamespace::SaberModelController,
                      DECLARE_INSTANCE_PRIVATE_FIELD(GlobalNamespace::ColorManager*, _colorManager);
                      DECLARE_INSTANCE_PRIVATE_FIELD(SaberModelContainer*, _saberModelContainer);
                      DECLARE_INSTANCE_PRIVATE_FIELD(GlobalNamespace::GameplayCoreSceneSetupData*, _gameplayCoreSceneSetupData);
                      DECLARE_INSTANCE_PRIVATE_FIELD(Lapiz::Sabers::SaberModelProvider*, _modelProvider);
                      DECLARE_INSTANCE_PRIVATE_FIELD(::Zenject::DiContainer*, _container);
                      DECLARE_INSTANCE_PRIVATE_FIELD(GlobalNamespace::Saber*, saber);

                      DECLARE_INJECT_METHOD(void, Inject, GlobalNamespace::ColorManager* colorManager, SaberModelContainer* saberModelContainer, Lapiz::Sabers::SaberModelProvider* modelProvider, ::Zenject::DiContainer* container, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetupData);
                      DECLARE_INSTANCE_METHOD(void, InitOverride, UnityEngine::Transform* parent, GlobalNamespace::Saber* saber);
                      DECLARE_INSTANCE_METHOD(void, InitFromClone, GlobalNamespace::Saber* saber);
                      DECLARE_INSTANCE_METHOD(void, EditDefaultSaber);
                      DECLARE_INSTANCE_METHOD(void, HideDefaultSaberElements);
                      DECLARE_INSTANCE_METHOD(void, CreateDefaultTrailCopy, UnityEngine::Transform* parent, WhackerHandler* handler);
                      DECLARE_SIMPLE_DTOR();

)