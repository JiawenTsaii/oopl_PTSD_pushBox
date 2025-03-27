#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManager.hpp"
#include "AnimatedCharacter.hpp"

class App {
public:
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

private:
    enum class Phase {
        MENU,
        LEVEL,
        GAME,
    };

    State m_CurrentState = State::START;
	Phase m_Phase = Phase::MENU;
    std::shared_ptr<PhaseResourceManager> m_PRM;
    Util::Renderer m_Root;
	bool m_EnterKeyWasPressed = false; // 追蹤enter 用來解決連續偵測到enter的問題

    int m_SelectedLevel = 0;  // 目前選擇的關卡
    //std::string m_TypedNumbers;  // 輸入的數字
};

#endif
