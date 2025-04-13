#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
//#include "Util/Text.hpp"

#include "Character.hpp"
#include "PhaseResourceManager.hpp"
#include "AnimatedCharacter.hpp"

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
        WIN,
        LOSE
    };

    State m_CurrentState = State::START;
	Phase m_Phase = Phase::MENU;

    bool m_PhaseChanged = false;

    std::shared_ptr<PhaseResourceManager> m_PRM;

    std::shared_ptr<Character> m_Player;
    std::vector<std::shared_ptr<Character>> m_Box_vec;
    std::vector<std::shared_ptr<Character>> m_Wall;
	std::vector<std::shared_ptr<Character>> m_Floor;
	std::vector<std::shared_ptr<Character>> m_Point_vec;
	std::vector<std::shared_ptr<Character>> m_Check_vec;
    
    /* 關卡選擇 */
    int m_CurrentMaxLevel = 0; //目前已經顯示出來的關卡有哪些了(破關到哪)
    //void CheckKeyboardInput(); //作弊模式的數字輸入
    //void SwitchToLevel(int levelNum); // 跳到對應的關卡

    bool m_EnterKeyWasPressed = false; // 追蹤enter 用來解決連續偵測到enter的問題
    int m_SelectedLevel = 0;  // 目前選擇的關卡
    bool m_BackspaceWasPressed = false; // backspace
    bool m_ShowingBoxes = false;  // 有沒有跑出箱子
    bool m_AllBoxesShown = false; // 所有箱子都出現

    //void HandleMouseClick(int x, int y);// 處理滑鼠點擊事件
    //bool IsClickOnBox(int x, int y, const std::shared_ptr<Character>& box);    // 檢查點擊是否在箱子上
    bool m_MouseLeftButtonWasPressed = false;
    int m_LastClickedLevel = 0;  // 記錄上次點擊的關卡
    std::chrono::steady_clock::time_point m_LastClickTime;
    std::chrono::steady_clock::time_point m_PrevClickTime;

    bool m_ShiftKeyWasPressed = false;

    /* 讀人的位置 */
    bool isPlayerOnCheck = false;
    int m_PlayerPosition_i = 0;
    int m_PlayerPosition_j = 0;

    /* 讀箱子的位置 */
    std::vector<bool> isBoxOnCheck;

    /* 過關條件 */
    int BoxOnCheckCount = 0;
    int BoxPass = 0;

    Util::Renderer m_Root;

    std::vector<std::vector<int>> m_GameMap;

    /* 地圖 */
    /* 0:草地 1:牆壁 2:空地 3:箱子 4:人物 5:目標點*/
    std::vector<std::vector<int>> GameMap1 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 2, 2, 3, 2, 5, 1, 0},
        {0, 1, 2, 2, 1, 1, 1, 1, 0},
        {0, 1, 2, 4, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 0},
    };

    std::vector<std::vector<int>> GameMap2 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 2, 2, 4, 2, 2, 1, 0},
        {0, 1, 2, 2, 2, 2, 2, 1, 0},
        {0, 1, 2, 2, 2, 3, 5, 1, 0},
        {0, 1, 2, 2, 2, 2, 2, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
    };

	std::vector<std::vector<int>> GameMap3 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 5, 3, 2, 1, 0},
        {0, 1, 2, 2, 2, 2, 2, 1, 0},
        {0, 1, 2, 2, 2, 2, 2, 1, 0},
        {0, 1, 2, 2, 3, 5, 2, 1, 0},
        {0, 1, 4, 2, 2, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
	};
};

#endif