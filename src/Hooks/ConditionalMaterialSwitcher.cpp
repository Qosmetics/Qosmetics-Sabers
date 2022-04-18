#include "hooking.hpp"

#include "GlobalNamespace/ConditionalMaterialSwitcher.hpp"
#include "UnityEngine/GameObject.hpp"

// Fix trails cutting into eachother by using the PC material
MAKE_AUTO_HOOK_ORIG_MATCH(ConditionalMaterialSwitcher_Awake, &GlobalNamespace::ConditionalMaterialSwitcher::Awake, void, GlobalNamespace::ConditionalMaterialSwitcher* self)
{
    if (self->get_name() == "Trail(Clone)")
        return;
    ConditionalMaterialSwitcher_Awake(self);
}