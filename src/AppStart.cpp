#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

//#include "InitializeMap.cpp"

void App::Start() {
    LOG_TRACE("Start");
	std::cout << "Start" << std::endl;
    
    /* Phase Resource Manager */
    m_PRM = std::make_shared<PhaseResourceManager>();
    m_Root.AddChildren(m_PRM->GetChildren());

    /* 目標點 */
    /* 0:草地 1:牆壁 2:空地 3:目標點 */
    /*int GoalMap[8][6] = {
        {1, 1, 1, 1, 1, 1},
        {1, 2, 3, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1}
    };*/

    // 原點在中間，所以左下角是(-180, -320)
	// 640-480=160，160/2=80，所以上下各空80
    // 第一個(左下角)箱子: (-150, -210)
	// SetPosition是設定中間的位置

    m_CurrentState = State::UPDATE;
}