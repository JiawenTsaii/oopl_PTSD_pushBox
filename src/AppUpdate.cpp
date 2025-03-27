#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>
//#include <chrono> // �o��ӳ��O���F�b������d���ɭԥi�H���c�l�i�H�Ȯɩ�j�X���F��
//#include <thread>

// Below are the keycodes handling mouse buttons.
// ��IsKeyPressed���˴��ƹ���O�_���U�򰻴���L������Τ@�˪��覡
// MOUSE_LB = 513,
// MOUSE_MB = 514,
// MOUSE_RB = 515,

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    // �˴�Enter�䪺���U�A���קK����Ĳ�o
    bool enterKeyCurrentlyPressed = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

    // LEVEL�B�z��J(�ݭn����������d)
    if (m_Phase == Phase::LEVEL) {
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) m_SelectedLevel = 1;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) m_SelectedLevel = 2;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_3)) m_SelectedLevel = 3;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_4)) m_SelectedLevel = 4;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_5)) m_SelectedLevel = 5;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_6)) m_SelectedLevel = 6;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_7)) m_SelectedLevel = 7;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_8)) m_SelectedLevel = 8;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_9)) m_SelectedLevel = 9;
    }

    // GAME �i�H��^LEVEL����J�B�z
    if (m_Phase == Phase::GAME) {
        if (Util::Input::IsKeyPressed(Util::Keycode::UP) ||
            Util::Input::IsKeyPressed(Util::Keycode::DOWN) ||
            Util::Input::IsKeyPressed(Util::Keycode::LEFT) ||
            Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {

			// �^�hLEVEL
            m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
            m_PRM->ShowLevelBoxes(true);  // ��ܽc�l
            m_Phase = Phase::LEVEL;
			m_SelectedLevel = 0;  // ������d�����k�s
        }
    }




    // �u����Enter��q�����U���A�ܬ����U���A�ɤ~����ʧ@
    if (enterKeyCurrentlyPressed && !m_EnterKeyWasPressed) {
        // �O�����e��phase
        Phase prevPhase = m_Phase;

        // �ھڤ��P���q�B�zenter
        switch (m_Phase) {
        case Phase::MENU:
            // �qMENU��LEVEL
            ValidTask();
            break;
        case Phase::LEVEL:
            // �c�l�٨S�񧹳��i�H�~��
            if (!m_PRM->AreAllBoxesAdded()) {
                m_PRM->AddNextLevelBox();
                auto box = m_PRM->GetLevelBoxes().back();
                m_Root.AddChildren({ box });
            }
			// �c�l�񧹤F�N����GAME
            else if (m_SelectedLevel >= 1 && m_SelectedLevel <= 30) {
                std::string gameBackground = RESOURCE_DIR"/Background/bg_game" + std::to_string(m_SelectedLevel) + ".png";
                m_PRM->SetImage(gameBackground);

                m_PRM->ShowLevelBoxes(false);

                m_Phase = Phase::GAME;
                //m_TypedNumbers = "";
            }
            break;
        case Phase::GAME:
            // �bGAME�̭����F�F
            break;
        default:
            break;
        }
    }

    // ��sEnter�䪬�A
    m_EnterKeyWasPressed = enterKeyCurrentlyPressed;
    //m_PRM->Update();

    m_Root.Update();
}


