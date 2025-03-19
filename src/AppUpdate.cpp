#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
		// 記錄之前的phase
        Phase prevPhase = m_Phase;

        // 根據不同階段處理enter
        switch (m_Phase) {
        case Phase::MENU:
            // 從MENU到LEVEL
            ValidTask();
            break;

        case Phase::LEVEL:
            // 在LEVEL 開始把箱子放進去
            if (!m_PRM->AreAllBoxesAdded()) {
                m_PRM->AddNextLevelBox();
                auto box = m_PRM->GetLevelBoxes().back();
                m_Root.AddChildren({ box });
            }
            else {
                // 箱子都加完就換到GAME
                // 這裡之後再改一下要怎麼進入GAME
                m_PRM->SetImage(RESOURCE_DIR"/game.png");
                m_Phase = Phase::GAME;
            }
            break;

        case Phase::GAME:
            // 在GAME裡面的東東
            break;

        default:
            break;
        }
    }

    m_Root.Update();
}

