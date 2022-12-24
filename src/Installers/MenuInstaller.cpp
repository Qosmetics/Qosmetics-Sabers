#include "Installers/MenuInstaller.hpp"

#include "UI/PreviewViewController.hpp"
#include "UI/SelectionViewController.hpp"
#include "UI/SettingsViewController.hpp"
#include "UI/WhackerFlowCoordinator.hpp"

#include "lapiz/shared/arrayutils.hpp"
#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(Qosmetics::Sabers, MenuInstaller);

using namespace ::Lapiz::Zenject::ZenjectExtensions;

namespace Qosmetics::Sabers
{
    void MenuInstaller::InstallBindings()
    {
        auto container = get_Container();

        FromNewComponentOnNewGameObject(container->Bind<Qosmetics::Core::QosmeticsBaseFlowCoordinator*>()->To(Lapiz::ArrayUtils::TypeArray<Qosmetics::Sabers::WhackerFlowCoordinator*>()))->AsSingle();
        FromNewComponentAsViewController(container->BindInterfacesAndSelfTo<Qosmetics::Sabers::PreviewViewController*>())->AsSingle();
        FromNewComponentAsViewController(container->BindInterfacesAndSelfTo<Qosmetics::Sabers::SettingsViewController*>())->AsSingle();
        FromNewComponentAsViewController(container->BindInterfacesAndSelfTo<Qosmetics::Sabers::SelectionViewController*>())->AsSingle();
    }
}