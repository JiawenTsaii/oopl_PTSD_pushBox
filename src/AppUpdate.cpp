#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
		ValidTask(); // 這裡是切換畫面的部分
    }
    
    
    m_Root.Update();
}


//void App::ValidTask() {
//	switch (m_Phase) {
//	case Phase::MENU:
//		m_PRM->NextPhase();
//		m_Phase = Phase::LEVEL;
//		break;
//	case Phase::LEVEL:
//		m_PRM->SetImage(RESOURCE_DIR"/bg_level_new.png");
//		break;
//	default:
//		m_CurrentState = State::END;
//	}
//}