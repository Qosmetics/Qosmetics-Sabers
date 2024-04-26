#pragma once

#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/SaberType.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

#include "CustomTypes/TrailHandler.hpp"
#include "CustomTypes/TrailTransform.hpp"
#include "CustomTypes/WhackerColorHandler.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, WhackerHandler, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD_PRIVATE(WhackerColorHandler*, colorHandler);
                      DECLARE_INSTANCE_FIELD_PRIVATE(ArrayW<TrailHandler*>, trailHandlers);
                      DECLARE_INSTANCE_FIELD_PRIVATE(ArrayW<TrailTransform*>, trailTransforms);
                      DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::SaberModelController*, saberModelController);
                      DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::SaberType, saberType);

                      DECLARE_INSTANCE_METHOD(void, GetTrailHandlers);
                      DECLARE_INSTANCE_METHOD(void, SetupTrails);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      __declspec(property(get = get_TrailHandlers, put = set_TrailHandlers)) ArrayW<TrailHandler*>
                          TrailHandlers;
                      void set_TrailHandlers(ArrayW<TrailHandler*> trailHandlers);
                      ArrayW<TrailHandler*> get_TrailHandlers() const;

                      __declspec(property(get = get_TrailTransforms, put = set_TrailTransforms)) ArrayW<TrailTransform*> TrailTransforms;
                      void set_TrailTransforms(ArrayW<TrailTransform*> trailTransforms);
                      ArrayW<TrailTransform*> get_TrailTransforms() const;

                      __declspec(property(get = get_ColorHandler, put = set_ColorHandler)) WhackerColorHandler * ColorHandler;
                      void set_ColorHandler(WhackerColorHandler* colorHandler);
                      WhackerColorHandler * get_ColorHandler() const;

                      __declspec(property(get = get_SaberType, put = set_SaberType)) GlobalNamespace::SaberType SaberType;
                      void set_SaberType(GlobalNamespace::SaberType saberType);
                      GlobalNamespace::SaberType get_SaberType() const;

                      void SetColor(const Sombrero::FastColor& thisColor, const Sombrero::FastColor& thatColor);
                      void SetSize(float width, float length);

)
