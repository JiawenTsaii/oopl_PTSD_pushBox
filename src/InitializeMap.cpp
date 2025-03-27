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
    // 640-480=160，160/2=80，所以上下各空80
    // 第一個(左下角)箱子: (-150, -210)
    // SetPosition是設定中間的位置

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 6; j++) {
            int tile = GameMap[i][j];
            switch (tile) {
                case 1: // 牆壁
                {
                    auto wall = std::make_shared<Character>(RESOURCE_DIR"/Object/wall.png");
                    wall->SetZIndex(50);
                    wall->SetPosition({ -150 + 60 * j, 210 - 60 * i });
                    wall->SetVisible(false);
                    m_Wall.push_back(wall);
                    m_Root.AddChild(wall);
                }
                    break;
                case 2: // 空地
                {
                    auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
                    floor->SetZIndex(40);
                    floor->SetPosition({ -150 + 60 * j, 210 - 60 * i });
                    floor->SetVisible(false);
                    m_Floor.push_back(floor);
                    m_Root.AddChild(floor);
                }
                    break;
                case 3: // 箱子
                {
                    auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
                    floor->SetZIndex(40);
                    floor->SetPosition({ -150 + 60 * j, 210 - 60 * i });
                    floor->SetVisible(false);
                    m_Floor.push_back(floor);
                    m_Root.AddChild(floor);

                    m_Box = std::make_shared<Character>(RESOURCE_DIR"/Object/box.png");
                    m_Box->SetPosition({ -150 + 60 * j, 210 - 60 * i });
                    m_Box->SetVisible(false);
                    m_Box->SetZIndex(50);
                    m_Root.AddChild(m_Box);
                }
                    break;
                case 4: // 人物
                {
                    auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
                    floor->SetZIndex(40);
                    floor->SetPosition({ -150 + 60 * j, 210 - 60 * i });
                    floor->SetVisible(false);
                    m_Floor.push_back(floor);
                    m_Root.AddChild(floor);

                    m_Player = std::make_shared<Character>(RESOURCE_DIR"/Object/player_down.png");
                    m_Player->SetPosition({ -150 + 60 * j, 210 - 60 * i });
                    m_Player->SetVisible(false);
                    m_Player->SetZIndex(50);
                    m_Root.AddChild(m_Player);
                }
                    break;
                default:
                    break;
            }
        }
    }
}

