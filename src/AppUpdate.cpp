#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>
//#include <chrono> // 這兩個都是為了在選擇關卡的時候可以讓箱子可以暫時放大幾秒的東西
//#include <thread>

// Below are the keycodes handling mouse buttons.
// 用IsKeyPressed來檢測滑鼠鍵是否按下跟偵測鍵盤的按鍵用一樣的方式
// MOUSE_LB = 513,
// MOUSE_MB = 514,
// MOUSE_RB = 515,

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    // 檢測Enter鍵的按下，但避免重複觸發
    bool enterKeyCurrentlyPressed = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

    // LEVEL處理輸入(看要跳到哪個關卡)
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

    // GAME 可以返回LEVEL的輸入處理
    if (m_Phase == Phase::GAME) {
        if (Util::Input::IsKeyPressed(Util::Keycode::UP) ||
            Util::Input::IsKeyPressed(Util::Keycode::DOWN) ||
            Util::Input::IsKeyPressed(Util::Keycode::LEFT) ||
            Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {

			// 回去LEVEL
            m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
            m_PRM->ShowLevelBoxes(true);  // 顯示箱子
            m_Phase = Phase::LEVEL;
			m_SelectedLevel = 0;  // 選擇關卡的值歸零
        }
    }




    // 只有當Enter鍵從未按下狀態變為按下狀態時才執行動作
    if (enterKeyCurrentlyPressed && !m_EnterKeyWasPressed) {
        // 記錄之前的phase
        Phase prevPhase = m_Phase;

        // 根據不同階段處理enter
        switch (m_Phase) {
        case Phase::MENU:
            // 從MENU到LEVEL
            ValidTask();
            break;
        case Phase::LEVEL:
            // 箱子還沒放完都可以繼續
            if (!m_PRM->AreAllBoxesAdded()) {
                m_PRM->AddNextLevelBox();
                auto box = m_PRM->GetLevelBoxes().back();
                m_Root.AddChildren({ box });
            }
			// 箱子放完了就換到GAME
            else if (m_SelectedLevel >= 1 && m_SelectedLevel <= 30) {
                std::string gameBackground = RESOURCE_DIR"/Background/bg_game" + std::to_string(m_SelectedLevel) + ".png";
                m_PRM->SetImage(gameBackground);

                m_PRM->ShowLevelBoxes(false);

                m_Phase = Phase::GAME;
                //m_TypedNumbers = "";
            }
            break;
        case Phase::GAME:
            // 在GAME裡面的東東
            break;
        default:
            break;
        }
    }

    // 更新Enter鍵狀態
    m_EnterKeyWasPressed = enterKeyCurrentlyPressed;
    //m_PRM->Update();

    m_Root.Update();
}


