#include "API.hpp"
#include "ConstStrings.hpp"
#include "Disabling.hpp"
#include "conditional-dependencies/shared/main.hpp"
#include "config.hpp"
#include "qosmetics-core/shared/Data/Descriptor.hpp"
#include "static-defines.hpp"
#include <fmt/core.h>

#include "CustomTypes/SaberModelContainer.hpp"
#include "CustomTypes/TrailHandler.hpp"
#include "CustomTypes/WhackerColorHandler.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

#define SABERMODELCONTAINER Qosmetics::Sabers::SaberModelContainer::get_instance()
#define GET_SABERMODELCONTAINER() auto saberModelContainer = SABERMODELCONTAINER
#define VISIBLE_API(name, retVal, ...)                                                   \
    retVal name(__VA_ARGS__);                                                            \
    extern "C" __attribute__((visibility("default"))) ::CondDeps::CondDepsRet __##name() \
    {                                                                                    \
        return ::CondDeps::CondDepConverter<decltype(&name)>::get(&name);                \
    }                                                                                    \
    retVal name(__VA_ARGS__)

VISIBLE_API(GetActiveDescriptor, Qosmetics::Core::Descriptor)
{
    return SABERMODELCONTAINER->GetDescriptor();
}

VISIBLE_API(GetConfig, Qosmetics::Sabers::SabersConfig*)
{
    return reinterpret_cast<Qosmetics::Sabers::SabersConfig*>(&Qosmetics::Sabers::Config::get_config());
}

VISIBLE_API(SetDefault, void)
{
    SABERMODELCONTAINER->Default();
}

VISIBLE_API(SetActiveFromFilePath, bool, std::string filePath)
{
    if (!fileexists(filePath))
        return false;
    auto manifest = Qosmetics::Sabers::SaberModelContainer::Manifest(filePath);
    return Qosmetics::Sabers::SaberModelContainer::get_instance()->LoadObject(manifest, nullptr);
}

VISIBLE_API(SetActive, bool, std::string fileName)
{
    std::string filePath = fmt::format("{}/{}", whacker_path, fileName);
    if (!fileexists(filePath))
        return false;
    auto manifest = Qosmetics::Sabers::SaberModelContainer::Manifest(filePath);
    return Qosmetics::Sabers::SaberModelContainer::get_instance()->LoadObject(manifest, nullptr);
}

VISIBLE_API(GetSaberIsCustom, bool)
{
    return SABERMODELCONTAINER->currentSaberObject != nullptr;
}
/*
VISIBLE_API(GetInUseSaberClone, UnityEngine::GameObject*, int saberType)
{
    auto saberModelControllers = UnityEngine::Resources::FindObjectsOfTypeAll<Qosmetics::Sabers::SaberModelController*>();
    for (auto saberModelController : saberModelControllers)
    {
        if (saberModelController->saber->get_saberType().value == saberType)
        {
            auto saber = UnityEngine::Object::Instantiate(saberModelController->get_gameObject());
            saber->set_name(saberModelController->get_name());
            auto modelController = saber->GetComponent<Qosmetics::Sabers::SaberModelController*>();
            modelController->InitFromClone(saberModelController->saber);
            return saber->get_gameObject();
        }
    }
    return nullptr;
}
*/
VISIBLE_API(GetSaber, UnityEngine::GameObject*, int saberType)
{
    GET_SABERMODELCONTAINER();

    if (!saberModelContainer->currentSaberObject)
        return nullptr;
    return UnityEngine::Object::Instantiate(saberModelContainer->currentSaberObject->get_transform()->Find(saberType == 0 ? ConstStrings::LeftSaber() : ConstStrings::RightSaber())->get_gameObject());
}

VISIBLE_API(GetPrefabClone, UnityEngine::GameObject*)
{
    GET_SABERMODELCONTAINER();

    if (!saberModelContainer->currentSaberObject)
        return nullptr;
    return UnityEngine::Object::Instantiate(saberModelContainer->currentSaberObject);
}

VISIBLE_API(GetPrefab, UnityEngine::GameObject*)
{
    return SABERMODELCONTAINER->currentSaberObject;
}

VISIBLE_API(GetSabersDisabled, bool)
{
    return Qosmetics::Sabers::Disabling::GetAnyDisabling();
}

VISIBLE_API(UnregisterSaberDisablingInfo, void, modloader::ModInfo info)
{
    Qosmetics::Sabers::Disabling::UnregisterDisablingModInfo(info);
}

VISIBLE_API(RegisterSaberDisablingInfo, void, modloader::ModInfo info)
{
    Qosmetics::Sabers::Disabling::RegisterDisablingModInfo(info);
}

VISIBLE_API(GetSaberFolder, std::string)
{
    return whacker_path;
}

// Whacker Color Handler
VISIBLE_API(WhackerColorHandler_SetColor, void, Qosmetics::Sabers::WhackerColorHandler* self, const Sombrero::FastColor& thisColor, const Sombrero::FastColor& thatColor)
{
    self->SetColor(thisColor, thatColor);
}

// Trail Handler
VISIBLE_API(TrailHandler_SetColor, void, Qosmetics::Sabers::TrailHandler* self, const Sombrero::FastColor& leftColor, const Sombrero::FastColor& rightColor)
{
    self->SetColor(leftColor, rightColor);
}

VISIBLE_API(TrailHandler_SetTrailActive, void, Qosmetics::Sabers::TrailHandler* self, bool active)
{
    self->SetTrailActive(active);
}

VISIBLE_API(TrailComponent_Reset, void, Qosmetics::Sabers::TrailComponent* self)
{
    self->Reset();
}

#pragma GCC diagnostic pop
