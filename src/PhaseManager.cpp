#include "PhaseResourceManager.hpp"

#include "Util/Logger.hpp"

#include <iostream>

PhaseResourceManager::PhaseResourceManager() {
    std::cout << "Initializing PhaseResourceManager" << std::endl;
    //m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
}

void PhaseResourceManager::NextPhase() {
    if (m_Phase == 7) return;
    LOG_DEBUG("Passed! Next phase: {}", m_Phase);
	if (m_Phase != 0) {     // menu to level, not phase
        m_Background->NextPhase(m_Phase);
    }
    //m_TaskText->NextPhase(m_Phase);
    m_Phase++;
}

void PhaseResourceManager::SetImage(const std::string& filepath) {
	m_Background->SetImage(filepath);
}