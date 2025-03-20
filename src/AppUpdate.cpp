#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    // 檢測Enter鍵的按下，但避免重複觸發
    bool enterKeyCurrentlyPressed = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

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
            // 在LEVEL 開始把箱子放進去
            if (!m_PRM->AreAllBoxesAdded()) {
                m_PRM->AddNextLevelBox();
                auto box = m_PRM->GetLevelBoxes().back();
                m_Root.AddChildren({ box });
            }
            else {
                // 箱子都加完就換到GAME
                m_PRM->SetImage(RESOURCE_DIR"/game.png");
                m_Phase = Phase::GAME;
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

    m_Root.Update();
}


// 滑鼠的點擊操作和讀取要用到的資源有Util::Input::IsMousePressed()和Util::Input::GetMousePosition()
// 還有Util::Input::IsKeyPressed()和Util::Input::GetKeycode()
// Util::Input::IfExit() 這個是用來判斷是否要離開的 這個是在AppUpdate.cpp裡面的Update()裡面用到的
// 上面提到的跟滑鼠有關的函數都是在Util/Input.hpp裡面的 可以參考Util/Input.hpp裡面的註解
// 像是IsMousePressed()這個函數是用來判斷滑鼠是否被按下的
// GetMousePosition()這個函數是用來取得滑鼠的位置的
// IsKeyPressed()這個函數是用來判斷鍵盤是否被按下的
// GetKeycode()這個函數是用來取得鍵盤的按鍵的
// IfExit()這個函數是用來判斷是否要離開的