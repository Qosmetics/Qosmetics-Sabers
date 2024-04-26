#include "CustomTypes/WhackerHandler.hpp"
#include "Trail/TrailInitData.hpp"
#include "logging.hpp"

#include <map>

DEFINE_TYPE(Qosmetics::Sabers, WhackerHandler);

namespace Qosmetics::Sabers
{
    void WhackerHandler::GetTrailHandlers()
    {
        trailHandlers = GetComponentsInChildren<TrailHandler*>(true);
        trailTransforms = GetComponentsInChildren<TrailTransform*>(true);
    }

    void WhackerHandler::SetupTrails()
    {
        if (!trailHandlers)
            GetTrailHandlers();

        DEBUG("trailTransforms size: {}", trailTransforms.size());
        DEBUG("trailHandlers size: {}", trailHandlers.size());

        for (auto t : trailTransforms)
            t->Init();

        for (auto handler : trailHandlers)
        {
            handler->InitData();
            TrailTransform *top = nullptr, *bot = nullptr;

            for (auto t : trailTransforms)
            {
                if (t->TrailID == handler->TrailID)
                {
                    if (t->IsTop)
                        top = t;
                    else
                        bot = t;
                    if (top && bot)
                        break;
                }
            }

            handler->InitTransforms(top->transform, bot->transform);
            handler->InitTrail();
        }
    }

    void WhackerHandler::SetColor(const Sombrero::FastColor& thisColor, const Sombrero::FastColor& thatColor)
    {
        if (colorHandler)
            colorHandler->SetColor(thisColor, thatColor);
    }

    void WhackerHandler::SetSize(float width, float length)
    {
        get_transform()->set_localScale({width, width, length});
    }

    void WhackerHandler::set_ColorHandler(WhackerColorHandler* colorHandler) { this->colorHandler = colorHandler; }
    WhackerColorHandler* WhackerHandler::get_ColorHandler() const { return colorHandler; }

    void WhackerHandler::set_SaberType(GlobalNamespace::SaberType saberType) { this->saberType = saberType; }
    GlobalNamespace::SaberType WhackerHandler::get_SaberType() const { return saberType; }

    ArrayW<TrailHandler*> WhackerHandler::get_TrailHandlers() const { return trailHandlers; }
    void WhackerHandler::set_TrailHandlers(ArrayW<TrailHandler*> trailHandlers) { this->trailHandlers = trailHandlers; }
    ArrayW<TrailTransform*> WhackerHandler::get_TrailTransforms() const { return trailTransforms; }
    void WhackerHandler::set_TrailTransforms(ArrayW<TrailTransform*> trailTransforms) { this->trailTransforms = trailTransforms; }

}
