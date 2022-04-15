#pragma once
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "sombrero/shared/FastColor.hpp"

namespace Qosmetics::Sabers
{
    struct TrailPoint
    {
        int trailId;
        int isTop;

        bool get_isTop()
        {
            return isTop;
        }

        TrailPoint(int trailId, bool isTop) : trailId(trailId), isTop(isTop){};
        TrailPoint(rapidjson::Document& doc)
        {
            ParseDoc(doc);
        };

        void ParseDoc(rapidjson::Document& doc)
        {
            trailId = doc["trailId"].GetInt();
            isTop = (int)doc["isTop"].GetBool();
        }

        rapidjson::Value ToJson(rapidjson::Document::AllocatorType& allocator)
        {
            rapidjson::Value val;
            val.SetObject();

            val.AddMember("trailId", trailId, allocator);
            val.AddMember("isTop", (bool)isTop, allocator);
            return val;
        }
    };
}