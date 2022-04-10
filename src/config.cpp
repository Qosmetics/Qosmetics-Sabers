#include "config.hpp"
#include "logging.hpp"

#include "CustomTypes/SaberModelContainer.hpp"
#include "UI/PreviewViewController.hpp"
#include "UI/SettingsViewController.hpp"
#include "static-defines.hpp"

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

#define GET_JSON_BOOL(identifier)                                                 \
    auto identifier##Itr = member.FindMember(#identifier);                        \
    if (identifier##Itr != member.MemberEnd() && identifier##Itr->value.IsBool()) \
    {                                                                             \
        actual_config.identifier = identifier##Itr->value.GetBool();              \
    }                                                                             \
    else                                                                          \
        foundEverything = false;

#define SET_JSON_BOOL(identifier)                                           \
    auto identifier##Itr = member.FindMember(#identifier);                  \
    if (identifier##Itr != member.MemberEnd())                              \
    {                                                                       \
        identifier##Itr->value.SetBool(actual_config.identifier);           \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        member.AddMember(#identifier, actual_config.identifier, allocator); \
    }

#define GET_JSON_DOUBLE(identifier)                                                 \
    auto identifier##Itr = member.FindMember(#identifier);                          \
    if (identifier##Itr != member.MemberEnd() && identifier##Itr->value.IsDouble()) \
    {                                                                               \
        actual_config.identifier = identifier##Itr->value.GetDouble();              \
    }                                                                               \
    else                                                                            \
        foundEverything = false;

#define SET_JSON_DOUBLE(identifier)                                         \
    auto identifier##Itr = member.FindMember(#identifier);                  \
    if (identifier##Itr != member.MemberEnd())                              \
    {                                                                       \
        identifier##Itr->value.SetDouble(actual_config.identifier);         \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        member.AddMember(#identifier, actual_config.identifier, allocator); \
    }

#define GET_JSON_ENUM(identifier)                                                                       \
    auto identifier##Itr = member.FindMember(#identifier);                                              \
    if (identifier##Itr != member.MemberEnd() && identifier##Itr->value.IsInt())                        \
    {                                                                                                   \
        actual_config.identifier = (decltype(actual_config.identifier))identifier##Itr->value.GetInt(); \
    }                                                                                                   \
    else                                                                                                \
        foundEverything = false;

#define SET_JSON_ENUM(identifier)                                                \
    auto identifier##Itr = member.FindMember(#identifier);                       \
    if (identifier##Itr != member.MemberEnd())                                   \
    {                                                                            \
        identifier##Itr->value.SetInt((int)actual_config.identifier);            \
    }                                                                            \
    else                                                                         \
    {                                                                            \
        member.AddMember(#identifier, (int)actual_config.identifier, allocator); \
    }

namespace Qosmetics::Sabers
{
    Config actual_config;

    Config& Config::get_config() { return actual_config; }
    void SaberConfigRegistration::SaveConfig(rapidjson::Value& member, rapidjson::Document::AllocatorType& allocator) const
    {
        INFO("Saving config...");
        SET_JSON_STRING(lastUsedWhacker);
        SET_JSON_DOUBLE(saberWidth);
        SET_JSON_BOOL(overrideTrailLength);
        SET_JSON_DOUBLE(trailLength);
        SET_JSON_BOOL(whiteTrail);
        SET_JSON_BOOL(overrideWhiteStep);
        SET_JSON_DOUBLE(whiteStep);
        SET_JSON_BOOL(overrideTrailWidth);
        SET_JSON_DOUBLE(trailWidth);
        SET_JSON_BOOL(enableMenuPointer);
        SET_JSON_DOUBLE(menuPointerSize);
        SET_JSON_ENUM(trailType);
        INFO("Config Saved!");
    }

    bool SaberConfigRegistration::LoadConfig(const rapidjson::Value& member) const
    {
        bool foundEverything = true;
        INFO("Loading config...");
        GET_JSON_STRING(lastUsedWhacker);
        GET_JSON_DOUBLE(saberWidth);
        GET_JSON_BOOL(overrideTrailLength);
        GET_JSON_DOUBLE(trailLength);
        GET_JSON_BOOL(whiteTrail);
        GET_JSON_BOOL(overrideWhiteStep);
        GET_JSON_DOUBLE(whiteStep);
        GET_JSON_BOOL(overrideTrailWidth);
        GET_JSON_DOUBLE(trailWidth);
        GET_JSON_BOOL(enableMenuPointer);
        GET_JSON_DOUBLE(menuPointerSize);
        GET_JSON_ENUM(trailType);

        if (foundEverything)
            INFO("Config Loaded!");
        return foundEverything;
    }

    void SaberConfigRegistration::OnProfileSwitched() const
    {
        // TODO: Saber shenanigans
        Qosmetics::Sabers::SettingsViewController::justChangedProfile = true;
        Qosmetics::Sabers::PreviewViewController::justChangedProfile = true;

        auto saberModelContainer = Qosmetics::Sabers::SaberModelContainer::get_instance();
        if (actual_config.lastUsedWhacker == "" || actual_config.lastUsedWhacker == "Default")
        {
            saberModelContainer->Default();
            return;
        }

        std::string filePath = fmt::format("{}/{}.whacker", whacker_path, actual_config.lastUsedWhacker);
        if (!fileexists(filePath))
        {
            saberModelContainer->Default();
            return;
        }

        auto manifest = Qosmetics::Core::Manifest<Qosmetics::Sabers::SaberObjectConfig>(filePath);
        saberModelContainer->LoadObject(manifest, nullptr);
    }

    QOSMETICS_CONFIG_REGISTER(SaberConfigRegistration, "whackerConfig");
}