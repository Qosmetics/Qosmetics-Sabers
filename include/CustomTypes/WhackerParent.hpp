#pragma once

#include "CustomTypes/WhackerHandler.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, WhackerParent, UnityEngine::MonoBehaviour,

                      DECLARE_INSTANCE_FIELD(bool, defaultSaber);
                      DECLARE_INSTANCE_FIELD(WhackerHandler*, whackerHandler);
                      DECLARE_INSTANCE_FIELD(GlobalNamespace::SaberModelController*, saberModelController);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      void set_defaultSaber(bool value);
                      void Awake();
                      void OnDestroy();
                      void ColorizeSpecific(int saberType, const Sombrero::FastColor& saberTypeColor);
                      static void Colorize(int saberType, GlobalNamespace::SaberModelController* saberModelController, const Sombrero::FastColor& saberTypeColor);

)