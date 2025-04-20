//#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::ValidTask() {
	if (!m_PhaseChanged) {
		switch (m_Phase) {
			case Phase::MENU:
				std::cout << "MENU to LEVEL" << std::endl;
				
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_level.png");
				// m_PRM->ShowLevelBoxes(true);  // 顯示箱子
				m_PRM->NextPhase();

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

			case Phase::LEVELSELECT:
				std::cout << "LEVELSELECT to LEVEL1" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->ShowLevelBoxes(false);
				
				btn_return->SetVisible(true);
				// 新增重置按鈕
				if (!btn_reset) {
					btn_reset = std::make_shared<Character>(RESOURCE_DIR"/Button/btn_reset.png");
					m_Root.AddChild(btn_reset);
					btn_reset->SetZIndex(50);
					btn_reset->SetPosition({ 155, 295 }); // 右上角位置
				}
				btn_reset->SetVisible(true);

				//m_PRM->ShowNextLevelBox();
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL1;
				InitializeMap(GameMap1);
				BoxPass = 1;
				if (m_CurrentMaxLevel < 1) m_CurrentMaxLevel = 1; // 更新已破關的關卡紀錄
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL1:
				std::cout << "LEVEL1 to LEVEL2" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL2;
				InitializeMap(GameMap2);
				BoxPass = 1;
				if (m_CurrentMaxLevel < 2) m_CurrentMaxLevel = 2; // 更新已破關的關卡紀錄
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL2:
				std::cout << "LEVEL2 to LEVEL3" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL3;
				InitializeMap(GameMap3);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 3) m_CurrentMaxLevel = 3; // 更新已破關的關卡紀錄
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL3:
				std::cout << "LEVEL3 to LEVEL4" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL4;
				InitializeMap(GameMap4);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 4) m_CurrentMaxLevel = 4;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL4:
				std::cout << "LEVEL4 to LEVEL5" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL5;
				InitializeMap(GameMap5);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 5) m_CurrentMaxLevel = 5;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL5:
				std::cout << "LEVEL5 to LEVEL6" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL6;
				InitializeMap(GameMap6);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 6) m_CurrentMaxLevel = 6;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL6:
				std::cout << "LEVEL6 to LEVEL7" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL7;
				InitializeMap(GameMap7);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 7) m_CurrentMaxLevel = 7;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL7:
				std::cout << "LEVEL7 to LEVEL8" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL8;
				InitializeMap(GameMap8);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 8) m_CurrentMaxLevel = 8;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL8:
				std::cout << "LEVEL8 to LEVEL9" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL9;
				InitializeMap(GameMap9);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 9) m_CurrentMaxLevel = 9;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL9:
				std::cout << "LEVEL9 to LEVEL10" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL10;
				InitializeMap(GameMap10);
				BoxPass = 2;
				if (m_CurrentMaxLevel < 10) m_CurrentMaxLevel = 10;
				m_PhaseChanged = true;
				break;
			//
			// case Phase::LEVEL10:
			// 	std::cout << "LEVEL10 to LEVEL11" << std::endl;
			// 	m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
			// 	m_PRM->NextPhase();
			// 	m_Phase = Phase::LEVEL11;
			// 	InitializeMap(GameMap11);
			// 	BoxPass = 2;
			// if (m_CurrentMaxLevel < 11) m_CurrentMaxLevel = 11;
			// 	m_PhaseChanged = true;
			// 	break;

			default:
				m_CurrentState = State::END;
		}
	}
}