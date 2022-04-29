#pragma once

#include "UnityEngine/Material.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"
#include "sombrero/shared/FastColor.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, WhackerColorHandler, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(Sombrero::FastColor, lastThisColor);
                      DECLARE_INSTANCE_FIELD(Sombrero::FastColor, lastThatColor);
                      DECLARE_INSTANCE_FIELD(ArrayW<UnityEngine::Material*>, customColorMaterials);

                      DECLARE_INSTANCE_METHOD(void, Awake);
                      DECLARE_INSTANCE_METHOD(void, FetchCCMaterials);
                      DECLARE_SIMPLE_DTOR();
                      
                      public
                      :

                      void SetColor(const Sombrero::FastColor& thisColor, const Sombrero::FastColor& thatColor);

)