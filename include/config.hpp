#pragma once
#include "qosmetics-core/shared/ConfigRegister.hpp"

namespace Qosmetics::Sabers
{
    struct Config
    {
        enum TrailType
        {
            CUSTOM,
            BASEGAME,
            NONE
        };

        std::string lastUsedWhacker;
        double saberWidth = 1.0f;
        bool overrideTrailLength = false;
        double trailLength = 14.0f;
        bool whiteTrail = false;
        bool overrideWhiteStep = false;
        double whiteStep = 0.1f;
        bool overrideTrailWidth = false;
        double trailWidth = 1.0f;
        bool enableMenuPointer = false;
        double menuPointerSize = 0.4f;
        TrailType trailType = CUSTOM;

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