#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::Start() {
    LOG_TRACE("Start");
	std::cout << "Start" << std::endl;
    
    /* Phase Resource Manager */
    m_PRM = std::make_shared<PhaseResourceManager>();
    m_Root.AddChildren(m_PRM->GetChildren());

    // 初始化剩餘步數
    m_RemainingSteps = 100;
    m_PRM->GetRemainingStepsText()->UpdatePosition(0.0F, -250.0F);
	m_PRM->GetRemainingStepsText()->SetVisible(false);
    m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));

    m_CurrentMaxLevel = 1; // 初始設定成已經解鎖第一關了

    m_CurrentState = State::UPDATE;
}