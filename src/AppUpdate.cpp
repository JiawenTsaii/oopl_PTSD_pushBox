#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

#include <iostream>

void App::Update() {

    static bool keyProcessed = false;

    bool needUpdate = false;

    if (m_Phase != Phase::MENU && m_Phase != Phase::LEVEL) {
        if (m_Player) { // 人物
            m_Player->SetVisible(true);
        }
		if (m_Box) { // 箱子
            m_Box->SetVisible(true);
        }
		for (auto& wall : m_Wall) { // 牆壁
            wall->SetVisible(true);
        }
		for (auto& floor : m_Floor) { // 地板
            floor->SetVisible(true);
        }
		if (m_Point) { // 目標點
			m_Point->SetVisible(true);
		}
        // 勾勾(m_Check)先不要顯示
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 9; j++) {
                    /* 人 */
                    if (m_GameMap[i][j] == 4 || (isPlayerOnCheck && (i == m_PlayerPosition_i) && (j == m_PlayerPosition_j))) {
                        /* 人的上面是空地 */
                        if (m_GameMap[i - 1][j] == 2) {
                            if (!isPlayerOnCheck) {
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                            }
                            m_GameMap[i - 1][j] = 4; // 將上面一格設為玩家
                            m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 40 });
                            needUpdate = true;
                            isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                        }
						/* 人的上面是箱子 */
                        if (m_GameMap[i - 1][j] == 3 || (isBoxOnCheck && (i == m_BoxPosition_i) && (j == m_BoxPosition_j))) {
                            /* 箱子上面是空地 */
							if (m_GameMap[i - 2][j] == 2) { // 若玩家在目標點上，前進一格時不該將目標點改為空地
								if (!isPlayerOnCheck) { // 玩家不在目標點上
                                    m_GameMap[i][j] = 2; // 將當前位置設為空地
                                }
								m_GameMap[i - 1][j] = 4; // 將上面一格設為玩家
								m_GameMap[i - 2][j] = 3; // 將箱子上面一格設為箱子
								m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 40 });
								m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y + 40 });
								needUpdate = true;
                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                                isBoxOnCheck = false; // 更新箱子位置後重置標誌
                            }
                            /* 箱子上面是目標點 */
                            else if (m_GameMap[i - 2][j] == 5) {
                                m_Check->SetVisible(true);
								isBoxOnCheck = true; // 箱子在目標點上
								m_BoxPosition_i = i - 2; // i和j是人的位子，所以箱子差2
								m_BoxPosition_j = j;
								m_GameMap[i][j] = 2; // 將當前位置設為空地
								m_GameMap[i - 1][j] = 4; // 將上面一格設為玩家
                                m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y + 40 });
								m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 40 });
								needUpdate = true;
                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                            }
                        }
                        /* 人的上面是目標點 */
                        if (m_GameMap[i - 1][j] == 5) {
							isPlayerOnCheck = true; // 人在目標點上
							m_PlayerPosition_i = i - 1;
							m_PlayerPosition_j = j;
                            std::cout << "Player Position on Check: (" << m_PlayerPosition_i << ", " << m_PlayerPosition_j << ")" << std::endl; 
                            /* 目標點上有箱子*/
                            /* 人會在目標點上，箱子在目標點上面 */
                            if (isBoxOnCheck) {
								m_Check->SetVisible(false);
								m_GameMap[i][j] = 2; // 將當前位置設為空地
								m_GameMap[i - 2][j] = 3; // 將目標點上面一格設為箱子
								m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 40 });
								m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y + 40 });
                                isBoxOnCheck = false;
                                needUpdate = true;
                            }
                            /* 目標點上沒東西 */
                            else{
								m_GameMap[i][j] = 2; // 將當前位置設為空地
								m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y + 40 });
                                needUpdate = true;
                            }
                        }
                        break; // 找到玩家並移動後直接跳出內層迴圈
                    }
                }
                if (needUpdate) break; // 找到玩家並移動後直接跳出外層迴圈
            }

            for (const auto& row : m_GameMap) {
                for (const auto& cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            keyProcessed = true;
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 9; j++) {
                    /* 人 */
                    if (m_GameMap[i][j] == 4 || (isPlayerOnCheck && (i == m_PlayerPosition_i) && (j == m_PlayerPosition_j))) {
						/* 人的下面是空地 */
                        if (m_GameMap[i + 1][j] == 2) {
                            if (!isPlayerOnCheck) {
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                            }
                            m_GameMap[i + 1][j] = 4; // 將下面一格設為玩家
                            m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y - 40 });
                            needUpdate = true;
                            isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                        }
						/* 人的下面是箱子 */
                        if (m_GameMap[i + 1][j] == 3 || (isBoxOnCheck && (i == m_BoxPosition_i) && (j == m_BoxPosition_j))) {
							/* 箱子下面是空地 */
                            if (m_GameMap[i + 2][j] == 2) {
                                if (!isPlayerOnCheck) { // 玩家不在目標點上
                                    m_GameMap[i][j] = 2; // 將當前位置設為空地
                                }
                                m_GameMap[i + 1][j] = 4; // 將下面一格設為玩家
                                m_GameMap[i + 2][j] = 3; // 將箱子下面一格設為箱子
                                m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y - 40 });
                                m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y - 40 });
                                needUpdate = true;
                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                                isBoxOnCheck = false;
                            }
							/* 箱子下面是目標點 */
                            else if (m_GameMap[i + 2][j] == 5) {
                                isBoxOnCheck = true; // 箱子在目標點上
								m_BoxPosition_i = i + 2;
								m_BoxPosition_j = j;
                                m_Check->SetVisible(true);
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_GameMap[i + 1][j] = 4; // 將上面一格設為玩家
                                m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y - 40 });
                                m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y - 40 });
                                needUpdate = true;
                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                            }
                        }
                        /* 人的下面是目標點 */
                        if (m_GameMap[i + 1][j] == 5) {
                            isPlayerOnCheck = true;
                            m_PlayerPosition_i = i + 1;
                            m_PlayerPosition_j = j;
                            std::cout << "Player Position on Check: (" << m_PlayerPosition_i << ", " << m_PlayerPosition_j << ")" << std::endl;
                            /* 目標點上有箱子 */
                            if (isBoxOnCheck) {
                                m_Check->SetVisible(false);
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_GameMap[i + 2][j] = 3; // 將目標點下面一格設為箱子
                                m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y - 40 });
                                m_Box->SetPosition({ m_Box->GetPosition().x, m_Box->GetPosition().y - 40 });
                                isBoxOnCheck = false;
                                needUpdate = true;
                            }
                            /* 目標點上沒東西 */
                            else {
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_Player->SetPosition({ m_Player->GetPosition().x, m_Player->GetPosition().y - 40 });
                                needUpdate = true;
                            }
                        }
                        break; // 找到玩家並移動後直接跳出內層迴圈
                    }
                }
                if (needUpdate) break; // 找到玩家並移動後直接跳出外層迴圈
            }

            for (const auto& row : m_GameMap) {
                for (const auto& cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            keyProcessed = true;
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 9; j++) {
                    /* 人 */
                    if (m_GameMap[i][j] == 4 || (isPlayerOnCheck && (i == m_PlayerPosition_i) && (j == m_PlayerPosition_j))) {
                        /* 人的左邊是空地 */
                        if (m_GameMap[i][j - 1] == 2) {
                            if (!isPlayerOnCheck) {
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                            }
                            m_GameMap[i][j - 1] = 4; // 將左邊一格設為玩家
                            m_Player->SetPosition({ m_Player->GetPosition().x - 40, m_Player->GetPosition().y });
                            needUpdate = true;
                            isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                        }
						/* 人的左邊是箱子 */
                        if (m_GameMap[i][j - 1] == 3 || (isBoxOnCheck && (i == m_BoxPosition_i) && (j == m_BoxPosition_j))) {
                            /* 箱子左邊是空地 */
                            if (m_GameMap[i][j - 2] == 2) {
                                if (!isPlayerOnCheck) { // 玩家不在目標點上
                                    m_GameMap[i][j] = 2; // 將當前位置設為空地
                                }
                                m_GameMap[i][j - 1] = 4; // 將左邊一格設為玩家
                                m_GameMap[i][j - 2] = 3; // 將箱子左邊一格設為箱子
                                m_Player->SetPosition({ m_Player->GetPosition().x - 40, m_Player->GetPosition().y });
                                m_Box->SetPosition({ m_Box->GetPosition().x - 40, m_Box->GetPosition().y });
                                needUpdate = true;
                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                                isBoxOnCheck = false;
                            }
							/* 箱子左邊是目標點 */
                            else if (m_GameMap[i][j - 2] == 5) {
                                m_Check->SetVisible(true);
								isBoxOnCheck = true; // 箱子在目標點上
								m_BoxPosition_i = i;
								m_BoxPosition_j = j - 2;
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_GameMap[i][j - 1] = 4; // 將上面一格設為玩家
                                m_Box->SetPosition({ m_Box->GetPosition().x - 40, m_Box->GetPosition().y });
                                m_Player->SetPosition({ m_Player->GetPosition().x - 40, m_Player->GetPosition().y });
                                needUpdate = true;
                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                            }
                        }
                        /* 人的左邊是目標點 */
                        if (m_GameMap[i][j - 1] == 5) {
                            isPlayerOnCheck = true;
                            m_PlayerPosition_i = i;
                            m_PlayerPosition_j = j - 1;
                            std::cout << "Player Position on Check: (" << m_PlayerPosition_i << ", " << m_PlayerPosition_j << ")" << std::endl; 
                            /* 目標點上有箱子 */
                            if (isBoxOnCheck) {
                                m_Check->SetVisible(false);
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_GameMap[i][j - 2] = 3; // 將目標點左邊一格設為箱子
                                m_Player->SetPosition({ m_Player->GetPosition().x - 40, m_Player->GetPosition().y});
                                m_Box->SetPosition({ m_Box->GetPosition().x - 40, m_Box->GetPosition().y});
                                isBoxOnCheck = false;
                                needUpdate = true;
                            }
                            /* 目標點上沒東西 */
                            else {
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_Player->SetPosition({ m_Player->GetPosition().x - 40, m_Player->GetPosition().y});
                                needUpdate = true;
                            }
                        }
                        break; // 找到玩家並移動後直接跳出內層迴圈
                    }
                }
                if (needUpdate) break; // 找到玩家並移動後直接跳出外層迴圈
            }

            for (const auto& row : m_GameMap) {
                for (const auto& cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            keyProcessed = true;
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 9; j++) {
                    /* 人 */
                    if (m_GameMap[i][j] == 4 || (isPlayerOnCheck && (i == m_PlayerPosition_i) && (j == m_PlayerPosition_j))) {
						/* 人的右邊是空地 */
                        if (m_GameMap[i][j + 1] == 2) {
                            if (!isPlayerOnCheck) {
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                            }
                            m_GameMap[i][j + 1] = 4; // 將右邊一格設為玩家
                            m_Player->SetPosition({ m_Player->GetPosition().x + 40, m_Player->GetPosition().y });
                            needUpdate = true;
                            isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                        }
						/* 人的右邊是箱子 */
                        if (m_GameMap[i][j + 1] == 3 || (isBoxOnCheck && (i == m_BoxPosition_i) && (j == m_BoxPosition_j))) {
							/* 箱子右邊是空地 */
							if (m_GameMap[i][j + 2] == 2) {
                                if (!isPlayerOnCheck) { // 玩家不在目標點上
                                    m_GameMap[i][j] = 2; // 將當前位置設為空地
                                }
								m_GameMap[i][j + 1] = 4; // 將右邊一格設為玩家
								m_GameMap[i][j + 2] = 3; // 將箱子右邊一格設為箱子
								m_Player->SetPosition({ m_Player->GetPosition().x + 40, m_Player->GetPosition().y });
								m_Box->SetPosition({ m_Box->GetPosition().x + 40, m_Box->GetPosition().y });
								needUpdate = true;
                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                                isBoxOnCheck = false;
							}
							/* 箱子右邊是目標點 */
                            else if (m_GameMap[i][j + 2] == 5) {
                                m_Check->SetVisible(true);
                                isBoxOnCheck = true; // 箱子在目標點上
								m_BoxPosition_i = i;
								m_BoxPosition_j = j + 2;
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_GameMap[i][j + 1] = 4; // 將上面一格設為玩家
                                m_Box->SetPosition({ m_Box->GetPosition().x + 40, m_Box->GetPosition().y });
                                m_Player->SetPosition({ m_Player->GetPosition().x + 40, m_Player->GetPosition().y });
                                needUpdate = true;
                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌
                            }
                        }
                        /* 人的右邊是目標點 */
                        if (m_GameMap[i][j + 1] == 5) {
                            isPlayerOnCheck = true;
                            m_PlayerPosition_i = i;
                            m_PlayerPosition_j = j + 1;
                            std::cout << "Player Position on Check: (" << m_PlayerPosition_i << ", " << m_PlayerPosition_j << ")" << std::endl; 
                            /* 目標點上有箱子 */
                            if (isBoxOnCheck) {
                                m_Check->SetVisible(false);
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_GameMap[i][j + 2] = 3; // 將目標點右邊一格設為箱子
                                m_Player->SetPosition({ m_Player->GetPosition().x + 40, m_Player->GetPosition().y });
                                m_Box->SetPosition({ m_Box->GetPosition().x + 40, m_Box->GetPosition().y });
                                isBoxOnCheck = false;
                                needUpdate = true;
                            }
                            /* 目標點上沒東西 */
                            else {
                                m_GameMap[i][j] = 2; // 將當前位置設為空地
                                m_Player->SetPosition({ m_Player->GetPosition().x + 40, m_Player->GetPosition().y });
                                needUpdate = true;
                            }
                        }
                        break; // 找到玩家並移動後直接跳出內層迴圈
                    }
                }
                if (needUpdate) break; // 找到玩家並移動後直接跳出外層迴圈
            }

            for (const auto& row : m_GameMap) {
                for (const auto& cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

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