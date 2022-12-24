#include "UI/WhackerFlowCoordinator.hpp"
#include "UI/PreviewViewController.hpp"
#include "UI/SelectionViewController.hpp"
#include "UI/SettingsViewController.hpp"

#include "HMUI/TitleViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "qosmetics-core/shared/Utils/DateUtils.hpp"
#include "qosmetics-core/shared/Utils/RainbowUtils.hpp"
#include "qosmetics-core/shared/Utils/UIUtils.hpp"

#include "bsml/shared/Helpers/utilities.hpp"

#include "assets.hpp"
#include "logging.hpp"

DEFINE_TYPE(Qosmetics::Sabers, WhackerFlowCoordinator);

namespace Qosmetics::Sabers
{
    void WhackerFlowCoordinator::ctor()
    {
        static auto baseKlass = classof(Qosmetics::Core::QosmeticsBaseFlowCoordinator*);
        custom_types::InvokeBaseCtor(baseKlass, this);

        name = "Whackers";
        inActiveSprite = BSML::Utilities::LoadSpriteRaw(IncludedAssets::SaberIcon_png);
        activeSprite = BSML::Utilities::LoadSpriteRaw(IncludedAssets::SaberIconSelected_png);
    }

    void WhackerFlowCoordinator::Inject(PreviewViewController* previewViewController, SelectionViewController* selectionViewController, SettingsViewController* settingsViewController)
    {
        this->previewViewController = previewViewController;
        this->selectionViewController = selectionViewController;
        this->settingsViewController = settingsViewController;
    }

    void WhackerFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            ProvideInitialViewControllers(selectionViewController, settingsViewController, previewViewController, nullptr, nullptr);

            set_showBackButton(true);
            SetTitle(Qosmetics::Core::DateUtils::isMonth(6) ? Qosmetics::Core::RainbowUtils::gayify("Whacker") : "Whacker", HMUI::ViewController::AnimationType::In);
        }

        HMUI::TitleViewController* titleView = Object::FindObjectOfType<HMUI::TitleViewController*>();
        Qosmetics::Core::UIUtils::SetTitleColor(titleView, UnityEngine::Color::get_red());
    }

    void WhackerFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }

}