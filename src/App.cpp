//#include "App.hpp"
//
//#include "Util/Image.hpp"
//#include "Util/Input.hpp"
//#include "Util/Keycode.hpp"
//#include "Util/Logger.hpp"
//
//void App::Start() {
//    LOG_TRACE("Start");
//    LOG_DEBUG("Start");
//    m_CurrentState = State::UPDATE;
//}
//
//void App::Update() {
//
//    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
//        m_CurrentState = State::END;
//    }
//
//    if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
//        ValidTask();
//    }
//
//    m_Root.Update();
//}
//
//void App::End() {
//    LOG_TRACE("End");
//}
