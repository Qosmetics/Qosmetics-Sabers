#pragma once
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "sombrero/shared/FastColor.hpp"
#include <string>
#include <vector>

namespace Qosmetics::Sabers::QsaberConversion
{
    struct LegacyDescriptor
    {
        std::string authorName;
        std::string objectName;
        std::string description;

        LegacyDescriptor(const rapidjson::Document& doc)
        {
            authorName = doc["authorName"].GetString();
            objectName = doc["objectName"].GetString();
            description = doc["description"].GetString();
        }
    };

    struct LegacyTrail
    {
        std::string name;
        int colorType;
        Sombrero::FastColor trailColor;
        Sombrero::FastColor multiplierColor;
        int length;
        float whiteStep;
        LegacyTrail(const rapidjson::Value& val)
        {
            name = val["name"].GetString();
            colorType = val["colorType"].GetInt();
            auto trailColorItr = val["trailColorItr"].GetObject();
            trailColor = {
                float(trailColorItr["R"].GetDouble()),
                float(trailColorItr["G"].GetDouble()),
                float(trailColorItr["B"].GetDouble()),
                float(trailColorItr["A"].GetDouble())};
            auto multiplierColorItr = val["multiplierColorItr"].GetObject();
            multiplierColor = {
                float(multiplierColorItr["R"].GetDouble()),
                float(multiplierColorItr["G"].GetDouble()),
                float(multiplierColorItr["B"].GetDouble()),
                float(multiplierColorItr["A"].GetDouble())};
            length = val["length"].GetInt();
            whiteStep = val["whiteStep"].GetDouble();
        }
    };

    struct LegacyConfig
    {
        bool enableFakeGlow;
        bool hasCustomTrails;
        std::vector<LegacyTrail> leftTrails;
        std::vector<LegacyTrail> rightTrails;

        LegacyConfig(const rapidjson::Document& doc)
        {
            enableFakeGlow = doc["enableFakeGlow"].GetBool();
            hasCustomTrails = doc["hasCustomTrails"].GetBool();
            for (auto& trail : doc["leftTrails"].GetArray())
                leftTrails.emplace_back(trail);
            for (auto& trail : doc["rightTrails"].GetArray())
                rightTrails.emplace_back(trail);
        }
    };

    void ConvertOldQsabers();

    std::vector<std::string> GetQsaberFiles();
    std::vector<std::pair<std::string, std::string>> GetNonConverted(std::vector<std::string> filePaths);
    custom_types::Helpers::Coroutine ConvertAllFoundQsabers(std::vector<std::pair<std::string, std::string>> oldNewPathPairs);
}