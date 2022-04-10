#include "CustomTypes/TrailHandler.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Text.hpp"

DEFINE_TYPE(Qosmetics::Sabers, TrailHandler);

namespace Qosmetics::Sabers
{
    void TrailHandler::InitData()
    {
        trail = GetComponent<TrailComponent*>();
        auto text = get_gameObject()->GetComponent<UnityEngine::UI::Text*>();
        rapidjson::Document doc;
        doc.Parse(text->get_text());
        if (doc.GetParseError() == 0)
        {
            TrailData p(doc);
            trailId = p.trailId;
            length = p.length;
            whiteStep = p.whiteStep;
            trailColor = p.trailColor;
            multiplierColor = p.multiplierColor;
            colorType = p.colorType;
        }
    }

    void TrailHandler::InitTrail()
    {
        // TODO: Implement override properly
        trail->Setup({length, whiteStep, trailColor * multiplierColor}, botTransform, topTransform, GetComponent<UnityEngine::Renderer*>()->get_material(), false);
    }

    void TrailHandler::SetColor(const Sombrero::FastColor& leftColor, const Sombrero::FastColor& rightColor)
    {
        switch (colorType)
        {
        case 0:
            trail->SetColor(leftColor * multiplierColor);
            break;
        case 1:
            trail->SetColor(rightColor * multiplierColor);
            break;
        case 2:
        default:
            trail->SetColor(multiplierColor * multiplierColor);
            break;
        }
    }
}