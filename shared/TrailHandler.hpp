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
    class TrailHandler : UnityEngine::MonoBehaviour
    {
    public:
        /// @brief set the colors for this trail
        /// @param leftColor the main color
        /// @param rightColor the other color
        void SetColor(const COLOR& leftColor, const COLOR& rightColor) const
        {
            static auto function = CondDeps::FindUnsafe<void, decltype(this), const COLOR&, const COLOR&>(QOSMETICS_SABERS, "TrailHandler_SetColor");
            if (!function)
                return;

            function.value()(this, leftColor, rightColor);
        }

        /// @brief set the trail active for this trail
        /// @param active true / false for active / inactive
        void SetTrailActive(bool active) const
        {
            static auto function = CondDeps::FindUnsafe<void, decltype(this), bool>(QOSMETICS_SABERS, "TrailHandler_SetTrailActive");
            if (!function)
                return;

            function.value()(this, active);
        }
    };
}

DEFINE_IL2CPP_ARG_TYPE(Qosmetics::Sabers::TrailHandler*, "Qosmetics.Sabers", "TrailHandler");
#undef QOSMETICS_SABERS
#undef COLOR