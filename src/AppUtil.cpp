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
			default:
				m_CurrentState = State::END;
		}
	}
}