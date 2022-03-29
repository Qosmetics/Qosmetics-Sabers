#pragma once
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "qosmetics-core/shared/RedecorationRegister.hpp"

REDECORATION_REGISTRATION(saberModelControllerPrefab, 10, true, GlobalNamespace::SaberModelController*, GlobalNamespace::SaberModelContainer*)
{
    // TODO: implement replacing a model
    return saberModelControllerPrefab;
}