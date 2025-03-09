#include "pch.hpp"
#include "Util/Image.hpp"

#include "PhaseMenu.hpp"
#include "Character.hpp"

PhaseMenu::PhaseMenu() {
    auto background = std::make_shared<Character>();
    background->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/bg_menu.png"));
    background->SetZIndex(0.0f);
    m_Root.AddChild(background);
}

void PhaseMenu::Update() {
    m_Root.Update();
}
