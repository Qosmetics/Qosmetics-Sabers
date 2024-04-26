#include "UI/WhackerFlowCoordinator.hpp"
#include "_config.h"
#include "hooking.hpp"
#include "logging.hpp"
#include "scotland2/shared/modloader.h"
#include "static-defines.hpp"

#include "assets.hpp"

#include "Installers/AppInstaller.hpp"
#include "Installers/GameInstaller.hpp"
#include "Installers/MenuInstaller.hpp"
#include "lapiz/shared/AttributeRegistration.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"

modloader::ModInfo modInfo = {MOD_ID, VERSION, 0};

QOSMETICS_SABERS_EXPORT_FUNC void setup(CModInfo* info)
{
    info->id = MOD_ID;
    info->version = VERSION;
    info->version_long = 0;
}

QOSMETICS_SABERS_EXPORT_FUNC void late_load()
{
    il2cpp_functions::Init();

    mkpath(whacker_path);
    Hooks::InstallHooks();
    custom_types::Register::AutoRegister();
    Lapiz::Attributes::AutoRegister();

    auto zenjector = Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<Qosmetics::Sabers::AppInstaller*>(Lapiz::Zenject::Location::App);
    zenjector->Install<Qosmetics::Sabers::MenuInstaller*>(Lapiz::Zenject::Location::Menu);
    zenjector->Install<Qosmetics::Sabers::GameInstaller*>(Lapiz::Zenject::Location::Player | Lapiz::Zenject::Location::Tutorial);
}
