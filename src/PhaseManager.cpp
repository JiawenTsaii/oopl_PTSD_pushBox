#include "PhaseResourceManager.hpp"

#include "Util/Logger.hpp"

#include <iostream>

PhaseResourceManager::PhaseResourceManager() {
    std::cout << "Initializing PhaseResourceManager" << std::endl;
    //m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
}

void PhaseResourceManager::NextPhase() {
	std::cout << "Now phase: " << m_Phase << std::endl;
    m_Phase++;
	std::cout << "Next phase: " << m_Phase << std::endl;
}

void PhaseResourceManager::SetImage(const std::string& filepath) {
	m_Background->SetImage(filepath);
}