//#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::ValidTask() {
	switch (m_Phase) {
		case Phase::MENU:
			//std::cout << "MENU to LEVEL" << std::endl;
			m_PRM->NextPhase();
			m_Phase = Phase::LEVEL;
			break;
		case Phase::LEVEL:
			m_PRM->SetImage(RESOURCE_DIR"/bg_level.png");
			break;
		default:
			m_CurrentState = State::END;
	}
}