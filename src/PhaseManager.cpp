#include "PhaseResourceManager.hpp"

#include "Util/Logger.hpp"
#include "Util/Image.hpp"
#include <iostream>

PhaseResourceManager::PhaseResourceManager() {
    std::cout << "Initializing PhaseResourceManager" << std::endl;
    m_Background = std::make_shared<BackgroundImage>();
}

void PhaseResourceManager::NextPhase() {
    if (m_Phase == 7) return;
    LOG_DEBUG("Passed! Next phase: {}", m_Phase);
    if (m_Phase != 0) {     // menu to level, not phase
        m_Background->NextPhase(m_Phase);
    }
    m_Phase++;
}

void PhaseResourceManager::SetImage(const std::string& filepath) {
    m_Background->SetImage(filepath);
}

void PhaseResourceManager::AddBox() {
    if (m_BoxCount >= 30) return;  // �̦h 30 �ӽc�l

    auto box = std::make_shared<Character>();
    std::string boxPath = RESOURCE_DIR "/b" + std::to_string(m_BoxCount + 1) + ".png";
    box->SetDrawable(std::make_shared<Util::Image>(boxPath));

    // �]�w�c�l��m
    float yOffset = m_BoxCount * 50.0f;  // ���]�w�����U��
    box->SetPosition({ 100.0f, 200.0f + yOffset });
    box->SetZIndex(1.0f + m_BoxCount * 0.1f);

    // ��c�l�[��Ϥ��W��
    m_Boxes.push_back(box);
    m_BoxCount++;
}




//#include "PhaseResourceManager.hpp"
//
//#include "Util/Logger.hpp"
//
//#include <iostream>
//
//PhaseResourceManager::PhaseResourceManager() {
//    std::cout << "Initializing PhaseResourceManager" << std::endl;
//    //m_TaskText = std::make_shared<TaskText>();
//    m_Background = std::make_shared<BackgroundImage>();
//}
//
//void PhaseResourceManager::NextPhase() {
//    if (m_Phase == 7) return;
//    LOG_DEBUG("Passed! Next phase: {}", m_Phase);
//	if (m_Phase != 0) {     // menu to level, not phase
//        m_Background->NextPhase(m_Phase);
//    }
//    //m_TaskText->NextPhase(m_Phase);
//    m_Phase++;
//}
//
//void PhaseResourceManager::SetImage(const std::string& filepath) {
//	m_Background->SetImage(filepath);
//}