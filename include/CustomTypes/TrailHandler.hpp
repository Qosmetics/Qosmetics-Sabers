#pragma once

#include "CustomTypes/TrailComponent.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

#include "Trail/TrailData.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, TrailHandler, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(int, trailId);
                      DECLARE_INSTANCE_FIELD(Sombrero::FastColor, trailColor);
                      DECLARE_INSTANCE_FIELD(Sombrero::FastColor, multiplierColor);
                      DECLARE_INSTANCE_FIELD(int, length);
                      DECLARE_INSTANCE_FIELD(int, colorType);
                      DECLARE_INSTANCE_FIELD(float, whiteStep);

                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, topTransform);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, botTransform);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, customBotTransform);

                      DECLARE_INSTANCE_FIELD(Qosmetics::Sabers::TrailComponent*, trail);
                      DECLARE_INSTANCE_METHOD(void, InitData);
                      DECLARE_INSTANCE_METHOD(void, InitTrail);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      void SetColor(const Sombrero::FastColor& leftColor, const Sombrero::FastColor& rightColor) const;
                      void SetTrailActive(bool active) const;

                      UnityEngine::Transform * get_topTransform();
                      UnityEngine::Transform * get_botTransform();
                      UnityEngine::Transform * get_customBotTransform();

)