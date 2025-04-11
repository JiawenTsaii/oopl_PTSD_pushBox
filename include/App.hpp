#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
//#include "Util/Text.hpp"

#include "Character.hpp"
#include "PhaseResourceManager.hpp"

//#include "InitializeMap.cpp"

class App {
public:
	//App();

    enum class State {
        START,
        UPDATE,
        END,
    };
    State GetCurrentState() const { return m_CurrentState; }

    void Start();
    void Update();
    void End();

private:
    void ValidTask();
	void InitializeMap(const std::vector<std::vector<int>>& GameMap);

private:
    enum class Phase {
        MENU,
        GAME,
        LEVELSELECT,
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        LEVEL5,
        LEVEL6,
        LEVEL7,
        LEVEL8,
        LEVEL9,
        LEVEL10,
        LEVEL11,
        LEVEL12,
        LEVEL13,
        LEVEL14,
        LEVEL15,
        LEVEL16,
        LEVEL17,
        LEVEL18,
        LEVEL19,
        LEVEL20,
        LEVEL21,
        LEVEL22,
        LEVEL23,
        LEVEL24,
        LEVEL25,
        LEVEL26,
        LEVEL27,
        LEVEL28,
        LEVEL29,
        LEVEL30,
        END,
    };

    State m_CurrentState = State::START;
	Phase m_Phase = Phase::MENU;

    bool m_PhaseChanged = false;

    std::shared_ptr<PhaseResourceManager> m_PRM;

    std::shared_ptr<Character> m_Player;
    std::shared_ptr<Character> m_Box;
    std::vector<std::shared_ptr<Character>> m_Wall;
	std::vector<std::shared_ptr<Character>> m_Floor;
    Util::Renderer m_Root;


    // std::string m_InputLevelNumber = ""; //兩位數輸入
    int m_CurrentMaxLevel = 0; //目前已經顯示出來的關卡有哪些了(破關到哪)
    void CheckKeyboardInput(); //作弊模式的數字輸入
    void SwitchToLevel(int levelNum); // 跳到對應的關卡



    bool m_EnterKeyWasPressed = false; // 追蹤enter 用來解決連續偵測到enter的問題
    int m_SelectedLevel = 0;  // 目前選擇的關卡
    //std::string m_TypedNumbers;  // 輸入的數字
    bool m_BackspaceWasPressed = false; // backspace
    // std::string m_TypedNumbers = "";  // 輸入的數字
    bool m_ShowingBoxes = false;  // 有沒有跑出箱子
    bool m_AllBoxesShown = false; // 所有箱子都出現



    std::vector<std::vector<int>> m_GameMap;

    /* 地圖 */
    /* 0:草地 1:牆壁 2:空地 3:箱子 4:人物*/
    std::vector<std::vector<int>> GameMap1 = {
        {1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 3, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 4, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1}
    };

    std::vector<std::vector<int>> GameMap2 = {
        {1, 1, 1, 1, 1, 1},
        {1, 2, 2, 3, 4, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 4, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1}
    };

    std::vector<std::vector<int>> GameMap12 = {
        {1, 1, 1, 1, 1, 1},
        {1, 2, 2, 3, 4, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1}
    };

    /* 目標點 */
    /* 0:草地 1:牆壁 2:空地 3:目標點 */
    std::vector<std::vector<int>> GoalMap = {
        {1, 1, 1, 1, 1, 1},
        {1, 2, 3, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1}
    };
};

#endif