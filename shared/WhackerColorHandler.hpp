#pragma once

#include "UnityEngine/Material.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "conditional-dependencies/shared/main.hpp"

#if __has_include("sombrero/shared/FastColor.hpp")
#include "sombrero/shared/FastColor.hpp"
#define COLOR Sombrero::FastColor
#else
#include "UnityEngine/Color.hpp"
#define COLOR UnityEngine::Color
#endif

#define QOSMETICS_SABERS "qosmetics-sabers"

namespace Qosmetics::Sabers
{
    class WhackerColorHandler : UnityEngine::MonoBehaviour
    {
    public:
        /// @brief set the colors for this whacker, does NOT handle trails
        /// @param thisColor the main color
        /// @param thatColor the other color
        void SetColor(const COLOR& thisColor, const COLOR& thatColor) const
        {
            static auto function = CondDeps::FindUnsafe<void, decltype(this), const COLOR&, const COLOR&>(QOSMETICS_SABERS, "WhackerColorHandler_SetColor");
            if (!function)
                return;

            function.value()(this, thisColor, thatColor);
        }
    };
}

DEFINE_IL2CPP_ARG_TYPE(Qosmetics::Sabers::WhackerColorHandler*, "Qosmetics.Sabers", "WhackerColorHandler");

#undef QOSMETICS_SABERS
#undef COLOR