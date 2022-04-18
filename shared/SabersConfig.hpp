#pragma once
#include <string>

namespace Qosmetics::Sabers
{
    struct SabersConfig
    {
    public:
        enum TrailType
        {
            CUSTOM,
            BASEGAME,
            NONE
        };

        const std::string_view get_lastUsedWhacker() const { return lastUsedWhacker; };
        double get_saberLength() { return saberLength; };
        double get_saberWidth() { return saberWidth; };
        bool get_overrideTrailLength() { return overrideTrailLength; };
        int get_trailLength() { return trailLength; };
        bool get_whiteTrail() { return whiteTrail; };
        bool get_overrideWhiteStep() { return overrideWhiteStep; };
        double get_whiteStep() { return whiteStep; };
        bool get_overrideTrailWidth() { return overrideTrailWidth; };
        double get_trailWidth() { return trailWidth; };
        bool get_enableMenuPointer() { return enableMenuPointer; };
        double get_menuPointerSize() { return menuPointerSize; };
        TrailType get_trailType() { return trailType; };

    private:
        std::string lastUsedWhacker;
        double saberLength = 1.0f;
        double saberWidth = 1.0f;
        bool overrideTrailLength = false;
        int trailLength = 14;
        bool whiteTrail = false;
        bool overrideWhiteStep = false;
        double whiteStep = 0.1f;
        bool overrideTrailWidth = false;
        double trailWidth = 1.0f;
        bool enableMenuPointer = false;
        double menuPointerSize = 0.4f;
        TrailType trailType = CUSTOM;
    };
}