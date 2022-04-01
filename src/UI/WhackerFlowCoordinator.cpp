#include "UI/WhackerFlowCoordinator.hpp"
#include "UI/PreviewViewController.hpp"
#include "UI/SelectionViewController.hpp"
#include "UI/SettingsViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "HMUI/TitleViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "qosmetics-core/shared/Utils/UIUtils.hpp"
DEFINE_TYPE(Qosmetics::Sabers, WhackerFlowCoordinator);

using namespace QuestUI::BeatSaberUI;

namespace Qosmetics::Sabers
{
    void WhackerFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            previewViewController = CreateViewController<Qosmetics::Sabers::PreviewViewController*>();
            settingsViewController = CreateViewController<Qosmetics::Sabers::SettingsViewController*>();
            reinterpret_cast<Qosmetics::Sabers::SettingsViewController*>(settingsViewController)->previewViewController = reinterpret_cast<Qosmetics::Sabers::PreviewViewController*>(previewViewController);
            selectionViewController = CreateViewController<Qosmetics::Sabers::SelectionViewController*>();
            reinterpret_cast<Qosmetics::Sabers::SelectionViewController*>(selectionViewController)->previewViewController = reinterpret_cast<Qosmetics::Sabers::PreviewViewController*>(previewViewController);
            ProvideInitialViewControllers(selectionViewController, settingsViewController, previewViewController, nullptr, nullptr);

            set_showBackButton(true);
            SetTitle("Whacker", HMUI::ViewController::AnimationType::In);
        }

        HMUI::TitleViewController* titleView = Object::FindObjectOfType<HMUI::TitleViewController*>();
        Qosmetics::Core::UIUtils::SetTitleColor(titleView, UnityEngine::Color::get_red());
    }

    void WhackerFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }

}