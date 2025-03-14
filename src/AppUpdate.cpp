#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        // �O�����e�����q
        Phase prevPhase = m_Phase;
        ValidTask();

        // �p�G�qMENU�i�J�FLEVEL���q�A�ݭn����òK�[�c�l
        if (prevPhase == Phase::MENU && m_Phase == Phase::LEVEL) {
            // ����òK�[�Ҧ����d�c�l
            auto levelBoxes = m_PRM->GetLevelBoxes();
            std::cout << "Adding " << levelBoxes.size() << " level boxes to render system" << std::endl;

            for (const auto& box : levelBoxes) {
                m_Root.AddChildren({ box });
            }
        }
    }

    m_Root.Update();
}