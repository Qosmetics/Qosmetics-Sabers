#pragma once

#include "CustomTypes/WhackerHandler.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, WhackerParent, UnityEngine::MonoBehaviour,

                      DECLARE_INSTANCE_FIELD_PRIVATE(bool, defaultSaber);
                      DECLARE_INSTANCE_FIELD_PRIVATE(class WhackerHandler*, whackerHandler);
                      DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::SaberModelController*, saberModelController);
                      DECLARE_INSTANCE_METHOD(void, Awake);
                      DECLARE_INSTANCE_METHOD(void, OnDestroy);
                      DECLARE_SIMPLE_DTOR();

                      public
                      :

                      __declspec(property(get = get_WhackerHandler, put = set_WhackerHandler)) class WhackerHandler * WhackerHandler;
                      class WhackerHandler * get_WhackerHandler() const;
                      void set_WhackerHandler(class WhackerHandler* whackerHandler);

                      __declspec(property(put = set_DefaultSaber)) bool DefaultSaber;
                      void set_DefaultSaber(bool value);

                      void ColorizeSpecific(int saberType, const Sombrero::FastColor& saberTypeColor);
                      static void Colorize(int saberType, GlobalNamespace::SaberModelController* saberModelController, const Sombrero::FastColor& saberTypeColor);

)
