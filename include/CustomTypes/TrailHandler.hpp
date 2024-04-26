#pragma once

#include "CustomTypes/TrailComponent.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

#include "Trail/TrailData.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, TrailHandler, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD_PRIVATE(int, trailId);
                      DECLARE_INSTANCE_FIELD_PRIVATE(Sombrero::FastColor, trailColor);
                      DECLARE_INSTANCE_FIELD_PRIVATE(Sombrero::FastColor, multiplierColor);
                      DECLARE_INSTANCE_FIELD_PRIVATE(int, length);
                      DECLARE_INSTANCE_FIELD_PRIVATE(int, colorType);
                      DECLARE_INSTANCE_FIELD_PRIVATE(float, whiteStep);

                      DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Transform*, topTransform);
                      DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Transform*, botTransform);
                      DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Transform*, customBotTransform);

                      DECLARE_INSTANCE_FIELD_PRIVATE(Qosmetics::Sabers::TrailComponent*, trail);
                      DECLARE_INSTANCE_METHOD(void, InitData);
                      DECLARE_INSTANCE_METHOD(void, InitTrail);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      void InitTransforms(UnityEngine::Transform* topTransform, UnityEngine::Transform* botTransform);
                      void SetColor(const Sombrero::FastColor& leftColor, const Sombrero::FastColor& rightColor) const;
                      void SetTrailActive(bool active) const;

                      __declspec(property(get = get_TrailID)) int TrailID;
                      int get_TrailID() const;

                      __declspec(property(get = get_TopTransform)) UnityEngine::Transform * TopTransform;
                      __declspec(property(get = get_BotTransform)) UnityEngine::Transform * BotTransform;
                      __declspec(property(get = get_CustomBotTransform)) UnityEngine::Transform * CustomBotTransform;

                      UnityEngine::Transform * get_TopTransform();
                      UnityEngine::Transform * get_BotTransform();
                      UnityEngine::Transform * get_CustomBotTransform();

)
