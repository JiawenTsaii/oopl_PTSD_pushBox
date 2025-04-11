#include "App.hpp"
#include "Util/Logger.hpp"
#include <iostream>

// #include "InitializeMap.cpp"

void App::Start() {
    LOG_TRACE("Start");
	std::cout << "Start" << std::endl;

    /* Phase Resource Manager */
    m_PRM = std::make_shared<PhaseResourceManager>();
    // 背景初始資源
    m_Root.AddChildren(m_PRM->GetChildren());
    m_CurrentState = State::UPDATE;
}


