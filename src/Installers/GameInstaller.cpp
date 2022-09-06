#include "Installers/GameInstaller.hpp"
#include "ConstStrings.hpp"
#include "Disabling.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "CustomTypes/SaberModelController.hpp"
#include "CustomTypes/TrailComponent.hpp"
#include "CustomTypes/TrailHandler.hpp"
#include "CustomTypes/TrailTransform.hpp"
#include "CustomTypes/WhackerColorHandler.hpp"
#include "CustomTypes/WhackerHandler.hpp"
#include "CustomTypes/WhackerParent.hpp"

#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/DiContainer.hpp"

#include "lapiz/shared/sabers/SaberModelRegistration.hpp"

DEFINE_TYPE(Qosmetics::Sabers, GameInstaller);

namespace Qosmetics::Sabers
{
    void GameInstaller::ctor(SaberModelContainer* saberModelContainer, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetupData)
    {
        _saberModelContainer = saberModelContainer;
        _gameplayCoreSceneSetupData = gameplayCoreSceneSetupData;
    }

    void GameInstaller::InstallBindings()
    {
        if (Disabling::GetAnyDisabling())
            return;

        DEBUG("Install Bindings");
        auto container = get_Container();
        auto reg = Lapiz::Sabers::SaberModelRegistration::Create<Qosmetics::Sabers::SaberModelController*>(DECORATION_PRIORITY);
        container->Bind<Lapiz::Sabers::SaberModelRegistrationWrapper*>()->FromInstance(Lapiz::Sabers::SaberModelRegistrationWrapper::Make(reg))->AsSingle();
    }
}
