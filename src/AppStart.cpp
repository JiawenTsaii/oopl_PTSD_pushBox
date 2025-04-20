#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

//#include "InitializeMap.cpp"

void App::Start() {
    LOG_TRACE("Start");
	std::cout << "Start" << std::endl;
    
    /* Phase Resource Manager */
    m_PRM = std::make_shared<PhaseResourceManager>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentMaxLevel = 1; // 初始設定成已經解鎖第一關了

    m_CurrentState = State::UPDATE;
}