#include "App.hpp"

#include <iostream>

//void App::InitializeMap(const std::vector<std::vector<int>>& GameMap) {
//	std::cout << "InitializeMap()" << std::endl;
//    for (int i = 7; i >= 0; i--) {
//        for (int j = 0; j < 6; j++) {
//            /* wall: 60*60 */
//            if (GameMap[i][j] == 1) {
//                auto wall = std::make_shared<Character>(RESOURCE_DIR"/Object/wall.png");
//                wall->SetZIndex(50);
//                wall->SetPosition({ -150 + 60 * j, -210 + 60 * i });
//                wall->SetVisible(false);
//                m_Wall.push_back(wall);
//                m_Root.AddChild(wall);
//            }
//            /* floor: 60*60 */
//            else if (GameMap[i][j] == 2) {
//                auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
//                floor->SetZIndex(50);
//                floor->SetPosition({ -150 + 60 * j, 210 - 60 * i });
//                floor->SetVisible(false);
//                m_Floor.push_back(floor);
//                m_Root.AddChild(floor);
//            }
//            /* box: 60*60 */
//            else if (GameMap[i][j] == 3) {
//                m_Box = std::make_shared<Character>(RESOURCE_DIR"/Object/box.png");
//                m_Box->SetPosition({ -150 + 60 * j, 210 - 60 * i });
//                m_Box->SetVisible(false);
//                m_Box->SetZIndex(50);
//                m_Root.AddChild(m_Box);
//            }
//            /* player: 高度60 */
//            else if (GameMap[i][j] == 4) {
//                m_Player = std::make_shared<Character>(RESOURCE_DIR"/Object/player_down.png");
//                m_Player->SetPosition({ -150 + 60 * j, 210 - 60 * i });
//                m_Player->SetVisible(false);
//                m_Player->SetZIndex(50);
//                m_Root.AddChild(m_Player);
//            }
//            // 還是要用這種寫法呢?
//            /*for (int i = 0; i < 3; ++i) {
//                m_Doors.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/Image/Character/door_close.png"));
//                m_Doors[i]->SetZIndex(5);
//                m_Doors[i]->SetPosition({ 205.5f - 80.f * i, -3.5f });
//                m_Doors[i]->SetVisible(false);
//                m_Root.AddChild(m_Doors[i]);
//            }*/
//        }
//    }
//}

void App::InitializeMap(const std::vector<std::vector<int>>& GameMap) {
    // 清空現有的地圖物件並從渲染樹中移除
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

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 6; j++) {
            int tile = GameMap[i][j];
            switch (tile) {
            case 1: // 牆壁
            {
                auto wall = std::make_shared<Character>(RESOURCE_DIR"/Object/wall.png");
                wall->SetZIndex(50);
                wall->SetPosition({ -150 + 60 * j, -210 + 60 * i });
                wall->SetVisible(false);
                m_Wall.push_back(wall);
                m_Root.AddChild(wall);
            }
            break;
            case 2: // 空地
            {
                auto floor = std::make_shared<Character>(RESOURCE_DIR"/Object/floor.png");
                floor->SetZIndex(50);
                floor->SetPosition({ -150 + 60 * j, 210 - 60 * i });
                floor->SetVisible(false);
                m_Floor.push_back(floor);
                m_Root.AddChild(floor);
            }
            break;
            case 3: // 箱子
            {
                m_Box = std::make_shared<Character>(RESOURCE_DIR"/Object/box.png");
                m_Box->SetPosition({ -150 + 60 * j, 210 - 60 * i });
                m_Box->SetVisible(false);
                m_Box->SetZIndex(50);
                m_Root.AddChild(m_Box);
            }
            break;
            case 4: // 人物
            {
                m_Player = std::make_shared<Character>(RESOURCE_DIR"/Object/player_floor.png");
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

