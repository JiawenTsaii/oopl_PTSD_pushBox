#include "App.hpp"
#include "PhaseLevel.hpp"
#include "Util/Logger.hpp"

//void App::ValidTask() {
//	LOG_DEBUG("Validating the task {}", static_cast<int>(m_Phase));
//
//	switch (m_Phase) {
//		case Phase::MENU:
//			LOG_INFO("MENU to LEVEL");
//
//			m_Phase = Phase::LEVEL;
//			
//
//			break;
//	}
//}

void App::ValidTask() {
    switch (m_Phase) {
    case Phase::MENU:
        m_PRM->NextPhase();
        m_Phase = Phase::LEVEL;
        break;
    case Phase::LEVEL:
        // 讓現在的狀態(?)是在PhaseLevel
        if (auto level = std::dynamic_pointer_cast<PhaseLevel>(m_PRM->GetCurrentPhase())) {
            level->AddBox();
        }
        break;
    default:
        m_CurrentState = State::END;
    }
}
