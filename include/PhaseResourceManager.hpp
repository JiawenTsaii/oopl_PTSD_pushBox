#ifndef PHASE_MANAGER_HPP
#define PHASE_MANAGER_HPP

#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"

#include "Character.hpp"
#include "BackgroundImage.hpp"
#include "TaskText.hpp"

#include <memory>
#include <vector>
#include <string>

namespace Util {
	class GameObject;
}

class PhaseResourceManager {
public:
	PhaseResourceManager();

	[[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
		return { m_TaskText, m_Background, m_RemainingStepsText };
	}
	[[nodiscard]] std::vector<std::shared_ptr<Character>> GetLevelBoxes() const;

	void NextPhase();
	void SetImage(const std::string& filepath);
	void SetTaskText(int TextLevel);
	void SetPassText();
	void SetRemainingStepsText(const std::string& m_RemainingSteps);

	std::shared_ptr<TaskText> GetRemainingStepsText() const;
	std::shared_ptr<TaskText> GetTaskText() const;

	void CreateLevelBoxes();
	void AddNextLevelBox();
	bool AreAllBoxesAdded() const;

	// 關卡選擇的部分的箱子處理
	void ShowLevelBoxes(bool visible);

	// 檢查是否所有箱子都已添加
	bool AreAllBoxesAdded();
	// 檢查是否所有箱子都已顯示
	bool AreAllBoxesVisible();
	// 顯示下一個尚未顯示的箱子
	void ShowNextLevelBox();

private:
	std::shared_ptr<BackgroundImage> m_Background;
	std::shared_ptr<TaskText> m_TaskText;

	std::shared_ptr<TaskText> m_RemainingStepsText; // 用於顯示剩餘步數的 TaskText 物件

	std::vector<std::shared_ptr<Character>> m_LevelBoxes;

	Util::Renderer m_pRoot;
	int m_Phase = 0;    // 0: menu

	int m_AddedBoxCount = 0;
	static const int MAX_BOXES = 30;

	// 關卡選擇的部分的箱子處理
	std::chrono::time_point<std::chrono::system_clock> m_HighlightStartTime;
	int m_HighlightedBoxIndex = -1;
	bool m_IsHighlighting = false;
	glm::vec2 m_OriginalBoxSize;

	int m_VisibleBoxCount = 0;
};

#endif //PHASE_MANGER_HPP