#include "CustomTypes/WhackerHandler.hpp"
#include "Trail/TrailInitData.hpp"

DEFINE_TYPE(Qosmetics::Sabers, WhackerHandler);

namespace Qosmetics::Sabers
{
    void WhackerHandler::SetupTrails()
    {
        trailHandlers = GetComponentsInChildren<TrailHandler*>();
        trailTransforms = GetComponentsInChildren<TrailTransform*>();
        for (auto t : trailTransforms)
            t->Init();

        for (auto handler : trailHandlers)
        {
            handler->InitData();
            TrailTransform *top = nullptr, *bot = nullptr;

            for (auto t : trailTransforms)
            {
                if (t->trailId == handler->trailId)
                {
                    if (t->get_isTop())
                        top = t;
                    else
                        bot = t;
                    if (top && bot)
                        break;
                }
            }

            handler->topTransform = top->get_transform();
            handler->botTransform = bot->get_transform();

            handler->InitTrail();
        }
    }

    void WhackerHandler::SetColor(const Sombrero::FastColor& thisColor, const Sombrero::FastColor& thatColor)
    {
        if (colorHandler)
            colorHandler->SetColor(thisColor, thatColor);
    }

    void WhackerHandler::SetSize(float width)
    {
        get_transform()->set_localScale({width, width, 1.0f});
    }
}