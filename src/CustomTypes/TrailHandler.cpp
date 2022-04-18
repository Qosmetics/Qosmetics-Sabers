#include "CustomTypes/TrailHandler.hpp"
#include "ConstStrings.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Text.hpp"
#include "config.hpp"
#include "logging.hpp"

DEFINE_TYPE(Qosmetics::Sabers, TrailHandler);

namespace Qosmetics::Sabers
{
    void TrailHandler::InitData()
    {
        trail = GetComponent<TrailComponent*>();
        auto text = GetComponent<UnityEngine::UI::Text*>();
        rapidjson::Document doc;
        doc.Parse(text->get_text());
        DEBUG("Trail Component info: {}", text->get_text());
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
        auto& config = Config::get_config();

        auto renderer = GetComponent<UnityEngine::Renderer*>();
        auto material = renderer ? renderer->get_material() : nullptr;

        if (trail)
        {
            // 3 + length or overridelength due to length 0, 1, 2, 3 being invisible,
            // and == 0 crashing, this solved it really easily and doesn't take away from the user experience so hurray for sneaky ways of fixing things
            TrailInitData trailInitData(3 + (config.overrideTrailLength ? config.trailLength : length),
                                        config.overrideWhiteStep ? float(config.whiteStep) : whiteStep,
                                        (config.whiteTrail ? Sombrero::FastColor::white() : trailColor) * multiplierColor);
            trail->Setup(trailInitData,
                         config.overrideTrailWidth ? get_customBotTransform() : get_botTransform(),
                         get_topTransform(),
                         material,
                         false);
        }
        else
            ERROR("No trail component found for TrailHandler with ID {}!", trailId);
    }

    void TrailHandler::SetColor(const Sombrero::FastColor& leftColor, const Sombrero::FastColor& rightColor)
    {
        if (Config::get_config().whiteTrail)
            return;
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

    UnityEngine::Transform* TrailHandler::get_topTransform()
    {
        if (topTransform)
            return topTransform;
        INFO("topTransform NOT set, creating it");

        topTransform = UnityEngine::GameObject::New_ctor(ConstStrings::TrailEnd())->get_transform();
        topTransform->SetParent(get_transform(), false);
        topTransform->set_localPosition({0.0f, 0.0f, 1.0f});

        return topTransform;
    }

    UnityEngine::Transform* TrailHandler::get_botTransform()
    {
        if (botTransform)
            return botTransform;
        INFO("botTransform NOT set, creating it");

        botTransform = UnityEngine::GameObject::New_ctor(ConstStrings::TrailStart())->get_transform();
        botTransform->SetParent(get_transform(), false);
        botTransform->set_localPosition({0.0f, 0.0f, 0.0f});

        return botTransform;
    }

    UnityEngine::Transform* TrailHandler::get_customBotTransform()
    {
        if (customBotTransform)
            return customBotTransform;
        INFO("customBotTransform NOT set, creating it");
        auto& config = Config::get_config();
        customBotTransform = UnityEngine::GameObject::New_ctor(ConstStrings::CustomTrailStart())->get_transform();
        customBotTransform->SetParent(get_transform(), false);

        auto topPos = get_topTransform()->get_position();
        auto botPos = get_botTransform()->get_position();

        DEBUG("Lerping between positions:\n\t{}, {}, {}\n\t{}, {}, {}", topPos.x, topPos.y, topPos.z, botPos.x, botPos.y, botPos.z);
        customBotTransform->set_position(Sombrero::FastVector3::Lerp(topPos, botPos, config.trailWidth));

        return customBotTransform;
    }

}