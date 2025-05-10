#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::Start() {
    LOG_TRACE("Start");
	//std::cout << "Start" << std::endl;
    
    /* Phase Resource Manager */
    m_PRM = std::make_shared<PhaseResourceManager>();
    m_Root.AddChildren(m_PRM->GetChildren());

    /* BGM */


    // 初始化剩餘步數
    m_RemainingSteps = 100;
    m_PRM->GetRemainingStepsText()->UpdatePosition(0.0F, 150.0F);
	m_PRM->GetRemainingStepsText()->SetVisible(false);
    m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));

    m_CurrentMaxLevel = 1; // 初始設定成已經解鎖第一關了

	// 初始化時間文字
	m_TimeText = std::make_shared<TaskText>(RESOURCE_DIR"/Font/BodoniFLF-Bold.ttf", 40, "剩餘時間: 00:10", Util::Color::FromName(Util::Colors::WHITE));
	m_TimeText->UpdatePosition(0.0F, -240.0F); // 放在螢幕上方中間
	m_TimeText->SetVisible(false);
	m_Root.AddChild(m_TimeText);
	
    m_CurrentState = State::UPDATE;
}