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

#ifndef GET_DOUBLE
#define GET_DOUBLE(identifier)                                                     \
    auto identifier##Itr = value.FindMember(#identifier);                          \
    if (identifier##Itr != value.MemberEnd() && identifier##Itr->value.IsDouble()) \
    {                                                                              \
        identifier = identifier##Itr->value.GetDouble();                           \
    }

#endif

#ifndef ADD_DOUBLE
#define ADD_DOUBLE(identifier) val.AddMember(#identifier, identifier, allocator)
#endif

#ifndef GET_ENUM
#define GET_ENUM(identifier)                                                    \
    auto identifier##Itr = value.FindMember(#identifier);                       \
    if (identifier##Itr != value.MemberEnd() && identifier##Itr->value.IsInt()) \
    {                                                                           \
        identifier = (decltype(identifier))identifier##Itr->value.GetInt();     \
    }

#endif

#ifndef ADD_ENUM
#define ADD_ENUM(identifier) val.AddMember(#identifier, (int)identifier, allocator)
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
        SaberObjectConfig(bool hasTrail) : Qosmetics::Core::BasicConfig(), hasTrail(hasTrail), isLegacy(true), isDefault(false){};
        SaberObjectConfig(const rapidjson::Value& value) : Qosmetics::Core::BasicConfig(value)
        {
            GET_BOOL(hasTrail);
            GET_BOOL(isLegacy);
            isDefault = false;
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
        CONST_GETTER(isDefault);

    private:
        bool hasTrail = false;
        bool isLegacy = false;
        bool isDefault = true;
    };
}