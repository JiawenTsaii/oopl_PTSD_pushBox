#include "App.hpp"
#include "Util/Logger.hpp"
#include <iostream>
#include "Util/Renderer.hpp"

void App::Start() {
    LOG_TRACE("Start");
    std::cout << "Start" << std::endl;

    m_PRM = std::make_shared<PhaseResourceManager>();
    // ­I´ºªì©l¸ê·½
    m_Root.AddChildren(m_PRM->GetChildren());
    m_CurrentState = State::UPDATE;
}