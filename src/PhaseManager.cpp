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



void PhaseResourceManager::AddNextLevelBox() {
	// 30個箱子都加進去了就不再加了
    if (m_AddedBoxCount >= MAX_BOXES) {
        return;
    }

    // 箱子編號從1開始
    int boxNumber = m_AddedBoxCount + 1;
    std::string boxImagePath = RESOURCE_DIR"/b" + std::to_string(boxNumber) + ".png";
    std::cout << "Loading image: " << boxImagePath << std::endl;

    auto box = std::make_shared<Character>(boxImagePath);
    box->SetZIndex(50);

    // 計算箱子位置（5x6）
    int row = (boxNumber - 1) / 5;
    int col = (boxNumber - 1) % 5;

    // 箱子的完美位置被我找到了 嗚呼
    glm::vec2 position(-132 + col * 65.5, 150 - row * 65.5);
    box->SetPosition(position);

    std::cout << "Box " << boxNumber << " position: " << position.x << ", " << position.y << std::endl;

    m_LevelBoxes.push_back(box);
    std::cout << "Adding box " << boxNumber << " to root node" << std::endl;
    m_pRoot.AddChild({ box });

    m_AddedBoxCount++;
    LOG_DEBUG("Added box {}, total boxes: {}", boxNumber, m_AddedBoxCount);
}

bool PhaseResourceManager::AreAllBoxesAdded() const {
    return m_AddedBoxCount >= MAX_BOXES;
}

void PhaseResourceManager::CreateLevelBoxes() {
    // 清掉之前的箱子
    m_LevelBoxes.clear();
    m_AddedBoxCount = 0;
    std::cout << "Level boxes cleared, ready to add one by one" << std::endl;
    LOG_DEBUG("Level boxes cleared, ready to add one by one");
}

std::vector<std::shared_ptr<Character>> PhaseResourceManager::GetLevelBoxes() const {
    return m_LevelBoxes;
}




