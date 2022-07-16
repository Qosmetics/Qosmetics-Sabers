#include "CustomTypes/SaberModelController.hpp"
#include "UI/WhackerFlowCoordinator.hpp"
#include "hooking.hpp"
#include "logging.hpp"
#include "modloader/shared/modloader.hpp"
#include "qosmetics-core/shared/FlowCoordinatorRegister.hpp"
#include "qosmetics-core/shared/SaberModelControllerRegister.hpp"
#include "static-defines.hpp"

#include "assets.hpp"
#include "diglett/shared/Conversions.hpp"
#include "diglett/shared/Register.hpp"

#include "questui/shared/BeatSaberUI.hpp"

SABERMODELCONTROLLER_REGISTRATION(QosmeticsSabers, 10, true, Qosmetics::Sabers::SaberModelController*);

QOSMETICS_FLOWCOORDINATOR_REGISTER(Whackers, Qosmetics::Sabers::WhackerFlowCoordinator*)
{
    auto inactive = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::SaberIcon_png);
    auto active = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::SaberIconSelected_png);
    return std::make_pair(inactive, active);
}

ModInfo modInfo = {MOD_ID, VERSION};

extern "C" void setup(ModInfo& info)
{
    info = modInfo;
}

extern "C" void load()
{
    il2cpp_functions::Class_Init(classof(HMUI::ImageView*));
    il2cpp_functions::Class_Init(classof(HMUI::CurvedTextMeshPro*));

    mkpath(whacker_path);
    auto& logger = Qosmetics::Sabers::Logging::getLogger();
    Hooks::InstallHooks(logger);
    custom_types::Register::AutoRegister();

    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::de_xml), Diglett::Language::GERMAN);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::en_xml), Diglett::Language::ENGLISH);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::es_xml), Diglett::Language::SPANISH);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::fr_xml), Diglett::Language::FRENCH);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::ja_xml), Diglett::Language::JAPANESE);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::ko_xml), Diglett::Language::KOREAN);
}