#pragma once
#include "modloader/shared/modloader.hpp"

namespace Qosmetics::Sabers::Disabling
{
    void RegisterDisablingModInfo(ModInfo info);
    void UnregisterDisablingModInfo(ModInfo info);

    bool GetAnyDisabling();
}