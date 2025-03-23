#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

#include <iostream>

void App::Update() {

    static bool keyProcessed = false;

    bool needUpdate = false;

    if (m_Phase != Phase::MENU && m_Phase != Phase::LEVEL) {
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