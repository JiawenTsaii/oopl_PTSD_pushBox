#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::ValidTask() {
    switch (m_Phase) {
    case Phase::MENU:
        // MENU到LEVEL
        m_PRM->NextPhase(); // 用到CreateLevelBoxes 但還不會把箱子放進去
        m_PRM->SetImage(RESOURCE_DIR"/bg_level.png"); // LEVEL的背景
        m_Phase = Phase::LEVEL;
        break;

    case Phase::LEVEL:
        // 先不要在這裡放箱子
        // 改成在Update裡面一個一個放進去感覺比較好
        break;

    case Phase::GAME:
        // 玩遊戲的部分
        break;

    default:
        m_CurrentState = State::END;
        break;
    }
}

