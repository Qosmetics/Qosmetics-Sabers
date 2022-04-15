#include "CustomTypes/SaberModelController.hpp"
#include "ConstStrings.hpp"
#include "CustomTypes/SaberModelContainer.hpp"
#include "CustomTypes/WhackerHandler.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/MeshFilter.hpp"

#include "sombrero/shared/FastColor.hpp"
#include "sombrero/shared/FastQuaternion.hpp"

#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/SaberTrail.hpp"
#include "GlobalNamespace/SaberTrailRenderer.hpp"
#include "GlobalNamespace/SaberType.hpp"

DEFINE_TYPE(Qosmetics::Sabers, SaberModelController);

namespace Qosmetics::Sabers
{
    void SaberModelController::Init(GlobalNamespace::Saber* saber)
    {
        this->saber = saber;
        auto saberModelContainer = SaberModelContainer::get_instance();
        auto config = saberModelContainer->GetSaberConfig();
        auto globalConfig = Config::get_config();
        int saberType = saber->get_saberType().value;

        if (!saberModelContainer || !saberModelContainer->currentSaberObject)
        {
            EditDefaultSaber();
            return;
        }

        StringW saberName(saberType == 0 ? ConstStrings::LeftSaber() : ConstStrings::RightSaber());

        auto prefab = saberModelContainer->currentSaberObject->get_transform()->Find(saberName);

        /// TODO: should this be get_transform or get parent?
        auto customSaber = UnityEngine::Object::Instantiate(prefab->get_gameObject(), get_transform()->get_parent());
        auto customSaberT = customSaber->get_transform();

        customSaberT->set_localPosition(Sombrero::FastVector3::zero());
        customSaberT->set_localScale(Sombrero::FastVector3(globalConfig.saberWidth, globalConfig.saberWidth, 1.0f));
        customSaberT->set_localRotation(Sombrero::FastQuaternion::identity());

        // custom saber object instantiated! clean up default saber now
        HideDefaultSaberElements();

        // Make sure all the components on the custom saber are inited
        auto whackerHandlers = customSaber->GetComponentsInChildren<WhackerHandler*>(true);
        Sombrero::FastColor thisColor(colorManager->ColorForSaberType(saberType));
        Sombrero::FastColor thatColor(colorManager->ColorForSaberType(1 - saberType));
        for (auto handler : whackerHandlers)
        {
            handler->SetupTrails();
            handler->colorHandler = handler->get_gameObject()->GetComponentsInChildren<Qosmetics::Sabers::WhackerColorHandler*>().FirstOrDefault();
            handler->SetColor(thisColor, thatColor);
        }
    }

    void SaberModelController::HideDefaultSaberElements()
    {
        auto saberModelContainer = SaberModelContainer::get_instance();
        auto& config = saberModelContainer->GetSaberConfig();
        auto& globalConfig = Config::get_config();

        if (config.get_hasTrail())
        {
            DEBUG("Removing default trial");
            // TODO: hide default trail
            auto saberModelController = GetComponent<GlobalNamespace::SaberModelController*>();
            auto trail = saberModelController->dyn__saberTrail();
            trail->set_enabled(false);
            trail->dyn__trailRenderer()->set_enabled(false);
        }

        DEBUG("Removing default mesh objects");
        auto filters = get_gameObject()->GetComponentsInChildren<UnityEngine::MeshFilter*>(true);
        for (auto filter : filters)
        {
            auto filterGO = filter->get_gameObject();
            auto name = filterGO->get_name();
            if (config.get_keepFakeGlow() && (name == "FakeGlow0" || name == "FakeGlow1"))
                continue;
            filterGO->SetActive(false);
        }
    }
    void SaberModelController::EditDefaultSaber()
    {
    }
}