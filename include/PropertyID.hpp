#pragma once

#include "UnityEngine/Shader.hpp"

#ifndef PROPERTY_ID
#define PROPERTY_ID(identifier)                                                 \
    static int identifier()                                                     \
    {                                                                           \
        static int identifier = UnityEngine::Shader::PropertyToID(#identifier); \
        return identifier;                                                      \
    }
#endif

namespace PropertyID
{
    PROPERTY_ID(_CustomColors);
    PROPERTY_ID(_Glow);
    PROPERTY_ID(_Bloom);
    PROPERTY_ID(_Color);
    PROPERTY_ID(_OtherColor);
    PROPERTY_ID(_Alpha);
    PROPERTY_ID(_StencilRefID);
    PROPERTY_ID(_StencilComp);
    PROPERTY_ID(_StencilOp);
    PROPERTY_ID(_BlendSrcFactor);
    PROPERTY_ID(_BlendDstFactor);
    PROPERTY_ID(_BlendSrcFactorA);
    PROPERTY_ID(_BlendDstFactorA);
    PROPERTY_ID(_SlicePos);
    PROPERTY_ID(_CutPlane);
    PROPERTY_ID(_TransformOffset);
}