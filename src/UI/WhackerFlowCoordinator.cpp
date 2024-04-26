#include "UI/WhackerFlowCoordinator.hpp"
#include "UI/PreviewViewController.hpp"
#include "UI/SelectionViewController.hpp"
#include "UI/SettingsViewController.hpp"

#include "HMUI/TitleViewController.hpp"

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
    }

    void WhackerFlowCoordinator::Awake()
    {
        inActiveSprite = BSML::Utilities::LoadSpriteRaw(Assets::Icons::SaberIcon_png);
        activeSprite = BSML::Utilities::LoadSpriteRaw(Assets::Icons::SaberIconSelected_png);
    }

    void WhackerFlowCoordinator::Inject(PreviewViewController* previewViewController, SelectionViewController* selectionViewController, SettingsViewController* settingsViewController)
    {
        this->previewViewController = previewViewController;
        this->selectionViewController = selectionViewController;
        this->settingsViewController = settingsViewController;
    }

    void WhackerFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        HMUI::TitleViewController* titleView = Object::FindObjectOfType<HMUI::TitleViewController*>();
        if (firstActivation)
        {
            ProvideInitialViewControllers(selectionViewController, settingsViewController, previewViewController, nullptr, nullptr);

            set_showBackButton(true);
            SetTitle("Whacker", HMUI::ViewController::AnimationType::In);

            if (Qosmetics::Core::DateUtils::isMonth(6))
            {
                titleGradientUpdater = get_gameObject()->AddComponent<BSML::TextGradientUpdater*>();
                titleGradientUpdater->set_gradient(BSML::Gradient::Parse(Qosmetics::Core::RainbowUtils::randomGradient()));
                titleGradientUpdater->text = titleView->_text;
                titleGradientUpdater->scrollSpeed = 0.2;
                titleGradientUpdater->fixedStep = true;
                titleGradientUpdater->stepSize = 2;
            }
        }

        if (titleGradientUpdater && titleGradientUpdater->m_CachedPtr)
            titleGradientUpdater->set_enabled(true);

        Qosmetics::Core::UIUtils::SetTitleColor(titleView, UnityEngine::Color::get_red());
    }

    void WhackerFlowCoordinator::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
    {
        if (!titleGradientUpdater || !titleGradientUpdater->m_CachedPtr)
            return;
        titleGradientUpdater->set_enabled(false);
    }

    void WhackerFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        this->_parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }

}
