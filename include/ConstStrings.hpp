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
    CONST_STRING(LeftSaber);
    CONST_STRING(RightSaber);
}