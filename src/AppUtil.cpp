//#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::ValidTask() {
	if (!m_PhaseChanged) {

		/* 清空地圖 */
		for (auto& wall : m_Wall) {
			m_Root.RemoveChild(wall);
		}
		m_Wall.clear();

		for (auto& floor : m_Floor) {
			m_Root.RemoveChild(floor);
		}
		m_Floor.clear();

		if (m_Player) {
			m_Root.RemoveChild(m_Player);
			m_Player.reset();
		}

		for (auto& box : m_Box_vec) {
			m_Root.RemoveChild(box);
		}
		m_Box_vec.clear();

		for (auto& check : m_Check_vec) {
			m_Root.RemoveChild(check);
		}
		m_Check_vec.clear();

		for (auto& point : m_Point_vec) {
			m_Root.RemoveChild(point);
		}
		m_Point_vec.clear();

		isPlayerOnCheck = false;
		m_PlayerPosition_i = 0;
		m_PlayerPosition_j = 0;
		BoxOnCheckCount = 0;
		isBoxOnCheck.clear();

		/* 不同關卡要做的事 */

		if (m_Phase == Phase::MENU) {
			std::cout << "MENU to LEVEL" << std::endl;

			m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
			m_PRM->NextPhase();

			/* ----- 字 ----- */
			TextLevel = 0;
			std::cout << "TextLevel: " << TextLevel << std::endl;
			m_PRM->SetTaskText(TextLevel);

			/* ----- 關卡選擇的箱子 ----- */
			// 初始化關卡選擇的箱子
			while (!m_PRM->AreAllBoxesAdded()) {
				m_PRM->AddNextLevelBox();
				auto box = m_PRM->GetLevelBoxes().back();
				box->SetVisible(false);  // 一開始設定為不可見
				m_Root.AddChildren({ box });
			}

			// 只顯示已破關的關卡（包括當前可進入的關卡）
			for (int i = 0; i < m_CurrentMaxLevel; ++i) {
				if (i < m_PRM->GetLevelBoxes().size()) {
					m_PRM->GetLevelBoxes()[i]->SetVisible(true);
				}
			}

			/* ----- 返回 的按鍵 ----- */
			btn_return = std::make_shared<Character>(RESOURCE_DIR"/Button/btn_return.png");
			m_Root.AddChild(btn_return);
			btn_return->SetZIndex(50);
			btn_return->SetPosition({ -155, 295 });
			btn_return->SetVisible(false);

			/* ----- 重置 的按鍵 ----- */
			btn_reset = std::make_shared<Character>(RESOURCE_DIR"/Button/btn_reset.png");
			m_Root.AddChild(btn_reset);
			btn_reset->SetZIndex(50);
			btn_reset->SetPosition({ 155, 295 });
			btn_reset->SetVisible(false);

			/* ----- 跳下一關 ----- */
			m_PRM->GetLevelBoxes()[0]->SetVisible(true);

			m_Phase = Phase::LEVELSELECT;
			m_PhaseChanged = true;
		}

		else if (m_Phase >= Phase::LEVELSELECT && m_Phase <= Phase::LEVEL29) {
			std::cout << "LEVEL" << static_cast<int>(m_Phase) - static_cast<int>(Phase::LEVEL1) + 1 << " to LEVEL" << static_cast<int>(m_Phase) - static_cast<int>(Phase::LEVEL1) + 2 << std::endl;

			int levelIndex = static_cast<int>(m_Phase) - static_cast<int>(Phase::LEVEL1) + 1;

			/* ----- 背景 ----- */
			m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
			if (m_Phase == Phase::LEVELSELECT) {  // 做箱子、m_Phase++
				m_PRM->NextPhase();
			}

			/* ----- 文字 ----- */
			TextLevel = static_cast<int>(m_Phase) - static_cast<int>(Phase::LEVELSELECT);
			std::cout << "TextLevel+1: " << TextLevel + 1 << std::endl;
			//m_PRM->SetPassText();

			m_PRM->SetTaskText(TextLevel + 1);
			m_PRM->GetTaskText()->SetVisible(true);

			if (m_Phase == Phase::LEVELSELECT) {
				/* ----- 選擇關卡的箱子 ----- */
				m_PRM->ShowLevelBoxes(false);

				/* ----- 返回的按鈕 ----- */
				btn_return->SetVisible(true);

				/* ----- 重置的按鈕 ----- */
				if (!btn_reset) {
					btn_reset = std::make_shared<Character>(RESOURCE_DIR"/Button/btn_reset.png");
					m_Root.AddChild(btn_reset);
					btn_reset->SetZIndex(50);
					btn_reset->SetPosition({ 155, 295 }); // 右上角位置
				}
				btn_reset->SetVisible(true);
			}

			/* ----- [for 11~20] 限制步數 ----- */
			if (m_Phase >= Phase::LEVEL10 && m_Phase <= Phase::LEVEL19) {
				int remainingStepsValues[] = { 10, 10, 20, 25, 40 ,30 ,30 ,50 ,20 ,25 };
				m_RemainingSteps = remainingStepsValues[levelIndex % 10];
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);
			}
			else {
				m_PRM->GetRemainingStepsText()->SetVisible(false);
			}

			/* ----- [for 21~30] 限制時間 ----- */
			if (m_Phase >= Phase::LEVEL20 && m_Phase <= Phase::LEVEL29) {
				// 設置時間限制s
				int remainingTimeValues[] = { 15, 15, 30, 35, 50, 40, 40, 60, 30, 35 };
				if (m_Phase >= Phase::LEVEL21 && m_Phase <= Phase::LEVEL30) {
					m_RemainingTime = remainingTimeValues[levelIndex % 10];
				}
				m_LastTimeUpdate = std::chrono::steady_clock::now();

				m_TimeLimited = true;

				// 顯示時間文字
				int minutes = m_RemainingTime / 60;
				int seconds = m_RemainingTime % 60;
				std::string timeStr = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
					(seconds < 10 ? "0" : "") + std::to_string(seconds);
				m_TimeText->SetText(timeStr);
				m_TimeText->SetVisible(true);
			}
			else {
				// 非計時關卡隱藏時間文字
				m_TimeLimited = false;
				m_TimeText->SetVisible(false);
			}

			/* ----- 跳下一關 ----- */
			// 設定 m_Phase 為下一關
			m_Phase = static_cast<Phase>(static_cast<int>(m_Phase) + 1);

			// 設定地圖 (GameMap)
			std::vector<std::vector<int>>* gameMaps[] = {
				&GameMap1, &GameMap2, &GameMap3, &GameMap4, &GameMap5,
				&GameMap6, &GameMap7, &GameMap8, &GameMap9, &GameMap10
			};
			InitializeMap(*gameMaps[levelIndex % 10]);

			// 設定過關箱子數 (BoxPass)
			int boxPassValues[] = { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
			BoxPass = boxPassValues[levelIndex % 10];

			// 更新已破關的關卡紀錄
			if (m_CurrentMaxLevel < levelIndex + 1) {
				m_CurrentMaxLevel = levelIndex + 1;
			}

			m_PhaseChanged = true;
		}

		else if (m_Phase == Phase::LEVEL30) {
			std::cout << "Game Over! No remaining steps." << std::endl;

			if (m_PRM) {
				if (Lose) { // 輸了
					m_PRM->SetImage(RESOURCE_DIR"/Background/bg_lose.png");
				}
				else {
					m_PRM->SetImage(RESOURCE_DIR"/Background/bg_win.png");
				}
			}

			m_PRM->GetRemainingStepsText()->SetVisible(false);
			m_PRM->GetTaskText()->SetVisible(false);
			m_TimeText->SetVisible(false);

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

			m_Phase = Phase::END; // 遊戲結束
		}
	}
}