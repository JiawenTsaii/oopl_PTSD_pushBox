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
		switch (m_Phase) {
			case Phase::MENU:
				std::cout << "MENU to LEVEL" << std::endl;
				
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
				m_PRM->NextPhase();

				TextLevel = 0;
				std::cout << "TextLevel: " << TextLevel << std::endl;
				m_PRM->SetTaskText(TextLevel);

				// 初始化所有的箱子 (b1.png - b30.png)
				// 不過先設為不可見
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

				btn_return = std::make_shared<Character>(RESOURCE_DIR"/Button/btn_return.png");
				m_Root.AddChild(btn_return);
				btn_return->SetZIndex(50);
				btn_return->SetPosition({ -155, 295 });
				btn_return->SetVisible(false);

				btn_reset = std::make_shared<Character>(RESOURCE_DIR"/Button/btn_reset.png");
				m_Root.AddChild(btn_reset);
				btn_reset->SetZIndex(50);
				btn_reset->SetPosition({ 155, 295 });
				btn_reset->SetVisible(false);
				
				m_Phase = Phase::LEVELSELECT;
				m_PhaseChanged = true;

				m_PRM->GetLevelBoxes()[0]->SetVisible(true);

				break;

			/* LEVEL 1~10 (LEVELSELECT ~ LEVEL 9) */
			case Phase::LEVELSELECT:
				std::cout << "LEVELSELECT to LEVEL1" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->ShowLevelBoxes(false);

				m_PRM->NextPhase();

				/* 文字(第幾關) */
				TextLevel = 0;
				std::cout << "TextLevel+1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				btn_return->SetVisible(true);
				// 新增重置按鈕
				if (!btn_reset) {
					btn_reset = std::make_shared<Character>(RESOURCE_DIR"/Button/btn_reset.png");
					m_Root.AddChild(btn_reset);
					btn_reset->SetZIndex(50);
					btn_reset->SetPosition({ 155, 295 }); // 右上角位置
				}
				btn_reset->SetVisible(true);

				m_Phase = Phase::LEVEL1;
				InitializeMap(GameMap1);
				BoxPass = 1;
				if (m_CurrentMaxLevel < 1) m_CurrentMaxLevel = 1; // 更新已破關的關卡紀錄
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL1:
				std::cout << "LEVEL1 to LEVEL2" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 1;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL2;
				InitializeMap(GameMap2);
				BoxPass = 1;
				if (m_CurrentMaxLevel < 2) m_CurrentMaxLevel = 2; // 更新已破關的關卡紀錄

				m_PhaseChanged = true;
				break;

			case Phase::LEVEL2:
				std::cout << "LEVEL2 to LEVEL3" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				
				TextLevel = 2;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL3;
				InitializeMap(GameMap3);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 3) m_CurrentMaxLevel = 3; // 更新已破關的關卡紀錄
				
				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL3:
				std::cout << "LEVEL3 to LEVEL4" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				
				TextLevel = 3;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL4;
				InitializeMap(GameMap4);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 4) m_CurrentMaxLevel = 4;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL4:
				std::cout << "LEVEL4 to LEVEL5" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				
				TextLevel = 4;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL5;
				InitializeMap(GameMap5);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 5) m_CurrentMaxLevel = 5;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL5:
				std::cout << "LEVEL5 to LEVEL6" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				
				TextLevel = 5;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL6;
				InitializeMap(GameMap6);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 6) m_CurrentMaxLevel = 6;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL6:
				std::cout << "LEVEL6 to LEVEL7" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				
				TextLevel = 6;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL7;
				InitializeMap(GameMap7);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 7) m_CurrentMaxLevel = 7;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL7:
				std::cout << "LEVEL7 to LEVEL8" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				
				TextLevel = 7;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL8;
				InitializeMap(GameMap8);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 8) m_CurrentMaxLevel = 8;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL8:
				std::cout << "LEVEL8 to LEVEL9" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				
				TextLevel = 8;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL9;
				InitializeMap(GameMap9);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 9) m_CurrentMaxLevel = 9;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL9:
				std::cout << "LEVEL9 to LEVEL10" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				
				TextLevel = 9;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_Phase = Phase::LEVEL10;
				InitializeMap(GameMap10);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 10) m_CurrentMaxLevel = 10;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			/* LEVEL 11~20 (LEVEL 10~19) */
			case Phase::LEVEL10:
				std::cout << "LEVEL10 to LEVEL11" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 10;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 10; // 最多步數
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps)); // 更新步數文字
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL11;
				InitializeMap(GameMap11);
				BoxPass = 1;
				if (m_CurrentMaxLevel < 11) m_CurrentMaxLevel = 11;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL11:
				std::cout << "LEVEL1 to LEVEL2" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 11;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 10;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL12;
				InitializeMap(GameMap12);
				BoxPass = 1;
				if (m_CurrentMaxLevel < 12) m_CurrentMaxLevel = 12; // 更新已破關的關卡紀錄


				m_PhaseChanged = true;
				break;

			case Phase::LEVEL12:
				std::cout << "LEVEL2 to LEVEL3" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 12;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 20;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL13;
				InitializeMap(GameMap13);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 13) m_CurrentMaxLevel = 13; // 更新已破關的關卡紀錄

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL13:
				std::cout << "LEVEL3 to LEVEL4" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 13;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 25;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL14;
				InitializeMap(GameMap14);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 14) m_CurrentMaxLevel = 14;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL14:
				std::cout << "LEVEL4 to LEVEL5" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 14;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 40;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL15;
				InitializeMap(GameMap15);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 15) m_CurrentMaxLevel = 15;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL15:
				std::cout << "LEVEL5 to LEVEL6" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 15;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 30;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL16;
				InitializeMap(GameMap16);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 16) m_CurrentMaxLevel = 16;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL16:
				std::cout << "LEVEL6 to LEVEL7" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 16;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 30;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL17;
				InitializeMap(GameMap17);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 17) m_CurrentMaxLevel = 17;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL17:
				std::cout << "LEVEL7 to LEVEL8" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 17;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 50;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL18;
				InitializeMap(GameMap18);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 18) m_CurrentMaxLevel = 18;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL18:
				std::cout << "LEVEL8 to LEVEL9" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 18;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 20;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL19;
				InitializeMap(GameMap19);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 19) m_CurrentMaxLevel = 19;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL19:
				std::cout << "LEVEL9 to LEVEL10" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");

				TextLevel = 19;
				std::cout << "TextLevel + 1: " << TextLevel + 1 << std::endl;
				m_PRM->SetTaskText(TextLevel + 1);
				m_PRM->GetTaskText()->SetVisible(true);

				m_RemainingSteps = 25;
				m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));
				m_PRM->GetRemainingStepsText()->SetVisible(true);

				m_Phase = Phase::LEVEL20;
				InitializeMap(GameMap20);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 20) m_CurrentMaxLevel = 20;

				m_PRM->NextPhase();
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL30:
				std::cout << "Game Over! No remaining steps." << std::endl;
				
				if (Lose) { // 輸了
					m_PRM->SetImage(RESOURCE_DIR"/Background/bg_lose.png");
				}
				else {
					m_PRM->SetImage(RESOURCE_DIR"/Background/bg_win.png");
				}

				m_PRM->GetRemainingStepsText()->SetVisible(false);
				m_PRM->GetTaskText()->SetVisible(false);

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

				break;

			default:
				m_CurrentState = State::END;
		}
	}
}