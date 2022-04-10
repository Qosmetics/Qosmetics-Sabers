#pragma once

#include "CustomTypes/WhackerHandler.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, WhackerParent, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(ArrayW<WhackerHandler*>, handlers);
                      DECLARE_INSTANCE_FIELD(ArrayW<GlobalNamespace::Saber*>, sabers);
                      DECLARE_INSTANCE_FIELD(GlobalNamespace::SaberModelController*, saberModelController);

                      DECLARE_INSTANCE_METHOD(void, Awake);

)