#include "MaterialUtils.hpp"
#include "PropertyID.hpp"

#define HAS_FLOAT(theFloat) material->HasProperty(PropertyID::theFloat())
#define CHECK_FLOAT(theFloat) (material->GetFloat(PropertyID::theFloat()) > 0)

using namespace UnityEngine;

namespace Qosmetics::Sabers::MaterialUtils
{
    bool ShouldCC(Material* material)
    {
        if (!material)
            return false;
        else if (HAS_FLOAT(_CustomColors))
            return CHECK_FLOAT(_CustomColors);
        else if (HAS_FLOAT(_Glow))
            return CHECK_FLOAT(_Glow);
        else if (HAS_FLOAT(_Bloom))
            return CHECK_FLOAT(_Bloom);
        return false;
    }
}