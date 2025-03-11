#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManager.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };
    State GetCurrentState() const { return m_CurrentState; }

    int m_BoxCount = 0;  // 選擇關卡的部分 紀錄已經出現的箱子數量
    std::vector<std::shared_ptr<Character>> m_Boxes;  //用來放箱子 的vector

    void Start();
    void Update();
    void End();


private:
    void ValidTask();

private:
    enum class Phase {
        MENU,
        LEVEL,
    };

    State m_CurrentState = State::START;
	Phase m_Phase = Phase::MENU;

    std::shared_ptr<PhaseResourceManager> m_PRM;

    Util::Renderer m_Root;
};

#endif
