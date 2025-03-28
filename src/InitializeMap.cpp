#include "App.hpp"

#include <iostream>

void App::InitializeMap(const std::vector<std::vector<int>>& GameMap) {
    // 清空現有的地圖物件
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

    if (m_Box) {
        m_Root.RemoveChild(m_Box);
        m_Box.reset();
    }

    /* 複製 GameMap 到 m_GameMap */
	m_GameMap.assign(GameMap.begin(), GameMap.end());

    // 原點在中間，所以左下角是(-180, -320)
    // 640-320=320，320/2=160，所以上下各空160
    // 第一個(左下角)箱子: (-160, -140)
    // SetPosition是設定中間的位置

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 9; j++) {
            int tile = GameMap[i][j];
            switch (tile) {
                case 1: // 牆壁
                {
					/* 牆壁 */
                    auto wall = std::make_shared<Character>(RESOURCE_DIR"/Object/wall.png");
                    wall->SetZIndex(50);
                    wall->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    wall->SetVisible(false);
                    m_Wall.push_back(wall);
                    m_Root.AddChild(wall);
                }
                    break;
                case 2: // 空地
                {
                    /* 地板 */
                    auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
                    floor->SetZIndex(30);
                    floor->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    floor->SetVisible(false);
                    m_Floor.push_back(floor);
                    m_Root.AddChild(floor);
                }
                    break;
                case 3: // 箱子
                {
                    /* 地板 */
                    auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
                    floor->SetZIndex(30);
                    floor->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    floor->SetVisible(false);
                    m_Floor.push_back(floor);
                    m_Root.AddChild(floor);

                    /* 箱子 */
                    m_Box = std::make_shared<Character>(RESOURCE_DIR"/Object/box.png");
                    m_Box->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    m_Box->SetVisible(false);
                    m_Box->SetZIndex(50);
                    m_Root.AddChild(m_Box);
                }
                    break;
                case 4: // 人物
                {
                    /* 地板 */
                    auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
                    floor->SetZIndex(30);
                    floor->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    floor->SetVisible(false);
                    m_Floor.push_back(floor);
                    m_Root.AddChild(floor);

                    /* 人物 */
                    m_Player = std::make_shared<Character>(RESOURCE_DIR"/Object/player_down.png");
                    m_Player->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    m_Player->SetVisible(false);
                    m_Player->SetZIndex(50);
                    m_Root.AddChild(m_Player);
                }
                    break;
                case 5: // 目標點
                {
                    /* 地板 */
                    auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
                    floor->SetZIndex(30);
                    floor->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    floor->SetVisible(false);
                    m_Floor.push_back(floor);
                    m_Root.AddChild(floor);

                    /* 人物 */
                    m_Player = std::make_shared<Character>(RESOURCE_DIR"/Object/player_down.png");
                    m_Player->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    m_Player->SetVisible(false);
                    m_Player->SetZIndex(50);
                    m_Root.AddChild(m_Player);

                    /* 目標點 */
					m_Point = std::make_shared<Character>(RESOURCE_DIR"/Object/point.png");
                    m_Point->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    m_Point->SetVisible(false);
                    m_Point->SetZIndex(40);
                    m_Root.AddChild(m_Point);

                    /* 勾勾 */
					m_Check = std::make_shared<Character>(RESOURCE_DIR"/Object/check.png");
                    m_Check->SetPosition({ -160 + 40 * j, 140 - 40 * i });
                    m_Check->SetVisible(false);
                    m_Check->SetZIndex(60);
                    m_Root.AddChild(m_Check);
				}
				    break;
                default:
                    break;
            }
        }
    }
}

