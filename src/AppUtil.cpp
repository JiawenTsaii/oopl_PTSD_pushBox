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
				m_PRM->ShowLevelBoxes(true);  // 顯示箱子
				m_PRM->NextPhase();
				
				m_Phase = Phase::LEVELSELECT;
				m_PhaseChanged = true;

				// 初始化所有的箱子 (b1.png - b30.png)
				// 不過先設為不可見
				while (!m_PRM->AreAllBoxesAdded()) {
					m_PRM->AddNextLevelBox();
					auto box = m_PRM->GetLevelBoxes().back();
					box->SetVisible(false);  // 一開始設定為不可見
					m_Root.AddChildren({ box });
				}

				m_PRM->GetLevelBoxes()[0]->SetVisible(true);

				break;

			case Phase::LEVELSELECT:
				std::cout << "LEVELSELECT to LEVEL1" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->ShowLevelBoxes(false);
				//m_PRM->ShowNextLevelBox();
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL1;
				InitializeMap(GameMap1);
				BoxPass = 1;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL1:
				std::cout << "LEVEL1 to LEVEL2" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL2;
				InitializeMap(GameMap2);
				BoxPass = 1;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL2:
				std::cout << "LEVEL2 to LEVEL3" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL3;
				InitializeMap(GameMap3);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL3:
				std::cout << "LEVEL3 to LEVEL4" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL4;
				InitializeMap(GameMap4);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL4:
				std::cout << "LEVEL4 to LEVEL5" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL5;
				InitializeMap(GameMap5);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL5:
				std::cout << "LEVEL4 to LEVEL5" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL5;
				InitializeMap(GameMap5);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL6:
				std::cout << "LEVEL5 to LEVEL6" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL6;
				InitializeMap(GameMap6);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL7:
				std::cout << "LEVEL6 to LEVEL7" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL7;
				InitializeMap(GameMap7);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL8:
				std::cout << "LEVEL7 to LEVEL8" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL8;
				InitializeMap(GameMap8);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL9:
				std::cout << "LEVEL8 to LEVEL9" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL9;
				InitializeMap(GameMap9);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			case Phase::LEVEL10:
				std::cout << "LEVEL9 to LEVEL10" << std::endl;
				m_PRM->SetImage(RESOURCE_DIR"/Background/bg_game.png");
				m_PRM->NextPhase();
				m_Phase = Phase::LEVEL10;
				InitializeMap(GameMap10);
				BoxPass = 2;
				m_PhaseChanged = true;
				break;

			default:
				m_CurrentState = State::END;
		}
	}
}