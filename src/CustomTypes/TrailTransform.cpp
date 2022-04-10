#include "CustomTypes/TrailTransform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Text.hpp"

#include "Trail/TrailPoint.hpp"

DEFINE_TYPE(Qosmetics::Sabers, TrailTransform);

namespace Qosmetics::Sabers
{
    void TrailTransform::Init()
    {
        auto text = get_gameObject()->GetComponent<UnityEngine::UI::Text*>();
        rapidjson::Document doc;
        doc.Parse(text->get_text());

        if (doc.GetParseError() == 0)
        {
            TrailPoint p(doc);
            trailId = p.trailId;
            isTop = p.get_isTop();
        }
    }

    bool TrailTransform::get_isTop()
    {
        return isTop;
    }
}