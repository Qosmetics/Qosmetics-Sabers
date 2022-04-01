#include "hooking.hpp"
#include "modloader/shared/modloader.hpp"
#include "static-defines.hpp"

#include "qosmetics-core/shared/FlowCoordinatorRegister.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "diglett/shared/Conversions.hpp"
#include "diglett/shared/Register.hpp"

#include "assets.hpp"
#include "logging.hpp"

#include "UI/WhackerFlowCoordinator.hpp"

QOSMETICS_FLOWCOORDINATOR_REGISTER(Whackers, Qosmetics::Sabers::WhackerFlowCoordinator*)
{
    auto inactive_data = SaberIcon_png::getData();
    auto inactive = QuestUI::BeatSaberUI::VectorToSprite(std::vector<uint8_t>(inactive_data, inactive_data + SaberIcon_png::getLength()));
    auto active_data = SaberIconSelected_png::getData();
    auto active = QuestUI::BeatSaberUI::VectorToSprite(std::vector<uint8_t>(active_data, active_data + SaberIconSelected_png::getLength()));
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

    Diglett::RegisterAsset(ASSET_TO_STR(de_xml), Diglett::Language::GERMAN);
    Diglett::RegisterAsset(ASSET_TO_STR(en_xml), Diglett::Language::ENGLISH);
    Diglett::RegisterAsset(ASSET_TO_STR(es_xml), Diglett::Language::SPANISH);
    Diglett::RegisterAsset(ASSET_TO_STR(fr_xml), Diglett::Language::FRENCH);
    Diglett::RegisterAsset(ASSET_TO_STR(ja_xml), Diglett::Language::JAPANESE);
    Diglett::RegisterAsset(ASSET_TO_STR(ko_xml), Diglett::Language::KOREAN);
}