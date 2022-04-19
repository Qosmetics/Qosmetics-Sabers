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
#include "UnityEngine/Transform.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

#define SABERMODELCONTAINER Qosmetics::Sabers::SaberModelContainer::get_instance()
#define GET_SABERMODELCONTAINER() auto saberModelContainer = SABERMODELCONTAINER

EXPOSE_API(GetActiveDescriptor, Qosmetics::Core::Descriptor)
{
    return SABERMODELCONTAINER->GetDescriptor();
}

EXPOSE_API(GetConfig, Qosmetics::Sabers::SabersConfig*)
{
    return reinterpret_cast<Qosmetics::Sabers::SabersConfig*>(&Qosmetics::Sabers::Config::get_config());
}

EXPOSE_API(SetDefault, void)
{
    SABERMODELCONTAINER->Default();
}

EXPOSE_API(SetActiveFromFilePath, bool, std::string filePath)
{
    if (!fileexists(filePath))
        return false;
    auto manifest = Qosmetics::Sabers::SaberModelContainer::Manifest(filePath);
    return Qosmetics::Sabers::SaberModelContainer::get_instance()->LoadObject(manifest, nullptr);
}

EXPOSE_API(SetActive, bool, std::string fileName)
{
    std::string filePath = fmt::format("{}/{}", whacker_path, fileName);
    if (!fileexists(filePath))
        return false;
    auto manifest = Qosmetics::Sabers::SaberModelContainer::Manifest(filePath);
    return Qosmetics::Sabers::SaberModelContainer::get_instance()->LoadObject(manifest, nullptr);
}

EXPOSE_API(GetSaberIsCustom, bool)
{
    return SABERMODELCONTAINER->currentSaberObject != nullptr;
}

EXPOSE_API(GetSaber, UnityEngine::GameObject*, bool left)
{
    GET_SABERMODELCONTAINER();

    if (!saberModelContainer->currentSaberObject)
        return nullptr;
    return UnityEngine::Object::Instantiate(saberModelContainer->currentSaberObject->get_transform()->Find(left ? ConstStrings::LeftSaber() : ConstStrings::RightSaber())->get_gameObject());
}

EXPOSE_API(GetPrefabClone, UnityEngine::GameObject*)
{
    GET_SABERMODELCONTAINER();

    if (!saberModelContainer->currentSaberObject)
        return nullptr;
    return UnityEngine::Object::Instantiate(saberModelContainer->currentSaberObject);
}

EXPOSE_API(GetPrefab, UnityEngine::GameObject*)
{
    return SABERMODELCONTAINER->currentSaberObject;
}

EXPOSE_API(GetSabersDisabled, bool)
{
    return Qosmetics::Sabers::Disabling::GetAnyDisabling();
}

EXPOSE_API(UnregisterSaberDisablingInfo, void, ModInfo info)
{
    Qosmetics::Sabers::Disabling::UnregisterDisablingModInfo(info);
}

EXPOSE_API(RegisterSaberDisablingInfo, void, ModInfo info)
{
    Qosmetics::Sabers::Disabling::RegisterDisablingModInfo(info);
}

EXPOSE_API(GetSaberFolder, std::string)
{
    return whacker_path;
}

// Whacker Color Handler
EXPOSE_API(WhackerColorHandler_SetColor, void, Qosmetics::Sabers::WhackerColorHandler* self, const Sombrero::FastColor& thisColor, const Sombrero::FastColor& thatColor)
{
    self->SetColor(thisColor, thatColor);
}

// Trail Handler
EXPOSE_API(TrailHandler_SetColor, void, Qosmetics::Sabers::TrailHandler* self, const Sombrero::FastColor& leftColor, const Sombrero::FastColor& rightColor)
{
    self->SetColor(leftColor, rightColor);
}

EXPOSE_API(TrailHandler_SetTrailActive, void, Qosmetics::Sabers::TrailHandler* self, bool active)
{
    self->SetTrailActive(active);
}

EXPOSE_API(TrailComponent_Reset, void, Qosmetics::Sabers::TrailComponent* self)
{
    self->Reset();
}

#pragma GCC diagnostic pop