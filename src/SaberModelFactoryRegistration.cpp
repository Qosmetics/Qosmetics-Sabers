#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "qosmetics-core/shared/SaberModelControllerRegister.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"

#include "ConstStrings.hpp"
#include "CustomTypes/SaberModelContainer.hpp"
#include "CustomTypes/SaberModelController.hpp"
#include "config.hpp"

#include "sombrero/shared/FastQuaternion.hpp"
#include "sombrero/shared/FastVector3.hpp"

SABERMODELCONTROLLER_REGISTRATION(QosmeticsSabers, 10, Qosmetics::Sabers::SaberModelController*);