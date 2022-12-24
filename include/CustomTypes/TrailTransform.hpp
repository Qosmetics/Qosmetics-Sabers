#pragma once

#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

#include "private_field.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, TrailTransform, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_PRIVATE_FIELD(int, trailId);
                      DECLARE_INSTANCE_PRIVATE_FIELD(int, isTop);
                      DECLARE_INSTANCE_METHOD(void, Init);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      bool get_isTop();

)