#pragma once

#include "TrailHandler.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Sabers, WhackerHandler, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(ArrayW<TrailHandler*>, trailHandlers);

)