#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

#include <iostream>

void App::Update() {

    if (m_Phase == Phase::LEVEL1 || m_Phase == Phase::LEVEL2) {
        if (m_Player) {
			//std::cout << "Player" << std::endl;
            m_Player->SetVisible(true);
        }
        if (m_Box) {
            //std::cout << "Box" << std::endl;
            m_Box->SetVisible(true);
        }
        for (auto& wall : m_Wall) {
            //std::cout << "Walls" << std::endl;
            wall->SetVisible(true);
        }
		for (auto& floor : m_Floor) {
            //std::cout << "Floors" << std::endl;
			floor->SetVisible(true);
		}
    }

    /* 動畫 */
    /* 如果上面有箱子就人和箱子一起動，否則人動 */
    /* 看一格的大小決定每次移動多少 */
    //m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 5 });
    //if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
    //    if (m_Player->IfCollides(m_Box)) {
    //        // m_Player和m_Box一起動
    //        for (int i = 0; i < 80; i++) {
    //            m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 1 });
    //            m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y + 1 });
    //        }
    //    }
    //    else {
    //        for (int i = 0; i < 80; i++) {
    //            m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 1 });
    //        }
    //        // m_Player移動一個箱子的距離
    //            // for迴圈，每次移動0.5或1，中間要有休息時間，才會像動畫
    //    }
    //}
    if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RETURN) && !m_PhaseChanged) {
		std::cout << "RETURN" << std::endl;
        ValidTask();
	}

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();

    if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        m_PhaseChanged = false;
    }
}