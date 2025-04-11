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
		for (auto& box : m_Box_vec) { // 箱子
			box->SetVisible(true);
		}
		for (auto& wall : m_Wall) { // 牆壁
            wall->SetVisible(true);
        }
		for (auto& floor : m_Floor) { // 地板
            floor->SetVisible(true);
        }
        for (auto& point : m_Point_vec) { // 目標點
            point->SetVisible(true);
        }
        // 勾勾(m_Check)先不要顯示
    }

    /* 設定上下左右ㄉGameMap和SetPosition的移動方向 */
    
    // 上
    int UP_GameMap_i = -1;
	int UP_GameMap_j = 0;
    int UP_SetPosition_i = 0;
	int UP_SetPosition_j = 1;
    // 下
	int DOWN_GameMap_i = 1;
	int DOWN_GameMap_j = 0;
	int DOWN_SetPosition_i = 0;
	int DOWN_SetPosition_j = -1;
	// 左
	int LEFT_GameMap_i = 0;
    int LEFT_GameMap_j = -1;
	int LEFT_SetPosition_i = -1;
	int LEFT_SetPosition_j = 0;
	// 右
	int RIGHT_GameMap_i = 0;
    int RIGHT_GameMap_j = 1;
	int RIGHT_SetPosition_i = 1;
	int RIGHT_SetPosition_j = 0;

    if ((Util::Input::IsKeyPressed(Util::Keycode::UP)) || (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) || (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) || (Util::Input::IsKeyPressed(Util::Keycode::RIGHT))) {
        
        /* 設定上下左右delta */
        int GameMap_i = 0;
		int GameMap_j = 0;
		int SetPosition_i = 0;
		int SetPosition_j = 0;

        if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
			GameMap_i = UP_GameMap_i;
			GameMap_j = UP_GameMap_j;
			SetPosition_i = UP_SetPosition_i;
			SetPosition_j = UP_SetPosition_j;
        }
        else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
			GameMap_i = DOWN_GameMap_i;
		    GameMap_j = DOWN_GameMap_j;
		    SetPosition_i = DOWN_SetPosition_i;
			SetPosition_j = DOWN_SetPosition_j;
        }
        else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
			GameMap_i = LEFT_GameMap_i;
			GameMap_j = LEFT_GameMap_j;
			SetPosition_i = LEFT_SetPosition_i;
			SetPosition_j = LEFT_SetPosition_j;
		}
		else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
			GameMap_i = RIGHT_GameMap_i;
			GameMap_j = RIGHT_GameMap_j;
			SetPosition_i = RIGHT_SetPosition_i;
			SetPosition_j = RIGHT_SetPosition_j;
        }
		
        
        if (!keyProcessed) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 9; j++) {

                    /* 人 */
                    if ((m_GameMap[i][j] == 4) || (isPlayerOnCheck && (i == m_PlayerPosition_i) && (j == m_PlayerPosition_j))) {

                        /* 人的上面是空地 (1、2) */
                        if (m_GameMap[i + GameMap_i][j + GameMap_j] == 2) {

                            /* 人不在目標點上 */
                            if (!isPlayerOnCheck) {
                                m_GameMap[i][j] = 2; // 目前位置設為空地
                            }
                            // GameMap
                            m_GameMap[i + GameMap_i][j + GameMap_j] = 4; // 上面一格設為人
                            // SetPosition
                            m_Player->SetPosition({ m_Player->GetPosition().x + (SetPosition_i * 40), m_Player->GetPosition().y + (SetPosition_j * 40)});

                            needUpdate = true;

                            isPlayerOnCheck = false; // 人離開目標點了

                            break;
                        }

                        /* 人的上面是箱子 */
                        if (m_GameMap[i + GameMap_i][j + GameMap_j] == 3) {

                            /* 箱子上面是空地 (3、4) */
                            if (m_GameMap[i + (GameMap_i * 2)][j + (GameMap_j * 2)] == 2) {

                                /* 人不在目標點上 */
                                if (!isPlayerOnCheck) {
                                    m_GameMap[i][j] = 2; // 目前位置設為空地
                                }

                                // GameMap
                                m_GameMap[i + GameMap_i][j + GameMap_j] = 4; // 上面一格設為人
                                m_GameMap[i + (GameMap_i * 2)][j + (GameMap_j * 2)] = 3; // 上面兩格設為箱子
                                // SetPosition (箱子先移動，再換人移動)
                                for (size_t k = 0; k < m_Box_vec.size(); ++k) { // 找到在人的上面一格的箱子
									std::cout << "m_Box_vec[" << k << "]: " << m_Box_vec[k]->GetPosition().x << ", " << m_Box_vec[k]->GetPosition().y << std::endl;
									std::cout << "m_Player->GetPosition().x + (SetPosition_i * 40): " << m_Player->GetPosition().x + (SetPosition_i * 40) << ", " << m_Player->GetPosition().y + (SetPosition_j * 40) << std::endl;
                                    if ((m_Box_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 40)) && (m_Box_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 40))) {
										m_Box_vec[k]->SetPosition({ m_Box_vec[k]->GetPosition().x + (SetPosition_i * 40), m_Box_vec[k]->GetPosition().y + (SetPosition_j * 40) });
                                        break;
                                    }
                                }
                                m_Player->SetPosition({ m_Player->GetPosition().x + (SetPosition_i * 40), m_Player->GetPosition().y + (SetPosition_j * 40) }); // 人往上一格

                                needUpdate = true;

                                isPlayerOnCheck = false; // 人離開目標點了

                                break;
                            }

                            /* 箱子上面是目標點 (5、6) */
                            else if (m_GameMap[i + (GameMap_i * 2)][j + (GameMap_j * 2)] == 5) {

                                /* 人不在目標點上 */
                                if (!isPlayerOnCheck) {
                                    m_GameMap[i][j] = 2; // 目前位置設為空地
                                }

                                // GameMap
                                m_GameMap[i + GameMap_i][j + GameMap_j] = 4; // 上面一格設為人
                                // SetPosition
                                for (size_t k = 0; k < m_Box_vec.size(); ++k) { // 找到在人的上面一格的箱子
                                    if ((m_Box_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 40)) && (m_Box_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 40))) {
                                        m_Box_vec[k]->SetPosition({ m_Box_vec[k]->GetPosition().x + (SetPosition_i * 40), m_Box_vec[k]->GetPosition().y + (SetPosition_j * 40) });
                                        isBoxOnCheck[k] = true;
                                        BoxOnCheckCount++;
                                        std::cout << "BoxOnCheckCount: " << BoxOnCheckCount << std::endl;
                                        break;
                                    }
                                }
                                
                                // 勾勾出現 (先勾勾，再人)
                                for (size_t k = 0; k < m_Check_vec.size(); ++k) { // 找到在人的上面兩格的勾勾(箱子的上面一格)
                                    if ((m_Check_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 80)) && (m_Check_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 80))) {
                                        m_Check_vec[k]->SetVisible(true);
                                    }
                                }

                                m_Player->SetPosition({ m_Player->GetPosition().x + (SetPosition_i * 40), m_Player->GetPosition().y + (SetPosition_j * 40) });

                                needUpdate = true;

                                isPlayerOnCheck = false; // 更新玩家位置後重置標誌

                                break;
                            }
                        }
                        /* 人的上面是目標點 */
                        if (m_GameMap[i + GameMap_i][j + GameMap_j] == 5) {

                            /* 目標點上有箱子*/
                            for (size_t k = 0; k < m_Box_vec.size(); ++k) {
                                if ((m_Box_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 40)) && (m_Box_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_i * 40))) {

                                    bool temp2box = false; // 記錄上面的上面還有沒有箱子

                                    /* 目標點的上面一格還有箱子 */
                                    for (size_t j = 0; j < m_Box_vec.size(); ++j) {
                                        if ((m_Box_vec[j]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 80)) && (m_Box_vec[j]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 80))) {

                                            temp2box = true; // 上面的上面還有箱子

                                            /* 上面的上面那個箱子踩在另一個目標點上 (9) */
                                            if (isBoxOnCheck[j]) {
                                                // GameMap
                                                m_GameMap[i][j] = 2; // 目前位置設為空地
                                                m_GameMap[i + (GameMap_i * 3)][j + (GameMap_j * 3)] = 3; // 上面三格設為箱子

                                                // SetPosition
                                                m_Box_vec[k]->SetPosition({ m_Box_vec[k]->GetPosition().x + (SetPosition_i * 40), m_Box_vec[k]->GetPosition().y + (SetPosition_j * 40) });
                                                m_Box_vec[j]->SetPosition({ m_Box_vec[j]->GetPosition().x + (SetPosition_i * 40), m_Box_vec[j]->GetPosition().y + (SetPosition_j * 40) });
                                                m_Player->SetPosition({ m_Player->GetPosition().x + (SetPosition_i * 40), m_Player->GetPosition().y + (SetPosition_j * 40) });

                                                isPlayerOnCheck = true;
                                                m_PlayerPosition_i = i + GameMap_i;
                                                m_PlayerPosition_j = j + GameMap_j;

                                                isBoxOnCheck[k] = true;
                                                isBoxOnCheck[j] = false;
                                                BoxOnCheckCount--;
                                                std::cout << "BoxOnCheckCount: " << BoxOnCheckCount << std::endl;

                                                needUpdate = true;

                                                break;
                                            }

                                            /* 上面的上面那個箱子沒有踩在另一個目標點上 (10、11) */
                                            else {
                                                if (!isPlayerOnCheck) {
                                                    m_GameMap[i][j] = 2; // 目前位置設為空地
                                                }

                                                // GameMap
                                                m_GameMap[i + (GameMap_i * 2)][j + (GameMap_j * 2)] = 4; // 上面兩格設為箱子
                                                m_GameMap[i + (GameMap_i * 3)][j + (GameMap_j * 3)] = 3; // 上面三格設為箱子

                                                // SetPosition
                                                m_Box_vec[k]->SetPosition({ m_Box_vec[k]->GetPosition().x + (SetPosition_i * 40), m_Box_vec[k]->GetPosition().y + (SetPosition_j * 40) });
                                                m_Box_vec[j]->SetPosition({ m_Box_vec[j]->GetPosition().x + (SetPosition_i * 40), m_Box_vec[j]->GetPosition().y + (SetPosition_j * 40) });
                                                
                                                isBoxOnCheck[k] = false;
                                                BoxOnCheckCount--;

                                                isPlayerOnCheck = true; // 人在目標點上
                                                m_PlayerPosition_i = i + GameMap_i;
                                                m_PlayerPosition_j = j + GameMap_j;

                                                // 勾勾消失
                                                for (size_t k = 0; k < m_Check_vec.size(); ++k) {
                                                    if ((m_Check_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 40)) && (m_Check_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 40))) {
                                                        m_Check_vec[k]->SetVisible(false);
                                                    }
                                                }

                                                m_Player->SetPosition({ m_Player->GetPosition().x + (SetPosition_i * 40), m_Player->GetPosition().y + (SetPosition_j * 40) }); // 人往上一格

                                                needUpdate = true;

                                                break;
                                            }
                                        }
                                    }

                                    /* 目標點的上面一格沒有箱子 */
                                    if (!temp2box) {

                                        /* 目標點的上面是空地 (12、13) */
                                        if (m_GameMap[i + (GameMap_i * 2)][j + (GameMap_j * 2)] == 2) {
                                            if (!isPlayerOnCheck) {
                                                m_GameMap[i][j] = 2; // 目前位置設為空地
                                            }

                                            // GameMap
                                            m_GameMap[i + (GameMap_i * 2)][j + (GameMap_j * 2)] = 3; // 上面兩格設為箱子

                                            // SetPosition
                                            m_Box_vec[k]->SetPosition({ m_Box_vec[k]->GetPosition().x + (SetPosition_i * 40), m_Box_vec[k]->GetPosition().y + (SetPosition_j * 40) }); // 箱子往上一格
                                            
                                            isBoxOnCheck[k] = false;
                                            BoxOnCheckCount--;

                                            isPlayerOnCheck = true; // 人在目標點上
                                            m_PlayerPosition_i = i + GameMap_i;
                                            m_PlayerPosition_j = j + GameMap_j;

                                            // 勾勾消失
                                            for (size_t k = 0; k < m_Check_vec.size(); ++k) {
                                                if ((m_Check_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 40)) && (m_Check_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 40))) {
                                                    m_Check_vec[k]->SetVisible(false);
                                                }
                                            }

                                            m_Player->SetPosition({ m_Player->GetPosition().x + (SetPosition_i * 40), m_Player->GetPosition().y + (SetPosition_j * 40) }); // 人往上一格

                                            needUpdate = true;

                                            break;
                                        }

                                        /* 目標點的上面是另一個目標點 (14) */
                                        else if (m_GameMap[i + (GameMap_i * 2)][j + (GameMap_j * 2)] == 5) {

                                            // GameMap
                                            m_GameMap[i][j] = 2; // 目前位置設為空地
                                            m_GameMap[i + (GameMap_i * 2)][j + (GameMap_j * 2)] = 3; // 上面兩格設為箱子

                                            // SetPosition
                                            m_Box_vec[k]->SetPosition({ m_Box_vec[k]->GetPosition().x + (SetPosition_i * 40), m_Box_vec[k]->GetPosition().y + (SetPosition_j * 40) }); // 箱子往上一格
                                            
                                            isBoxOnCheck[k] = true;

                                            isPlayerOnCheck = true; // 人在目標點上
                                            m_PlayerPosition_i = i + GameMap_i;
                                            m_PlayerPosition_j = j + GameMap_j;

                                            // 勾勾消失 (人的上面一格)
                                            for (size_t k = 0; k < m_Check_vec.size(); ++k) {
                                                if ((m_Check_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 40)) && (m_Check_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 40))) {
                                                    m_Check_vec[k]->SetVisible(false);
                                                }
                                            }

                                            // 勾勾出現 (人的上面兩格)
                                            for (size_t k = 0; k < m_Check_vec.size(); ++k) {
                                                if ((m_Check_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 80)) && (m_Check_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 80))) {
                                                    m_Check_vec[k]->SetVisible(true);
                                                }
                                            }

                                            m_Player->SetPosition({ m_Player->GetPosition().x + (SetPosition_i * 40), m_Player->GetPosition().y + (SetPosition_j * 40) }); // 人往上一格
											
                                            needUpdate = true;

                                            break;
                                        }
                                    }
                                }

                                /* 目標點上沒箱子 (7、8) */
                                if (!needUpdate) {
                                    if (!isPlayerOnCheck) {
                                        m_GameMap[i][j] = 2; // 將當前位置設為空地
                                    }

                                    // SetPosition
                                    m_Player->SetPosition({ m_Player->GetPosition().x + (SetPosition_i * 40), m_Player->GetPosition().y + (SetPosition_j * 40) });

                                    isPlayerOnCheck = true;
                                    m_PlayerPosition_i = i + GameMap_i;
                                    m_PlayerPosition_j = j + GameMap_j;

                                    needUpdate = true;

                                    break;
                                }
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