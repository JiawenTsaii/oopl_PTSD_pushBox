#ifndef PHASE_RESOURCE_MANAGER_HPP
#define PHASE_RESOURCE_MANAGER_HPP

#include "Util/GameObject.hpp"
#include "Character.hpp"
#include "BackgroundImage.hpp"
#include "Phase.hpp"
#include <vector>
#include <memory>

class PhaseResourceManager {
public:
	PhaseResourceManager();

	[[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
		// 回傳所有 GameObject (包含背景和箱子)
		std::vector<std::shared_ptr<Util::GameObject>> children = { m_Background };
		children.insert(children.end(), m_Boxes.begin(), m_Boxes.end());
		return children;
	}

	void NextPhase();
	void SetImage(const std::string& filepath);
	void AddBox();  // AddBox是用來增加箱子的功能

private:
	std::shared_ptr<BackgroundImage> m_Background;
	std::vector<std::shared_ptr<Character>> m_Boxes; // 用來放箱子的vector
	int m_BoxCount = 0;	// 記錄箱子有幾個了 (最多30
	int m_Phase = 0;	// 0的時候是menu
};

#endif //PHASE_RESOURCE_MANAGER_HPP



//#ifndef PHASE_MANAGER_HPP
//#define PHASE_MANAGER_HPP
//
//#include "Util/GameObject.hpp"
//#include "Character.hpp"
//#include "BackgroundImage.hpp"
//#include "TaskText.hpp"
//#include "Phase.hpp"
//#include <memory>
//
//class PhaseResourceManager {
//public:
//	PhaseResourceManager();
//
//	[[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
//		//return { m_TaskText, m_Background };
//		return { m_Background };
//	}
//
//	void NextPhase();
//	void SetImage(const std::string& filepath);
//
//private:
//	std::shared_ptr<BackgroundImage> m_Background;
//	//std::shared_ptr<TaskText> m_TaskText;
//
//	int m_Phase = 0;	// 0: menu
//};
//
//#endif //PHASE_MANGER_HPP
