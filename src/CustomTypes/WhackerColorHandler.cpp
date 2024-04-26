#include "CustomTypes/WhackerColorHandler.hpp"
#include "MaterialUtils.hpp"
#include "PropertyID.hpp"
#include "logging.hpp"

#include "UnityEngine/Renderer.hpp"

DEFINE_TYPE(Qosmetics::Sabers, WhackerColorHandler);

namespace Qosmetics::Sabers
{
    void WhackerColorHandler::Awake()
    {
        FetchCCMaterials();
    }

    void WhackerColorHandler::SetColor(const Sombrero::FastColor& thisColor, const Sombrero::FastColor& thatColor)
    {
        if (lastThisColor.operator==(thisColor) && lastThatColor.operator==(thatColor))
            return;

        DEBUG("{}: setting colors!", fmt::ptr(this));
        DEBUG("thisColor: {:.2f}, {:.2f}, {:.2f}, {:.2f}", thisColor.r, thisColor.g, thisColor.b, thisColor.a);
        DEBUG("thatColor: {:.2f}, {:.2f}, {:.2f}, {:.2f}", thatColor.r, thatColor.g, thatColor.b, thatColor.a);

        lastThisColor = thisColor;
        lastThatColor = thatColor;

        for (auto* mat : customColorMaterials)
        {
            if (mat->HasProperty(PropertyID::_Color()))
                mat->SetColor(PropertyID::_Color(), thisColor);
            if (mat->HasProperty(PropertyID::_OtherColor()))
                mat->SetColor(PropertyID::_OtherColor(), thatColor);
        }
    }

    void WhackerColorHandler::FetchCCMaterials()
    {
        if (customColorMaterials)
            return;
        auto renderers = GetComponentsInChildren<UnityEngine::Renderer*>(true);

        std::vector<UnityEngine::Material*> customColorMaterialsVec = {};
        for (auto renderer : renderers)
        {
            auto materials = renderer->get_materials();
            for (auto material : materials)
            {
                // if CC material, add to CC vec
                if (MaterialUtils::ShouldCC(material))
                    customColorMaterialsVec.push_back(material);
            }
        }
        DEBUG("Found {} custom colors materials", customColorMaterialsVec.size());
        customColorMaterials = il2cpp_utils::vectorToArray(customColorMaterialsVec);
    }

    Sombrero::FastColor WhackerColorHandler::get_LastThisColor() { return lastThisColor; }

    Sombrero::FastColor WhackerColorHandler::get_LastThatColor() { return lastThatColor; }
}
