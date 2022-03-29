#pragma once
#include "beatsaber-hook/shared/config./rapidjson-utils.hpp"
#include "qosmetics-core/shared/Data/BasicConfig.hpp"

#ifndef GET_BOOL
#define GET_BOOL(identifier)                                                              \
    auto identifier##Itr = value.FindMember(#identifier);                                 \
    if (identifier##Itr != value.MemberEnd())                                             \
    {                                                                                     \
        identifier = identifier##Itr->value.IsBool() && identifier##Itr->value.GetBool(); \
    }

#endif

#ifndef ADD_BOOL
#define ADD_BOOL(identifier) val.AddMember(#identifier, identifier, allocator)
#endif

#ifndef CONST_GETTER
#define CONST_GETTER(identifier) \
    auto get_##identifier() const { return identifier; }
#endif

namespace Qosmetics::Sabers
{
    class SaberObjectConfig : public Qosmetics::Core::BasicConfig
    {
    public:
        SaberObjectConfig() : Qosmetics::Core::BasicConfig(){};
        SaberObjectConfig(const rapidjson::Value& value) : Qosmetics::Core::BasicConfig(value)
        {
            GET_BOOL(hasTrail);
            GET_BOOL(isLegacy);
        }

        rapidjson::Value ToJson(rapidjson::Document::AllocatorType& allocator) override
        {
            rapidjson::Value val;
            val.SetObject();
            ADD_BOOL(hasTrail);
            ADD_BOOL(isLegacy);
            return val;
        }

        CONST_GETTER(hasTrail);
        CONST_GETTER(isLegacy);

    private:
        bool hasTrail = false;
        bool isLegacy = false;
    };
}