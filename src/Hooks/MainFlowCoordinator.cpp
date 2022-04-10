#include "hooking.hpp"

#include "CustomTypes/SaberModelContainer.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"

// just a hook to make sure the model container inits itself
MAKE_AUTO_HOOK_MATCH(MainFlowCoordinator_DidActivate, &GlobalNamespace::MainFlowCoordinator::DidActivate, void, GlobalNamespace::MainFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    MainFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    auto noteModelContainer = Qosmetics::Sabers::SaberModelContainer::get_instance();
}