//#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::ValidTask() {
	if (!m_PhaseChanged) {
		switch (m_Phase) {
			case Phase::MENU:
				std::cout << "MENU to LEVEL" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
				m_PRM->NextPhase(); // 用到CreateLevelBoxes 但還不會把箱子放進去
				m_Phase = Phase::LEVELSELECT;
				m_PhaseChanged = true;
				break;
			case Phase::LEVELSELECT:
				std::cout << "LEVEL to LEVEL1" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL1;
				InitializeMap(GameMap1);
				m_PhaseChanged = true;
				break;
			case Phase::LEVEL1:
				std::cout << "LEVEL1 to LEVEL2" << std::endl;
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL2;
				InitializeMap(GameMap2);
				m_PhaseChanged = true;
				break;
			default:
				m_CurrentState = State::END;
				break;
		}
	}
}