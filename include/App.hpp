#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Util/Text.hpp"
#include "Util/Time.hpp"
#include "Util/BGM.hpp"

#include "Character.hpp"
#include "PhaseResourceManager.hpp"
#include "AnimatedCharacter.hpp"
#include "TaskText.hpp"

class App {
public:
	App();

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
    std::shared_ptr<Util::BGM> m_BGM = nullptr;

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
    
    bool m_EnterKeyWasPressed = false; // 追蹤enter 用來解決連續偵測到enter的問題
    int m_SelectedLevel = 0;  // 目前選擇的關卡
    bool m_BackspaceWasPressed = false; // backspace
    bool m_ShowingBoxes = false;  // 有沒有跑出箱子
    bool m_AllBoxesShown = false; // 所有箱子都出現

    bool m_MouseLeftButtonWasPressed = false;
    int m_LastClickedLevel = 0;  // 記錄上次點擊的關卡
    std::chrono::steady_clock::time_point m_LastClickTime;
    std::chrono::steady_clock::time_point m_PrevClickTime;

	std::shared_ptr<Character> btn_return; // 返回鍵
	std::shared_ptr<Character> btn_reset; // 重置鍵

	int TextLevel = 0; // 要顯示哪個關卡的字

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
    bool allPointsHaveBoxes = false;
    bool m_LevelCompleted = false; // 紀錄關卡完成了沒 之後用在SELECTLEVEL階段要出線多少個箱子的部分

    bool Lose = false; // 紀錄是否輸了->跳Phase::LOSE

    Util::Renderer m_Root;

    std::vector<std::vector<int>> m_GameMap;

    /* 時間限制相關 */
    bool m_TimeLimited = false;          // 是否有時間限制
    int m_TimeLimit = 10;                // 時間限制（秒）
    int m_RemainingTime = 0;             // 剩餘時間（秒）
    std::chrono::steady_clock::time_point m_LastTimeUpdate; // 上次更新時間
    std::shared_ptr<TaskText> m_TimeText;  // 顯示時間的文字

    // 更新計時器
    void UpdateTimer();

    /* 步數限制 */
    int m_RemainingSteps = 100;   // 初始剩餘步數

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

    std::vector<std::vector<int>> GameMap4 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 1, 1, 1, 0, 1, 5, 2, 1},
        {0, 1, 4, 1, 1, 1, 2, 2, 1},
        {1, 1, 2, 2, 2, 2, 2, 2, 1},
        {1, 5, 2, 2, 3, 2, 3, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
    };

    std::vector<std::vector<int>> GameMap5 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 2, 2, 1, 0, 0},
        {0, 1, 4, 2, 5, 3, 1, 1, 0},
        {0, 1, 2, 2, 2, 3, 2, 1, 0},
        {0, 1, 2, 1, 5, 2, 2, 1, 0},
        {0, 1, 2, 2, 2, 2, 2, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
    };

    std::vector<std::vector<int>> GameMap6 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 4, 2, 2, 1, 1, 0},
        {0, 1, 2, 2, 1, 2, 2, 1, 0},
        {0, 1, 2, 3, 3, 2, 2, 1, 0},
        {0, 1, 2, 2, 5, 2, 2, 1, 0},
        {0, 1, 1, 2, 5, 2, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
    };

    std::vector<std::vector<int>> GameMap7 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 2, 2, 2, 2, 1, 1, 1, 0},
        {1, 2, 2, 2, 2, 5, 2, 1, 0},
        {1, 2, 2, 3, 3, 4, 2, 1, 0},
        {1, 2, 2, 1, 2, 5, 2, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
    };

    std::vector<std::vector<int>> GameMap8 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 5, 2, 2, 1, 1, 1, 0},
        {1, 2, 2, 1, 2, 3, 4, 1, 0},
        {1, 2, 2, 1, 2, 1, 2, 1, 0},
        {1, 2, 2, 2, 2, 3, 5, 1, 0},
        {1, 2, 2, 2, 2, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0},
    };

    std::vector<std::vector<int>> GameMap9 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 4, 2, 2, 2, 1, 1, 0},
        {0, 1, 2, 3, 1, 2, 2, 1, 0},
        {0, 1, 2, 3, 2, 5, 2, 1, 0},
        {0, 1, 5, 2, 2, 2, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0},
    };

    std::vector<std::vector<int>> GameMap10 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 2, 2, 2, 2, 1, 1, 0},
        {1, 2, 5, 5, 2, 2, 2, 1, 0},
        {1, 2, 1, 2, 3, 3, 2, 1, 0},
        {1, 2, 2, 2, 1, 4, 2, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
    };
};

#endif

