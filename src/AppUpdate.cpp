#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    // �˴�Enter�䪺���U�A���קK����Ĳ�o
    bool enterKeyCurrentlyPressed = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

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
            // �bLEVEL �}�l��c�l��i�h
            if (!m_PRM->AreAllBoxesAdded()) {
                m_PRM->AddNextLevelBox();
                auto box = m_PRM->GetLevelBoxes().back();
                m_Root.AddChildren({ box });
            }
            else {
                // �c�l���[���N����GAME
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

    // ��sEnter�䪬�A
    m_EnterKeyWasPressed = enterKeyCurrentlyPressed;

    m_Root.Update();
}


// �ƹ����I���ާ@�MŪ���n�Ψ쪺�귽��Util::Input::IsMousePressed()�MUtil::Input::GetMousePosition()
// �٦�Util::Input::IsKeyPressed()�MUtil::Input::GetKeycode()
// Util::Input::IfExit() �o�ӬO�ΨӧP�_�O�_�n���}�� �o�ӬO�bAppUpdate.cpp�̭���Update()�̭��Ψ쪺
// �W�����쪺��ƹ���������Ƴ��O�bUtil/Input.hpp�̭��� �i�H�Ѧ�Util/Input.hpp�̭�������
// ���OIsMousePressed()�o�Ө�ƬO�ΨӧP�_�ƹ��O�_�Q���U��
// GetMousePosition()�o�Ө�ƬO�ΨӨ��o�ƹ�����m��
// IsKeyPressed()�o�Ө�ƬO�ΨӧP�_��L�O�_�Q���U��
// GetKeycode()�o�Ө�ƬO�ΨӨ��o��L�����䪺
// IfExit()�o�Ө�ƬO�ΨӧP�_�O�_�n���}��