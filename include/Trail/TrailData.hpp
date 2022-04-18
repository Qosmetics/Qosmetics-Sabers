#pragma once
#include "QsaberConversion.hpp"
#include "UnityEngine/UI/Text.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "sombrero/shared/FastColor.hpp"

namespace Qosmetics::Sabers
{
    struct TrailData
    {
        int trailId;
        int colorType;

        Sombrero::FastColor trailColor;
        Sombrero::FastColor multiplierColor;

        int length;
        float whiteStep;

        constexpr TrailData() = default;
        constexpr TrailData(int trailId, int colorType, const Sombrero::FastColor& trailColor, const Sombrero::FastColor& multiplierColor, int length, float whiteStep) : trailId(trailId), colorType(colorType), trailColor(trailColor), multiplierColor(multiplierColor), length(length), whiteStep(whiteStep){};
        constexpr TrailData(int trailId, const QsaberConversion::LegacyTrail& legacyTrail) : trailId(trailId), colorType(legacyTrail.colorType), trailColor(legacyTrail.trailColor), multiplierColor(legacyTrail.multiplierColor), length(legacyTrail.length), whiteStep(legacyTrail.whiteStep){};
        constexpr TrailData(const rapidjson::Document& doc)
        {
            ParseDoc(doc);
        };

        void ParseDoc(const rapidjson::Document& doc)
        {
            trailId = doc["trailId"].GetInt();
            colorType = doc["colorType"].GetInt();
            auto trailColorItr = doc["trailColor"].GetObject();
            trailColor = {float(trailColorItr["r"].GetDouble()),
                          float(trailColorItr["g"].GetDouble()),
                          float(trailColorItr["b"].GetDouble()),
                          float(trailColorItr["a"].GetDouble())};
            auto multiplierColorItr = doc["multiplierColor"].GetObject();
            multiplierColor = {float(multiplierColorItr["r"].GetDouble()),
                               float(multiplierColorItr["g"].GetDouble()),
                               float(multiplierColorItr["b"].GetDouble()),
                               float(multiplierColorItr["a"].GetDouble())};
            length = doc["length"].GetInt();
            whiteStep = doc["whiteStep"].GetDouble();
        }

        rapidjson::Value ToJson(rapidjson::Document::AllocatorType& allocator) const
        {
            rapidjson::Value val;
            val.SetObject();

            val.AddMember("trailId", trailId, allocator);
            val.AddMember("colorType", colorType, allocator);
            rapidjson::Value trailColorVal;
            trailColorVal.SetObject();
            trailColorVal.AddMember("r", trailColor.r, allocator);
            trailColorVal.AddMember("g", trailColor.g, allocator);
            trailColorVal.AddMember("b", trailColor.b, allocator);
            trailColorVal.AddMember("a", trailColor.a, allocator);
            val.AddMember("trailColor", trailColorVal, allocator);

            rapidjson::Value multiplierColorVal;
            multiplierColorVal.SetObject();
            multiplierColorVal.AddMember("r", multiplierColor.r, allocator);
            multiplierColorVal.AddMember("g", multiplierColor.g, allocator);
            multiplierColorVal.AddMember("b", multiplierColor.b, allocator);
            multiplierColorVal.AddMember("a", multiplierColor.a, allocator);
            val.AddMember("multiplierColor", multiplierColorVal, allocator);

            val.AddMember("length", length, allocator);
            val.AddMember("whiteStep", whiteStep, allocator);

            return val;
        }
    };
}