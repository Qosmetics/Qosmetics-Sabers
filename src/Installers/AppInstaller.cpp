#include "Installers/AppInstaller.hpp"

#include "CustomTypes/SaberModelContainer.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"
#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

DEFINE_TYPE(Qosmetics::Sabers, AppInstaller);

namespace Qosmetics::Sabers
{
    void AppInstaller::InstallBindings()
    {
        auto container = get_Container();

        ::Lapiz::Zenject::ZenjectExtensions::FromNewComponentOnNewGameObject(container->BindInterfacesAndSelfTo<Qosmetics::Sabers::SaberModelContainer*>())->AsSingle()->NonLazy();
    }
}