#include "PhaseResourceManager.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

PhaseResourceManager::PhaseResourceManager() {
    m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
	m_RemainingStepsText = std::make_shared<TaskText>(
		RESOURCE_DIR"/Font/BodoniFLF-Bold.ttf", // 字體路徑
		20,                                    // 字體大小
		"Remaining Steps: 100",                // 初始文字內容
		Util::Color::FromName(Util::Colors::BLACK) // 顏色
	);
}

void PhaseResourceManager::NextPhase() {
	// 如果正在轉到關卡選擇階段
	if (m_Phase == 0) {  // 假設0是從menu到level
		//std::cout << "CreateLevelBoxes()" << std::endl;
		CreateLevelBoxes();
	}

    //std::cout << "Now phase: " << m_Phase << std::endl;
    m_Phase++;
	//std::cout << "Next phase: " << m_Phase << std::endl;
}

void PhaseResourceManager::SetImage(const std::string& filepath) {
	m_Background->SetImage(filepath);
}

void PhaseResourceManager::SetTaskText(int TextLevel) {
	m_TaskText->NextPhase(TextLevel + 1);
}

void PhaseResourceManager::SetPassText() {
	m_TaskText->SetText("Level Complete!");
}

void PhaseResourceManager::SetRemainingStepsText(const std::string& remainingSteps) {
	m_RemainingStepsText->SetText("Remaining Steps: " + remainingSteps);
}

std::shared_ptr<TaskText> PhaseResourceManager::GetRemainingStepsText() const {
	return m_RemainingStepsText;
}

std::shared_ptr<TaskText> PhaseResourceManager::GetTaskText() const {
	return m_TaskText;
}

void PhaseResourceManager::AddNextLevelBox() {

	// 30個箱子都加進去了就不再加了
	if (m_AddedBoxCount >= MAX_BOXES) {
		return;
	}

	// 箱子編號從1開始
	int boxNumber = m_AddedBoxCount + 1;
	std::string boxImagePath = RESOURCE_DIR"/Object/LevelBox/b" + std::to_string(boxNumber) + ".png";
	//std::cout << "Loading image: " << boxImagePath << std::endl;

	auto box = std::make_shared<Character>(boxImagePath);
	box->SetZIndex(50);

	// 計算箱子位置（5x6）
	int row = (boxNumber - 1) / 5;
	int col = (boxNumber - 1) % 5;

	// 箱子的完美位置被我找到了 嗚呼
	// glm::vec2 position(-132 + col * 65.5, 150 - row * 65.5);
	// box->SetPosition(position);
	box->SetPosition({ -132 + col * 65.5, 150 - row * 65.5 });

	//std::cout << "Box " << boxNumber << " position: " << box->GetPosition().x << ", " << box->GetPosition().y << std::endl;

	m_LevelBoxes.push_back(box);
	// std::cout << "Adding box " << boxNumber << " to root node" << std::endl;
	m_pRoot.AddChild({ box });

	m_AddedBoxCount++;
	LOG_DEBUG("Added box {}, total boxes: {}", boxNumber, m_AddedBoxCount);
}

bool PhaseResourceManager::AreAllBoxesAdded() const {
	return m_AddedBoxCount >= MAX_BOXES;
}

void PhaseResourceManager::CreateLevelBoxes() {
	// 先清掉之前的箱子
	m_LevelBoxes.clear();
	m_AddedBoxCount = 0;
}

std::vector<std::shared_ptr<Character>> PhaseResourceManager::GetLevelBoxes() const {
	return m_LevelBoxes;
}


// // 關卡選擇的部分的箱子處理
void PhaseResourceManager::ShowLevelBoxes(bool visible) {
	for (auto& box : m_LevelBoxes) {
		box->SetVisible(visible);
	}
}


// 檢查是否所有箱子都已添加
bool PhaseResourceManager::AreAllBoxesAdded() {
	return m_LevelBoxes.size() >= 30;  // 總共有30個
}

// 檢查是否所有箱子都已顯示
bool PhaseResourceManager::AreAllBoxesVisible() {
	for (const auto& box : m_LevelBoxes) {
		if (!box->GetVisibility()) {
			return false;
		}
	}
	return true;
}

// 顯示下一個尚未顯示的箱子
void PhaseResourceManager::ShowNextLevelBox() {
	for (auto& box : m_LevelBoxes) {
		if (!box->GetVisibility()) {
			box->SetVisible(true);
			break;  // 顯示一個 然後退出
		}
	}
}