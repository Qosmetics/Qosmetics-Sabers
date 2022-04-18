#pragma once
#include "sombrero/shared/FastColor.hpp"

struct TrailInitData
{
    int TrailLength = 30;
    float Whitestep = 0.2f;
    Sombrero::FastColor TrailColor = {1.0f, 1.0f, 1.0f, 1.0f};
    int Granularity = 80;

    constexpr TrailInitData() = default;
    constexpr TrailInitData(int length, float whiteStep, Sombrero::FastColor const& trailColor)
    {
        TrailLength = length;
        Whitestep = whiteStep;
        TrailColor = trailColor;
        Granularity = length * 6;
    }
};