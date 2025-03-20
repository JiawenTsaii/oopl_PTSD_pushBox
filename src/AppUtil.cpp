#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::ValidTask() {
    switch (m_Phase) {
    case Phase::MENU:
        // MENU��LEVEL
        m_PRM->NextPhase(); // �Ψ�CreateLevelBoxes ���٤��|��c�l��i�h
        m_PRM->SetImage(RESOURCE_DIR"/bg_level.png"); // LEVEL���I��
        m_Phase = Phase::LEVEL;
        break;

    case Phase::LEVEL:
        // �����n�b�o�̩�c�l
        // �令�bUpdate�̭��@�Ӥ@�ө�i�h�Pı����n
        break;

    case Phase::GAME:
        // ���C��������
        break;

    default:
        m_CurrentState = State::END;
        break;
    }
}

