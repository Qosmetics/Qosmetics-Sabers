#include "CustomTypes/SaberModelContainer.hpp"
#include "hooking.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "System/Action_1.hpp"
#include "Zenject/DiContainer.hpp"

MAKE_AUTO_HOOK_MATCH(MenuTransitionsHelper_RestartGame, &GlobalNamespace::MenuTransitionsHelper::RestartGame, void, GlobalNamespace::MenuTransitionsHelper* self, System::Action_1<Zenject::DiContainer*>* finishCallback)
{
    Qosmetics::Sabers::SaberModelContainer::get_instance()->OnGameRestart();
    MenuTransitionsHelper_RestartGame(self, finishCallback);
}