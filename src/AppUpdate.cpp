#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

#include <iostream>

#include <SDL.h>
#include <chrono>

void App::Update() {

    /* 關卡選擇 */
    // 檢測Enter鍵 避免重複觸發
    bool enterKeyCurrentlyPressed = Util::Input::IsKeyPressed(Util::Keycode::RETURN);
    static bool keyProcessed = false; // 確認有沒有按過按鍵了(除作弊模式以外)，沒有就可以按，否則不能
    
    // 檢測滑鼠左鍵的按下
    bool mouseLeftButtonPressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
    bool mouseLeftButtonDown = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);
    
    // 檢測Shift鍵的按下，用於確認關卡選擇
    bool shiftKeyPressed = Util::Input::IsKeyPressed(Util::Keycode::LSHIFT) || Util::Input::IsKeyPressed(Util::Keycode::RSHIFT);

    // 這裡是對Phase::MENU按下滑鼠也能跳到下一個頁面的東東
    if (m_Phase == Phase::MENU && mouseLeftButtonDown) {
        ValidTask(); // 從MENU跳到LEVELSELECT
        keyProcessed = true;
    }

    if (m_Phase == Phase::MENU) {
        // 在MENU階段 任何按鍵跟滑鼠都可以進入LEVELSELECT
        if (mouseLeftButtonDown || enterKeyCurrentlyPressed) {
            ValidTask();
            keyProcessed = true;
        }
    }

    // LEVELSELECT處理輸入(看要跳到哪個關卡)
    if (m_Phase == Phase::LEVELSELECT) {

        /* [special] 作弊模式 */

        // 第1~10關
        // 普通的輸入數字 (0代表10)
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

		// 11~20
        // 按Alt+1表示11，Alt+2表示12...
        else if (Util::Input::IsKeyPressed(Util::Keycode::LALT) || Util::Input::IsKeyPressed(Util::Keycode::RALT)) {
            if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) m_SelectedLevel = 11;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) m_SelectedLevel = 12;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_3)) m_SelectedLevel = 13;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_4)) m_SelectedLevel = 14;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_5)) m_SelectedLevel = 15;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_6)) m_SelectedLevel = 16;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_7)) m_SelectedLevel = 17;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_8)) m_SelectedLevel = 18;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_9)) m_SelectedLevel = 19;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_0)) m_SelectedLevel = 20;
        }

        // 21~30
        // 按Ctrl + 1表示21，Ctrl + 2表示22...
        else if (Util::Input::IsKeyPressed(Util::Keycode::LCTRL) || Util::Input::IsKeyPressed(Util::Keycode::RCTRL)) {
            if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) m_SelectedLevel = 21;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) m_SelectedLevel = 22;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_3)) m_SelectedLevel = 23;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_4)) m_SelectedLevel = 24;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_5)) m_SelectedLevel = 25;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_6)) m_SelectedLevel = 26;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_7)) m_SelectedLevel = 27;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_8)) m_SelectedLevel = 28;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_9)) m_SelectedLevel = 29;
            else if (Util::Input::IsKeyPressed(Util::Keycode::NUM_0)) m_SelectedLevel = 30;
        }


        /* [normal] 滑鼠點擊 */

        if (mouseLeftButtonDown) {
            // 獲取滑鼠位置
            Util::PTSDPosition mousePos = Util::Input::GetCursorPosition();
            
            keyProcessed = true; // 有按過按鍵了

            // 是否點擊了箱子
            auto levelBoxes = m_PRM->GetLevelBoxes();

            for (size_t i = 0; i < 30; ++i) {
                // 只檢查已出現的箱子
                if (levelBoxes[i]->GetVisibility()) {
                    // 取得箱子位置
                    glm::vec2 boxPos = levelBoxes[i]->GetPosition();
                    
                    // 檢查滑鼠是否在箱子區域內
                    if (mousePos.x >= (boxPos.x - 25.0) && mousePos.x <= (boxPos.x + 25.0) &&
                        (mousePos.y) * -1 >= (boxPos.y - 25.0) && (mousePos.y) * -1 <= (boxPos.y + 25.0)) {
                        // 設置選中的關卡
                        m_SelectedLevel = i + 1;
                        std::cout << "m_SelectedLevel: " << m_SelectedLevel << std::endl;

                        // 模擬按下Shift確認選擇
                        shiftKeyPressed = true;
                        break;
                    }
                }
            }
        }

        // 當選定關卡後，按下Shift確認選擇
        if (m_SelectedLevel > 0 && shiftKeyPressed) {

            m_PRM->ShowLevelBoxes(false); // 所有關卡箱子消失

            // 根據選擇的關卡設置相應的階段並初始化地圖
            switch (m_SelectedLevel) {
                //m_Phase設在前一關，執行ValidTask()時會跳到下一關

                case 1:
                    m_Phase = Phase::LEVELSELECT;
                    ValidTask();
                    break;
                case 2:
                    m_Phase = Phase::LEVEL1;
                    ValidTask();
                    break;
                case 3:
                    m_Phase = Phase::LEVEL2;
                    ValidTask();
                    break;
                case 4:
                    m_Phase = Phase::LEVEL3;
                    ValidTask();
                case 5:
                    m_Phase = Phase::LEVEL4;
                    ValidTask();
                case 6:
                    m_Phase = Phase::LEVEL5;
                    ValidTask();
                case 7:
                    m_Phase = Phase::LEVEL6;
                    ValidTask();
                case 8:
                    m_Phase = Phase::LEVEL7;
                    ValidTask();
                case 9:
                    m_Phase = Phase::LEVEL8;
                    ValidTask();
                case 10:
                    m_Phase = Phase::LEVEL9;
                    ValidTask();
                break;

                // ----- 待完成更多關卡 -----

                default:
                    // 默認使用第一關地圖
                    m_Phase = Phase::LEVELSELECT;
                    ValidTask();
                    break;
            }


        }
    }

    /* 遊戲中返回關卡選擇畫面 */
    else if (m_Phase != Phase::MENU && m_Phase != Phase::LEVELSELECT) {
        if (Util::Input::IsKeyPressed(Util::Keycode::BACKSPACE) ||
            (mouseLeftButtonDown && Util::Input::GetCursorPosition().x < 50 && Util::Input::GetCursorPosition().y < 50)) {

            // 回去LEVELSELECT (按下Backspace鍵或點擊左上角區域)
            m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
            m_PRM->ShowLevelBoxes(true);  // 顯示箱子
            m_Phase = Phase::LEVELSELECT;
            m_SelectedLevel = 0;  // 選擇關卡的值歸零

            // 遊戲物件隱藏
            if (m_Player) { // 人物
                m_Player->SetVisible(false);
            }
            for (auto& box : m_Box_vec) { // 箱子
                box->SetVisible(false);
            }
            for (auto& wall : m_Wall) { // 牆壁
                wall->SetVisible(false);
            }
            for (auto& floor : m_Floor) { // 地板
                floor->SetVisible(false);
            }
            for (auto& point : m_Point_vec) { // 目標點
                point->SetVisible(false);
            }
            for (auto& check : m_Check_vec) { // 勾勾
                check->SetVisible(false);
            }

            keyProcessed = true; // 有按過按鍵了
        }
    }

    /* 遊戲 */
    bool needUpdate = false;

    if (m_Phase != Phase::MENU && m_Phase != Phase::LEVELSELECT) {
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

        // 勝利條件驗證：檢查是否所有目標點上都有箱子
        if (m_Phase != Phase::MENU && m_Phase != Phase::LEVELSELECT) {
            if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
                // 檢查所有目標點是否都有箱子
                bool allPointsHaveBoxes = true;
                // 如果所有的箱子都在目標點上，則 BoxOnCheckCount 應該等於 BoxPass
                if (BoxOnCheckCount >= BoxPass) {
                    std::cout << "Win! Proceed to next level" << std::endl;
                    // 跳到下一關卡
                    m_PhaseChanged = false; // 重置狀態以允許切換關卡
                    ValidTask();
                } else {
                    std::cout << "Current level not finish yet" << std::endl;
                    // 這裡可以加入視覺提示或其他反饋
                }
            }
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
                        for (size_t k = 0; k < m_Box_vec.size(); ++k) {
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

                                /* 箱子的上面是牆壁 (什麼事都不用做) */
                                else {
                                    needUpdate = true;

                                    break;
                                }
                            }
                        }

                        /* 人的上面是目標點 */
                        if (m_GameMap[i + GameMap_i][j + GameMap_j] == 5) {

                            /* 目標點上有箱子 */
                            for (size_t k = 0; k < m_Box_vec.size(); k++) {

                                if ((m_Box_vec[k]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 40))
                                    && (m_Box_vec[k]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 40))) {

                                    bool temp2box = false; // 記錄上面的上面還有沒有箱子

                                    /* 目標點的上面一格還有箱子 */
                                    for (size_t j = 0; j < m_Box_vec.size(); ++j) {
                                        if ((m_Box_vec[j]->GetPosition().x == m_Player->GetPosition().x + (SetPosition_i * 80))
                                            && (m_Box_vec[j]->GetPosition().y == m_Player->GetPosition().y + (SetPosition_j * 80))) {

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
                                        if (needUpdate) break;
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

                                        /* 目標點的上面是牆壁 (什麼事都不用做) */
                                        else {

											needUpdate = true;

                                            break;
                                        }
                                    }

                                }

                                if (needUpdate) break;
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
        
        // 在LEVELSELECT按下Enter不做任何事情
        if (m_Phase == Phase::LEVELSELECT) {
        }
        
        // 按下Enter檢查是否過關、過關就換到下一關的畫面 沒過關就會跳出通知並留在原本的關卡頁
        else if (m_Phase != Phase::LEVELSELECT && m_Phase != Phase::MENU && m_Phase != Phase::END) {
            
            // 檢查所有的目標點都有箱子
            if (BoxOnCheckCount >= BoxPass) {
                std::cout << "Win! All targets are covered with boxes." << std::endl;
                ValidTask(); // 跳到下一關
                BoxOnCheckCount = 0;
            } else {
                std::cout << "current level not finish yet" << std::endl;
            }
        }
        else {
            // 其他情況下按Enter才執行ValidTask()
            ValidTask();
        }
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();

    if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        m_PhaseChanged = false;
    }
}