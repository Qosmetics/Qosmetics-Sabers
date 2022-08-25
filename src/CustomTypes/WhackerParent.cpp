#include "CustomTypes/WhackerParent.hpp"
#include "logging.hpp"

#include <map>

DEFINE_TYPE(Qosmetics::Sabers, WhackerParent);

#if __has_include("chroma/shared/SaberAPI.hpp")
#include "chroma/shared/CoreAPI.hpp"
#include "chroma/shared/SaberAPI.hpp"
#ifndef HAS_CHROMA
#define HAS_CHROMA
#endif
#endif

namespace Qosmetics::Sabers
{
    static std::map<GlobalNamespace::SaberModelController*, WhackerParent*> saberModelControllerToWhackerParentMap = {};
    void WhackerParent::set_defaultSaber(bool value)
    {
        defaultSaber = value;
#ifdef HAS_CHROMA
        if (Chroma::CoreAPI::isChromaRunning())
        {
            Chroma::SaberAPI::setSaberColorable(saberModelController, !defaultSaber);

            auto callbackOpt = Chroma::SaberAPI::getSaberChangedColorCallbackSafe();
            if (callbackOpt.has_value())
            {
                auto& callback = callbackOpt.value().get();
                callback += &WhackerParent::Colorize;
            }
        }
#endif
    }

    void WhackerParent::Awake()
    {
        saberModelController = GetComponent<GlobalNamespace::SaberModelController*>();
        saberModelControllerToWhackerParentMap[saberModelController] = this;
    }

    void WhackerParent::OnDestroy()
    {
        saberModelControllerToWhackerParentMap.erase(saberModelController);
#ifdef HAS_CHROMA
        if (Chroma::CoreAPI::isChromaRunning())
        {
            Chroma::SaberAPI::setSaberColorable(saberModelController, false);
        }
#endif
    }

    void WhackerParent::ColorizeSpecific(int saberType, const Sombrero::FastColor& saberTypeColor)
    {
        const auto& thisColor = saberType == whackerHandler->saberType.value ? saberTypeColor : whackerHandler->colorHandler->lastThisColor;
        const auto& thatColor = saberType == whackerHandler->saberType.value ? whackerHandler->colorHandler->lastThatColor : saberTypeColor;
        // if the types are the same, the color being set is THIS color
        whackerHandler->SetColor(thisColor, thatColor);

        switch (whackerHandler->saberType.value)
        {
        case 0:
            for (auto trail : whackerHandler->trailHandlers)
                trail->SetColor(thisColor, thatColor);
        case 1:
            for (auto trail : whackerHandler->trailHandlers)
                trail->SetColor(thatColor, thisColor);
        default:
            break;
        }
    }

    void WhackerParent::Colorize(int saberType, GlobalNamespace::SaberModelController* saberModelController, const Sombrero::FastColor& saberTypeColor)
    {
        auto whackerItr = saberModelControllerToWhackerParentMap.find(saberModelController);

        if (whackerItr != saberModelControllerToWhackerParentMap.end())
            whackerItr->second->ColorizeSpecific(saberType, saberTypeColor);
    }
}