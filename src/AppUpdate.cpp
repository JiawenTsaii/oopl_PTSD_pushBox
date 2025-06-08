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
        // F1 + num
        if (Util::Input::IsKeyPressed(Util::Keycode::F1)) {
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
        }

		// 11~20
        // F2 + num
        else if (Util::Input::IsKeyPressed(Util::Keycode::F2)) {
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
        // F3 + num
        else if (Util::Input::IsKeyPressed(Util::Keycode::F3)) {
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
                        break;
                    }
                }
            }
        }

        if (m_SelectedLevel > 0) {

            m_PRM->ShowLevelBoxes(false); // 所有關卡箱子消失

            // reset、return按鈕出現
            btn_return->SetVisible(true);
            btn_reset->SetVisible(true);

            /* 根據選擇的關卡設置相應的階段並初始化地圖 */
            if (m_SelectedLevel == 1) {
                m_Phase = Phase::LEVELSELECT;
                TextLevel = 0;
            }
            else if (m_SelectedLevel >= 2 && m_SelectedLevel <= 30) {
                m_Phase = static_cast<Phase>(static_cast<int>(Phase::LEVEL1) + (m_SelectedLevel - 2));
                std::cout << "m_SelectedLevel-1: " << m_SelectedLevel-1 << std::endl;
                TextLevel = m_SelectedLevel - 1;
            }
            else {
                // 默認使用第一關地圖
                m_Phase = Phase::LEVELSELECT;
            }
            ValidTask();
        }
    }

    /* 遊戲中返回關卡選擇畫面 */
    else if (m_Phase != Phase::MENU && m_Phase != Phase::LEVELSELECT) {
        
        if (Util::Input::IsKeyPressed(Util::Keycode::BACKSPACE) ||
            (mouseLeftButtonDown && Util::Input::GetCursorPosition().x < -130 && Util::Input::GetCursorPosition().y < -270)) {

            if (Lose) {
                m_Phase = Phase::LEVELSELECT;
                Lose = false;
            }

            // 重置時間限制
            m_TimeLimited = false;
            m_TimeText->SetVisible(false);

            btn_return->SetVisible(false);
            btn_reset->SetVisible(false);

            // LEVEL ? 消失
            TextLevel = 0;
            std::cout << "TextLevel: " << TextLevel << std::endl;
            m_PRM->SetTaskText(TextLevel);

            // 剩餘步數消失
            m_PRM->GetRemainingStepsText()->SetVisible(false);

            // 回去LEVELSELECT (按下Backspace鍵或點擊左上角區域)
            m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");

            // 只顯示到目前已破關的關卡數量的箱子
            m_PRM->ShowLevelBoxes(false);  // 先隱藏所有箱子
            // 顯示已解鎖的關卡箱子
            for (int i = 0; i < m_CurrentMaxLevel; ++i) {
                if (i < m_PRM->GetLevelBoxes().size()) {
                    m_PRM->GetLevelBoxes()[i]->SetVisible(true);
                }
            }

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

        // 檢查滑鼠是否點擊了右上角的重置按鈕
        else if (mouseLeftButtonDown && Util::Input::GetCursorPosition().x > 130 && Util::Input::GetCursorPosition().y < -270) {
            
            isPlayerOnCheck = false;
            m_PlayerPosition_i = 0;
            m_PlayerPosition_j = 0;
            BoxOnCheckCount = 0;
            isBoxOnCheck.clear();

            m_LevelCompleted = false;
            
            // 重新初始化當前關卡
            if (m_Phase >= Phase::LEVEL1 && m_Phase <= Phase::LEVEL30) {
                int levelIndex = static_cast<int>(m_Phase) - static_cast<int>(Phase::LEVEL1);

                // 動態選擇對應的 GameMap
                std::vector<std::vector<int>>* gameMaps[] = {
                    &GameMap1, &GameMap2, &GameMap3, &GameMap4, &GameMap5,
                    &GameMap6, &GameMap7, &GameMap8, &GameMap9, &GameMap10
                };

                // 設定 BoxPass
                int boxPassValues[] = { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };

                // 設定剩餘步數 (僅適用於 LEVEL11~LEVEL20)
                int remainingStepsValues[] = { 10, 10, 20, 25, 40, 30, 30, 50, 20, 25 };
                int remainingTimeValues[] = { 15, 15, 30, 35, 50, 40, 40, 60, 30, 35 };

                // 初始化地圖
                InitializeMap(*gameMaps[levelIndex % 10]);

                // 設定 BoxPass
                BoxPass = boxPassValues[levelIndex % 10];

                // 設定剩餘步數 (LEVEL11~LEVEL20)
                if (m_Phase >= Phase::LEVEL11 && m_Phase <= Phase::LEVEL20) {
                    m_RemainingSteps = remainingStepsValues[levelIndex % 10];
                    m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                }
                // 設定剩餘時間 (LEVEL21~LEVEL30)
                if (m_Phase >= Phase::LEVEL21 && m_Phase <= Phase::LEVEL30) {
                    m_RemainingTime = remainingTimeValues[levelIndex % 10];
                    // m_PRM->
                    // m_PRM->SetRemainingTimeText(std::to_string(m_RemainingTime));
                }

                // 設置時間限制 (LEVEL21~LEVEL30)
                // m_TimeLimit = 10; // 10秒時間限制
                m_RemainingTime = m_TimeLimit;
                m_LastTimeUpdate = std::chrono::steady_clock::now();
                int minutes = m_RemainingTime / 60;
                int seconds = m_RemainingTime % 60;
                std::string timeStr = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                    (seconds < 10 ? "0" : "") + std::to_string(seconds);
            }
            else {
                // 默認處理
                ValidTask();
            }
        }
    }

    /* 步數限制 */
    bool StepKeyProcessed = false;

    /* 遊戲 */
    bool needUpdate = false;

    if (m_Phase != Phase::MENU && m_Phase != Phase::LEVELSELECT && m_Phase != Phase::END) {

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

        if ((m_Phase != Phase::MENU && m_Phase != Phase::LEVELSELECT && m_Phase != Phase::END) &&
            (
                (Util::Input::IsKeyPressed(Util::Keycode::UP))
                || (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) 
                || (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) 
                || (Util::Input::IsKeyPressed(Util::Keycode::RIGHT))
            )
           ) {

            /* 換角色圖片 */
            if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
			    m_Player->SetImage(RESOURCE_DIR"/Object/Player/player_up.png");
		    }
		    else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
			    m_Player->SetImage(RESOURCE_DIR"/Object/Player/player_down.png");
		    }
		    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
			    m_Player->SetImage(RESOURCE_DIR"/Object/Player/player_left.png");
		    }
		    else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
			    m_Player->SetImage(RESOURCE_DIR"/Object/Player/player_right.png");
            }

            // 每移動一步就偵測一次
            if (m_Phase != Phase::LEVELSELECT && m_Phase != Phase::MENU && m_Phase != Phase::END) {
            
                /* 檢查所有的目標點都有箱子 */
                if (BoxOnCheckCount >= BoxPass) {
                
                    m_PRM->SetPassText();
                    std::cout << "m_PRM->SetPassText()" << std::endl;
				    m_PRM->GetTaskText()->SetVisible(true);
                
                    // 停頓一秒
                    auto startTime = Util::Time::GetElapsedTimeMs();
                    while (Util::Time::GetElapsedTimeMs() - startTime < 1000) {
                        // Busy-wait loop for 1 second
                    }

                    ValidTask(); // 跳到下一關
                    BoxOnCheckCount = 0;
                }

                /* 檢查剩餘步數是否>=0 */
                if (m_Phase >= Phase::LEVEL11 && m_Phase <= Phase::LEVEL20) {
                    if (m_RemainingSteps == 0) {
                        m_Phase = Phase::LEVEL30;
                        Lose = true;
                        ValidTask();
                    }
                }
            }

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
            if (m_Phase != Phase::MENU && m_Phase != Phase::LEVELSELECT && m_Phase != Phase::END) {
                if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
                    // 檢查所有目標點是否都有箱子
                    bool allPointsHaveBoxes = true;
                    // 如果所有的箱子都在目標點上，則 BoxOnCheckCount 應該等於 BoxPass
                    if (BoxOnCheckCount >= BoxPass) {
                        // 計算目前關卡的編號
                        int currentLevel = static_cast<int>(m_Phase) - static_cast<int>(Phase::LEVEL1) + 1;

                        // 更新最大已解鎖關卡
                        if (currentLevel + 1 > m_CurrentMaxLevel) {
                            m_CurrentMaxLevel = currentLevel + 1;
                        }

                        // 跳到下一關卡
                        m_PhaseChanged = false; // 重置狀態以允許切換關卡
                        ValidTask();
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

                                /* 步數限制 */
                                if ((Util::Input::IsKeyDown(Util::Keycode::UP)) ||
                                    (Util::Input::IsKeyDown(Util::Keycode::DOWN)) ||
                                    (Util::Input::IsKeyDown(Util::Keycode::LEFT)) ||
                                    (Util::Input::IsKeyDown(Util::Keycode::RIGHT))) {

                                    if (!StepKeyProcessed) {
                                        m_RemainingSteps--; // 每次移動步數減1
                                        m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                                        StepKeyProcessed = true; // 標記按鍵已處理
                                    }
                                }
                                else {
                                    StepKeyProcessed = false; // 當按鍵釋放時，重置標記
                                }

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

                                        /* 步數限制 */
                                        if ((Util::Input::IsKeyDown(Util::Keycode::UP)) ||
                                            (Util::Input::IsKeyDown(Util::Keycode::DOWN)) ||
                                            (Util::Input::IsKeyDown(Util::Keycode::LEFT)) ||
                                            (Util::Input::IsKeyDown(Util::Keycode::RIGHT))) {

                                            if (!StepKeyProcessed) {
                                                m_RemainingSteps--; // 每次移動步數減1
                                                m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                                                StepKeyProcessed = true; // 標記按鍵已處理
                                            }
                                        }
                                        else {
                                            StepKeyProcessed = false; // 當按鍵釋放時，重置標記
                                        }

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

                                        /* 步數限制 */
                                        if ((Util::Input::IsKeyDown(Util::Keycode::UP)) ||
                                            (Util::Input::IsKeyDown(Util::Keycode::DOWN)) ||
                                            (Util::Input::IsKeyDown(Util::Keycode::LEFT)) ||
                                            (Util::Input::IsKeyDown(Util::Keycode::RIGHT))) {

                                            if (!StepKeyProcessed) {
                                                m_RemainingSteps--; // 每次移動步數減1
                                                m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                                                StepKeyProcessed = true; // 標記按鍵已處理
                                            }
                                        }
                                        else {
                                            StepKeyProcessed = false; // 當按鍵釋放時，重置標記
                                        }

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

                                                    /* 步數限制 */
                                                    if ((Util::Input::IsKeyDown(Util::Keycode::UP)) ||
                                                        (Util::Input::IsKeyDown(Util::Keycode::DOWN)) ||
                                                        (Util::Input::IsKeyDown(Util::Keycode::LEFT)) ||
                                                        (Util::Input::IsKeyDown(Util::Keycode::RIGHT))) {

                                                        if (!StepKeyProcessed) {
                                                            m_RemainingSteps--; // 每次移動步數減1
                                                            m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                                                            StepKeyProcessed = true; // 標記按鍵已處理
                                                        }
                                                    }
                                                    else {
                                                        StepKeyProcessed = false; // 當按鍵釋放時，重置標記
                                                    }

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

                                                    /* 步數限制 */
                                                    if ((Util::Input::IsKeyDown(Util::Keycode::UP)) ||
                                                        (Util::Input::IsKeyDown(Util::Keycode::DOWN)) ||
                                                        (Util::Input::IsKeyDown(Util::Keycode::LEFT)) ||
                                                        (Util::Input::IsKeyDown(Util::Keycode::RIGHT))) {

                                                        if (!StepKeyProcessed) {
                                                            m_RemainingSteps--; // 每次移動步數減1
                                                            m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                                                            StepKeyProcessed = true; // 標記按鍵已處理
                                                        }
                                                    }
                                                    else {
                                                        StepKeyProcessed = false; // 當按鍵釋放時，重置標記
                                                    }

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

                                                /* 步數限制 */
                                                if ((Util::Input::IsKeyDown(Util::Keycode::UP)) ||
                                                    (Util::Input::IsKeyDown(Util::Keycode::DOWN)) ||
                                                    (Util::Input::IsKeyDown(Util::Keycode::LEFT)) ||
                                                    (Util::Input::IsKeyDown(Util::Keycode::RIGHT))) {

                                                    if (!StepKeyProcessed) {
                                                        m_RemainingSteps--; // 每次移動步數減1
                                                        m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                                                        StepKeyProcessed = true; // 標記按鍵已處理
                                                    }
                                                }
                                                else {
                                                    StepKeyProcessed = false; // 當按鍵釋放時，重置標記
                                                }

												std::cout << "isPlayerOnCheck: " << isPlayerOnCheck << std::endl;
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

                                                /* 步數限制 */
                                                if ((Util::Input::IsKeyDown(Util::Keycode::UP)) ||
                                                    (Util::Input::IsKeyDown(Util::Keycode::DOWN)) ||
                                                    (Util::Input::IsKeyDown(Util::Keycode::LEFT)) ||
                                                    (Util::Input::IsKeyDown(Util::Keycode::RIGHT))) {

                                                    if (!StepKeyProcessed) {
                                                        m_RemainingSteps--; // 每次移動步數減1
                                                        m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                                                        StepKeyProcessed = true; // 標記按鍵已處理
                                                    }
                                                }
                                                else {
                                                    StepKeyProcessed = false; // 當按鍵釋放時，重置標記
                                                }

                                                // GameMap
                                                m_GameMap[i][j] = 2; // 目前位置設為空地

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

                                    /* 步數限制 */
                                    if ((Util::Input::IsKeyDown(Util::Keycode::UP)) ||
                                        (Util::Input::IsKeyDown(Util::Keycode::DOWN)) ||
                                        (Util::Input::IsKeyDown(Util::Keycode::LEFT)) ||
                                        (Util::Input::IsKeyDown(Util::Keycode::RIGHT))) {

                                        if (!StepKeyProcessed) {
                                            m_RemainingSteps--; // 每次移動步數減1
                                            m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
                                            StepKeyProcessed = true; // 標記按鍵已處理
                                        }
                                    }
                                    else {
                                        StepKeyProcessed = false; // 當按鍵釋放時，重置標記
                                    }

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
        //std::cout << "RETURN" << std::endl;

        // 在LEVELSELECT按下Enter不做任何事情
        if (m_Phase == Phase::LEVELSELECT) {
        }
        else {
            // 其他情況下按Enter才執行ValidTask()
            ValidTask();
        }
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    // 更新計時
    if (m_TimeLimited && (m_Phase >= Phase::LEVEL21 && m_Phase <= Phase::LEVEL30)) {
        UpdateTimer();
    }

    m_Root.Update();

    if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        m_PhaseChanged = false;
    }
}

void App::UpdateTimer() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_LastTimeUpdate).count();

    // 每秒更新一次
    if (elapsed >= 1) {
        m_RemainingTime--;
        m_LastTimeUpdate = currentTime;

        // 更新顯示的時間
        int minutes = m_RemainingTime / 60;
        int seconds = m_RemainingTime % 60;
        std::string timeStr = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
            (seconds < 10 ? "0" : "") + std::to_string(seconds);
        m_TimeText->SetText(timeStr);

        // 檢查時間是否用完
        if (m_RemainingTime <= 0) {
            Lose = true;
            m_Phase = Phase::LEVEL30;
            ValidTask();
        }
    }
}