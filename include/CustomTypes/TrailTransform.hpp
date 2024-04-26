#pragma once

#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, TrailTransform, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD_PRIVATE(int, trailId);
                      DECLARE_INSTANCE_FIELD_PRIVATE(int, isTop);
                      DECLARE_INSTANCE_METHOD(void, Init);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      __declspec(property(get = get_TrailID)) int TrailID;
                      int get_TrailID() const;

                      __declspec(property(get = get_IsTop)) bool IsTop;
                      bool get_IsTop() const;

)
