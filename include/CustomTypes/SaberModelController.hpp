#pragma once

#include "GlobalNamespace/Saber.hpp"
#include "UnityEngine/Transform.hpp"
#include "qosmetics-core/shared/SaberModelController.hpp"

DECLARE_CLASS_CUSTOM(Qosmetics::Sabers, SaberModelController, Qosmetics::Core::SaberModelController,
                     DECLARE_INSTANCE_FIELD(GlobalNamespace::Saber*, saber);
                     DECLARE_INSTANCE_METHOD(void, Init, GlobalNamespace::Saber* saber);
                     DECLARE_INSTANCE_METHOD(void, EditDefaultSaber);
                     DECLARE_INSTANCE_METHOD(void, HideDefaultSaberElements);

)