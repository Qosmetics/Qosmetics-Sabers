#pragma once
#include "qosmetics-core/shared/ConfigRegister.hpp"

namespace Qosmetics::Sabers
{
    struct Config
    {
        std::string lastUsedWhacker;

        static Config& get_config();
    };

    struct SaberConfigRegistration : public Qosmetics::Core::Config::Registration
    {
        SaberConfigRegistration(std::string_view memberName) : Qosmetics::Core::Config::Registration(memberName){};
        void SaveConfig(rapidjson::Value& member, rapidjson::Document::AllocatorType& allocator) const override;
        bool LoadConfig(const rapidjson::Value& member) const override;
        void OnProfileSwitched() const override;
    };
}