#pragma once
#include "beatsaber-hook/shared/utils/typedefs.h"

#ifndef CONST_STRING
#define CONST_STRING(identifier)                    \
    static StringW identifier()                     \
    {                                               \
        static ConstString identifier(#identifier); \
        return identifier;                          \
    }
#endif

namespace ConstStrings
{
    static StringW BasicSaberModelClone()
    {
        static ConstString BasicSaberModelClone("BasicSaberModel(Clone)");
        return BasicSaberModelClone;
    }

    CONST_STRING(LeftSaber);
    CONST_STRING(RightSaber);
    CONST_STRING(DefaultTrail);
    CONST_STRING(TrailEnd);
    CONST_STRING(TrailStart);
    CONST_STRING(CustomTrailStart);
}