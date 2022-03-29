#include "config.hpp"
#include "logging.hpp"

#define GET_JSON_STRING(identifier)                                                                                           \
    auto identifier##Itr = member.FindMember(#identifier);                                                                    \
    if (identifier##Itr != member.MemberEnd() && identifier##Itr->value.IsString())                                           \
    {                                                                                                                         \
        actual_config.identifier = std::string(identifier##Itr->value.GetString(), identifier##Itr->value.GetStringLength()); \
    }                                                                                                                         \
    else                                                                                                                      \
        foundEverything = false;

#define SET_JSON_STRING(identifier)                                            \
    auto identifier##Itr = member.FindMember(#identifier);                     \
    if (identifier##Itr != member.MemberEnd())                                 \
    {                                                                          \
        identifier##Itr->value.SetString(actual_config.identifier, allocator); \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        member.AddMember(#identifier, actual_config.identifier, allocator);    \
    }

namespace Qosmetics::Sabers
{
    Config actual_config;

    Config& Config::get_config() { return actual_config; }
    void SaberConfigRegistration::SaveConfig(rapidjson::Value& member, rapidjson::Document::AllocatorType& allocator) const
    {
        INFO("Saving config...");
        SET_JSON_STRING(lastUsedWhacker);
        INFO("Config Saved!");
    }

    bool SaberConfigRegistration::LoadConfig(const rapidjson::Value& member) const
    {
        bool foundEverything = true;
        INFO("Loading config...");
        GET_JSON_STRING(lastUsedWhacker);
        if (foundEverything)
            INFO("Config Loaded!");
        return foundEverything;
    }

    void SaberConfigRegistration::OnProfileSwitched() const
    {
        // TODO: Saber shenanigans
        /*
                Qosmetics::Notes::PreviewViewController::justChangedProfile = true;
        Qosmetics::Notes::SettingsViewController::justChangedProfile = true;

        auto noteModelContainer = Qosmetics::Notes::NoteModelContainer::get_instance();
        if (actual_config.lastUsedCyoob == "" || actual_config.lastUsedCyoob == "Default")
        {
            noteModelContainer->Default();
            return;
        }

        std::string filePath = fmt::format("{}/{}.cyoob", cyoob_path, actual_config.lastUsedCyoob);
        if (!fileexists(filePath))
        {
            noteModelContainer->Default();
            return;
        }

        auto manifest = Qosmetics::Core::Manifest<Qosmetics::Notes::NoteObjectConfig>(filePath);
        noteModelContainer->LoadObject(manifest, nullptr);
        */
    }

    QOSMETICS_CONFIG_REGISTER(SaberConfigRegistration, "whackerConfig");
}