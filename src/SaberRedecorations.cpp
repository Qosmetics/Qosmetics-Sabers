#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "qosmetics-core/shared/RedecorationRegister.hpp"

#include "UnityEngine/GameObject.hpp"

#include "CustomTypes/WhackerParent.hpp"

REDECORATION_REGISTRATION(saberModelControllerPrefab, 10, true, GlobalNamespace::SaberModelController*, GlobalNamespace::SaberModelContainer*)
{
    // TODO: implement replacing a model
    saberModelControllerPrefab->get_gameObject()->AddComponent<Qosmetics::Sabers::WhackerParent*>();
    return saberModelControllerPrefab;
}