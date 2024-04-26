#pragma once

#include "UnityEngine/Material.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"
#include "sombrero/shared/FastColor.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, WhackerColorHandler, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD_PRIVATE(Sombrero::FastColor, lastThisColor);
                      DECLARE_INSTANCE_FIELD_PRIVATE(Sombrero::FastColor, lastThatColor);
                      DECLARE_INSTANCE_FIELD_PRIVATE(ArrayW<UnityEngine::Material*>, customColorMaterials);

                      DECLARE_INSTANCE_METHOD(void, Awake);
                      DECLARE_INSTANCE_METHOD(void, FetchCCMaterials);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      __declspec(property(get = get_LastThisColor)) Sombrero::FastColor LastThisColor;
                      Sombrero::FastColor get_LastThisColor();

                      __declspec(property(get = get_LastThatColor)) Sombrero::FastColor LastThatColor;
                      Sombrero::FastColor get_LastThatColor();

                      void SetColor(const Sombrero::FastColor& thisColor, const Sombrero::FastColor& thatColor);

)
