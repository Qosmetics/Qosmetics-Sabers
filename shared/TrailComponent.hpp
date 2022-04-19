#pragma once

#include "UnityEngine/MonoBehaviour.hpp"
#include "conditional-dependencies/shared/main.hpp"

#define QOSMETICS_SABERS "qosmetics-sabers"

namespace Qosmetics::Sabers
{
    class TrailComponent : UnityEngine::MonoBehaviour
    {
    public:
        /// @brief Reset the trail
        void Reset() const
        {
            static auto function = CondDeps::FindUnsafe<void, decltype(this)>(QOSMETICS_SABERS, "TrailComponent_Reset");
            if (!function)
                return;

            function.value()(this);
        }
    };
}

DEFINE_IL2CPP_ARG_TYPE(Qosmetics::Sabers::TrailComponent*, "Qosmetics.Sabers", "TrailComponent");

#undef QOSMETICS_SABERS