#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        // 記錄之前的階段
        Phase prevPhase = m_Phase;
        ValidTask();

        // 如果從MENU進入了LEVEL階段，需要獲取並添加箱子
        if (prevPhase == Phase::MENU && m_Phase == Phase::LEVEL) {
            // 獲取並添加所有關卡箱子
            auto levelBoxes = m_PRM->GetLevelBoxes();
            std::cout << "Adding " << levelBoxes.size() << " level boxes to render system" << std::endl;

            for (const auto& box : levelBoxes) {
                m_Root.AddChildren({ box });
            }
        }
    }

    m_Root.Update();
}