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

    // LEVEL處理輸入(看要跳到哪個關卡)
    // if (m_Phase == Phase::LEVEL) {
    //     if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) m_SelectedLevel = 1;
    //     else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) m_SelectedLevel = 2;
    //     else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_3)) m_SelectedLevel = 3;
    //     else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_4)) m_SelectedLevel = 4;
    //     else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_5)) m_SelectedLevel = 5;
    //     else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_6)) m_SelectedLevel = 6;
    //     else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_7)) m_SelectedLevel = 7;
    //     else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_8)) m_SelectedLevel = 8;
    //     else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_9)) m_SelectedLevel = 9;
    // }
        if (m_Phase == Phase::LEVELSELECT) {
        // 輸入的關卡對應鍵 1-30
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) m_SelectedLevel = 1;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) m_SelectedLevel = 2;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_3)) m_SelectedLevel = 3;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_4)) m_SelectedLevel = 4;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_5)) m_SelectedLevel = 5;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_6)) m_SelectedLevel = 6;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_7)) m_SelectedLevel = 7;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_8)) m_SelectedLevel = 8;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_9)) m_SelectedLevel = 9;
        else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_0)) m_SelectedLevel = 10;
        // 10-30要弄其他新的逻辑 所以這裡先暂时用组合键
        // 按Alt+1表示11，Alt+2表示12...
        else if (Util::Input::IsKeyPressed(Util::Keycode::LALT) || Util::Input::IsKeyPressed(Util::Keycode::RALT)) {
            if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) m_SelectedLevel = 11;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) m_SelectedLevel = 12;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_3)) m_SelectedLevel = 13;
            //  之後補上
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_9)) m_SelectedLevel = 19;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_0)) m_SelectedLevel = 20;
        }
        // 21~30
        else if (Util::Input::IsKeyPressed(Util::Keycode::LCTRL) || Util::Input::IsKeyPressed(Util::Keycode::RCTRL)) {
            if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) m_SelectedLevel = 21;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) m_SelectedLevel = 22;
            // 之後補上
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_0)) m_SelectedLevel = 30;
        }
    }



    // GAME 可以返回LEVELSELECT的輸入處理
    if (m_Phase != Phase::MENU || m_Phase != Phase::LEVELSELECT) {
        if (Util::Input::IsKeyPressed(Util::Keycode::BACKSPACE)) {

			// 回去LEVEL
            m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
            m_PRM->ShowLevelBoxes(true);  // 顯示箱子
            m_Phase = Phase::LEVELSELECT;
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
            // ValidTask();


            break;

        case Phase::LEVELSELECT:
            m_Phase = Phase::LEVELSELECT;
            m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
            m_PRM->ShowLevelBoxes(true);  // 顯示箱子

            // 30個箱子
            // 使用m_PRM的方法来添加箱子
            while (!m_PRM->AreAllBoxesAdded()) {
                m_PRM->AddNextLevelBox();
                auto box = m_PRM->GetLevelBoxes().back();
                m_Root.AddChildren({ box });
            }
            // 箱子還沒放完都可以繼續
            if (!m_PRM->AreAllBoxesAdded()) {
                m_PRM->AddNextLevelBox();
                auto box = m_PRM->GetLevelBoxes().back();
                m_Root.AddChildren({ box });
            }
			// 箱子放完了就換到關卡裡面
            else if (m_SelectedLevel >= 1 && m_SelectedLevel <= 30) {
                std::string gameBackground = RESOURCE_DIR"/Background/bg_game" + std::to_string(m_SelectedLevel) + ".png";
                m_PRM->SetImage(gameBackground);

                m_PRM->ShowLevelBoxes(false);
                m_Phase = Phase::LEVEL1;
                //m_TypedNumbers = "";
            }
            break;
        case Phase::GAME:
            // 在GAME裡面的東東
            break;
        // case Phase::LEVEL1:
        // case Phase::LEVEL2:
        default:
            break;
        }
    }

    // 更新Enter鍵狀態
    m_EnterKeyWasPressed = enterKeyCurrentlyPressed;



    static bool keyProcessed = false;
    bool needUpdate = false;

    if (m_Phase != Phase::MENU && m_Phase != Phase::LEVELSELECT) {
        m_PRM->ShowLevelBoxes(false);
        if (m_Player) {
            m_Player->SetVisible(true);
        }
        if (m_Box) {
            m_Box->SetVisible(true);
        }
        for (auto& wall : m_Wall) {
            wall->SetVisible(true);
        }
        for (auto& floor : m_Floor) {
            floor->SetVisible(true);
        }
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 6; j++) {
                    if (m_GameMap[i][j] == 4) {
                        if (i > 0 && m_GameMap[i - 1][j] == 2) { // 確保不超出邊界並且上面是空地
                            m_GameMap[i][j] = 2; // 將當前位置設為空地
                            m_GameMap[i - 1][j] = 4; // 將上面一格設為玩家
                            m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 60 });
                            needUpdate = true;
                        }
                        if (i > 0 && m_GameMap[i - 1][j] == 3) {
							if (i > 1 && m_GameMap[i - 2][j] == 2) { // 確保箱子不會超出邊界並且箱子上面是空地
								m_GameMap[i][j] = 2; // 將當前位置設為空地
								m_GameMap[i - 1][j] = 4; // 將上面一格設為玩家
								m_GameMap[i - 2][j] = 3; // 將箱子上面一格設為箱子
								m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 60 });
								m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y + 60 });
								needUpdate = true;
							}
                        }
                        break; // 找到玩家並移動後直接跳出內層迴圈
                    }
                }
                if (needUpdate) break; // 找到玩家並移動後直接跳出外層迴圈
            }
            keyProcessed = true;
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 6; j++) {
                    if (m_GameMap[i][j] == 4) {
                        if (i < 7 && m_GameMap[i + 1][j] == 2) { // 確保不超出邊界並且下面是空地
                            m_GameMap[i][j] = 2; // 將當前位置設為空地
                            m_GameMap[i + 1][j] = 4; // 將下面一格設為玩家
                            m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y - 60 });
                            needUpdate = true;
                        }
                        if (i < 7 && m_GameMap[i + 1][j] == 3) {
                            if (i < 6 && m_GameMap[i + 2][j] == 2) { // 確保箱子不會超出邊界並且箱子下面是空地
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_GameMap[i + 1][j] = 4; // 將下面一格設為玩家
                                m_GameMap[i + 2][j] = 3; // 將箱子下面一格設為箱子
                                m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y - 60 });
                                m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y - 60 });
                                needUpdate = true;
                            }
                        }
                        break; // 找到玩家並移動後直接跳出內層迴圈
                    }
                }
                if (needUpdate) break; // 找到玩家並移動後直接跳出外層迴圈
            }
            keyProcessed = true;
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 6; j++) {
                    if (m_GameMap[i][j] == 4) {
                        if (j > 0 && m_GameMap[i][j - 1] == 2) { // 確保不超出邊界並且左邊是空地
                            m_GameMap[i][j] = 2; // 將當前位置設為空地
                            m_GameMap[i][j - 1] = 4; // 將左邊一格設為玩家
                            m_Player->SetPosition({ m_Player->GetPosition().x - 60, m_Player->GetPosition().y });
                            needUpdate = true;
                        }
                        if (j > 0 && m_GameMap[i][j - 1] == 3) {
                            if (j > 1 && m_GameMap[i][j - 2] == 2) { // 確保箱子不會超出邊界並且箱子左邊是空地
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_GameMap[i][j - 1] = 4; // 將左邊一格設為玩家
                                m_GameMap[i][j - 2] = 3; // 將箱子左邊一格設為箱子
                                m_Player->SetPosition({ m_Player->GetPosition().x - 60, m_Player->GetPosition().y });
                                m_Box->SetPosition({ m_Box->GetPosition().x - 60, m_Box->GetPosition().y });
                                needUpdate = true;
                            }
                        }
                        break; // 找到玩家並移動後直接跳出內層迴圈
                    }
                }
                if (needUpdate) break; // 找到玩家並移動後直接跳出外層迴圈
            }
            keyProcessed = true;
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 6; j++) {
                    if (m_GameMap[i][j] == 4) {
                        if (j < 5 && m_GameMap[i][j + 1] == 2) { // 確保不超出邊界並且右邊是空地
                            m_GameMap[i][j] = 2; // 將當前位置設為空地
                            m_GameMap[i][j + 1] = 4; // 將右邊一格設為玩家
                            m_Player->SetPosition({ m_Player->GetPosition().x + 60, m_Player->GetPosition().y });
                            needUpdate = true;
                        }
                        if (j < 5 && m_GameMap[i][j + 1] == 3) {
							if (j < 4 && m_GameMap[i][j + 2] == 2) { // 確保箱子不會超出邊界並且箱子右邊是空地
								m_GameMap[i][j] = 2; // 將當前位置設為空地
								m_GameMap[i][j + 1] = 4; // 將右邊一格設為玩家
								m_GameMap[i][j + 2] = 3; // 將箱子右邊一格設為箱子
								m_Player->SetPosition({ m_Player->GetPosition().x + 60, m_Player->GetPosition().y });
								m_Box->SetPosition({ m_Box->GetPosition().x + 60, m_Box->GetPosition().y });
								needUpdate = true;
							}
                        }
                        break; // 找到玩家並移動後直接跳出內層迴圈
                    }
                }
                if (needUpdate) break; // 找到玩家並移動後直接跳出外層迴圈
            }
            keyProcessed = true;
        }
    }
    else {
        keyProcessed = false; // 如果沒有按下任何方向鍵，重置 keyProcessed 標誌
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RETURN) && !m_PhaseChanged) {
		std::cout << "RETURN" << std::endl;
        ValidTask();
	}

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }



    m_Root.Update();

    if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        m_PhaseChanged = false;
    }
}


