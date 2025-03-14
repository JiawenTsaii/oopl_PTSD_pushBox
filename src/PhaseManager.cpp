#include "PhaseResourceManager.hpp"
#include "Util/Logger.hpp"
#include <iostream>

PhaseResourceManager::PhaseResourceManager(){
    std::cout << "Initializing PhaseResourceManager" << std::endl;
    m_Background = std::make_shared<BackgroundImage>();
}

void PhaseResourceManager::NextPhase(){
    if (m_Phase == 7) return;
    LOG_DEBUG("Passed! Next phase: {}", m_Phase);
    if (m_Phase != 0) {
        m_Background->NextPhase(m_Phase);
    }
    // 如果正在轉到關卡選擇階段
    if (m_Phase == 0) {  // 假設0是從menu到level
        CreateLevelBoxes();
    }
    m_Phase++;
}

void PhaseResourceManager::SetImage(const std::string& filepath) {
    m_Background->SetImage(filepath);
}

void PhaseResourceManager::CreateLevelBoxes() {
    // 清除之前的箱子
    m_LevelBoxes.clear();

    std::cout << "Creating level boxes..." << std::endl;
    LOG_DEBUG("Creating level boxes...");

    // 創30個箱子
    for (int i = 30; i >= 1; i--) {
        std::string boxImagePath = RESOURCE_DIR"/b" + std::to_string(i) + ".png";
        std::cout << "Loading image: " << boxImagePath << std::endl;

        auto box = std::make_shared<Character>(boxImagePath);
        box->SetZIndex(50);
        // 計算箱子位置（5x6）
        int row = (i - 1) / 5;
        int col = (i - 1) % 5;

        // 箱子的完美位置被我找到了 嗚呼
        glm::vec2 position(-132 + col * 65.5, 150 - row * 65.5);
        box->SetPosition(position);
        std::cout << "Box " << i << " position: " << position.x << ", " << position.y << std::endl;
        m_LevelBoxes.push_back(box);
        std::cout << "Adding box " << i << " to root node" << std::endl;
        m_pRoot.AddChild({ box });
    }

    std::cout << "Created " << m_LevelBoxes.size() << " level boxes" << std::endl;
    LOG_DEBUG("Created {} level boxes", m_LevelBoxes.size());
}

std::vector<std::shared_ptr<Character>> PhaseResourceManager::GetLevelBoxes() const {
    return m_LevelBoxes;
}