#ifndef PHASE_MANAGER_HPP
#define PHASE_MANAGER_HPP

#include "Util/GameObject.hpp"
#include "Character.hpp"
#include "BackgroundImage.hpp"
#include "TaskText.hpp"

class PhaseResourceManager {
public:
	PhaseResourceManager();

	[[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
		//return { m_TaskText, m_Background };
		return { m_Background };
	}

	void NextPhase();
	void SetImage(const std::string& filepath);

private:
	std::shared_ptr<BackgroundImage> m_Background;
	//std::shared_ptr<TaskText> m_TaskText;

	int m_Phase = 0;	// 0: menu
};

#endif //PHASE_MANGER_HPP