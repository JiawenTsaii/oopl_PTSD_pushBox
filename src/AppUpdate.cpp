#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
		// �O�����e��phase
        Phase prevPhase = m_Phase;

        // �ھڤ��P���q�B�zenter
        switch (m_Phase) {
        case Phase::MENU:
            // �qMENU��LEVEL
            ValidTask();
            break;

        case Phase::LEVEL:
            // �bLEVEL �}�l��c�l��i�h
            if (!m_PRM->AreAllBoxesAdded()) {
                m_PRM->AddNextLevelBox();
                auto box = m_PRM->GetLevelBoxes().back();
                m_Root.AddChildren({ box });
            }
            else {
                // �c�l���[���N����GAME
                // �o�̤���A��@�U�n���i�JGAME
                m_PRM->SetImage(RESOURCE_DIR"/game.png");
                m_Phase = Phase::GAME;
            }
            break;

        case Phase::GAME:
            // �bGAME�̭����F�F
            break;

        default:
            break;
        }
    }

    m_Root.Update();
}

