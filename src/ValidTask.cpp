#include "App.hpp"

#include "Util/Logger.hpp"

void App::ValidTask() {
	LOG_DEBUG("Validating the task {}", static_cast<int>(m_Phase));

	switch (m_Phase) {
		case Phase::MENU:
			LOG_INFO("MENU to LEVEL");

			m_Phase = Phase::LEVEL;
			

			break;
	}
}