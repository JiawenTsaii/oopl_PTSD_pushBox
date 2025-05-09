#include "App.hpp"

#include "Util/Logger.hpp"

#include <iostream>

void App::Start() {
    LOG_TRACE("Start");
	//std::cout << "Start" << std::endl;
    
    /* Phase Resource Manager */
    m_PRM = std::make_shared<PhaseResourceManager>();
    m_Root.AddChildren(m_PRM->GetChildren());

	// 初始化計時器文字
	m_TimerText = std::make_shared<Util::Text>(
		RESOURCE_DIR"/Fonts/NotoSansTC-Regular.ttf",
		36,
		"00:00",
		Util::Color(255, 255, 255, 255),
		true
	);

	// 初始化計時器狀態
	m_TimerActive = false;
	m_RemainingTime = 0.0f;

	m_CurrentState = State::UPDATE;


    // 初始化剩餘步數
    m_RemainingSteps = 100;
    m_PRM->GetRemainingStepsText()->UpdatePosition(0.0F, 150.0F);
	m_PRM->GetRemainingStepsText()->SetVisible(false);
    m_PRM->SetRemainingStepsText(std::to_string(m_RemainingSteps));

    m_CurrentMaxLevel = 1; // 初始設定成已經解鎖第一關了

    m_CurrentState = State::UPDATE;
}

// void App::ResetTimer(float timeLimit) {
//     m_LevelHasTimeLimit = true;
//     m_LevelTimeLimit = timeLimit;
//     m_RemainingTime = timeLimit;
//     m_LevelStartTime = std::chrono::steady_clock::now();
//
//     // 創建時鐘顯示 (如果還沒有)
//     if (!m_ClockDisplay) {
//         m_ClockDisplay = std::make_shared<Character>(RESOURCE_DIR"/Object/clock.png");
//         m_ClockDisplay->SetPosition({0, 250});  // 放在畫面上方中間
//         m_ClockDisplay->SetZIndex(70);
//         m_Root.AddChild(m_ClockDisplay);
//     } else {
//         m_ClockDisplay->SetVisible(true);
//     }
//
//     // 創建時間文字顯示 (使用AnimatedCharacter)
//     // 注意：需要有數字圖片資源，如果沒有，需要先創建
//
//     // 暫時先用箱子代替時間顯示，實際上應該用數字圖片
//     if (!m_TimeText) {
//         m_TimeText = std::make_shared<Character>(RESOURCE_DIR"/Object/time_text.png");
//         m_TimeText->SetPosition({0, 250});  // 放在時鐘旁邊
//         m_TimeText->SetZIndex(71);
//         m_Root.AddChild(m_TimeText);
//     } else {
//         m_TimeText->SetVisible(true);
//     }
//
//     UpdateTimeDisplay();  // 初始化時間顯示
// }
//
// // 添加UpdateTimeDisplay函數的實現
// void App::UpdateTimeDisplay() {
//     if (!m_LevelHasTimeLimit) return;
//
//     // 計算剩餘時間
//     auto currentTime = std::chrono::steady_clock::now();
//     auto elapsedDuration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_LevelStartTime);
//     float elapsedSeconds = elapsedDuration.count() / 1000.0f;
//     m_RemainingTime = m_LevelTimeLimit - elapsedSeconds;
//
//     if (m_RemainingTime <= 0) {
//         m_RemainingTime = 0;
//         // 時間到，遊戲失敗
//         if (m_Phase != Phase::LOSE) {
//             m_Phase = Phase::LOSE;
//             m_PhaseChanged = false;
//             ValidTask();
//         }
//     }
//
//     // 更新時間顯示
//     // 假設我們有一個方法來更新數字顯示，例如：
//     int minutes = static_cast<int>(m_RemainingTime) / 60;
//     int seconds = static_cast<int>(m_RemainingTime) % 60;
//
//     // 更新時間顯示的文字或圖像
//     // 實際上，你可能需要根據你的UI系統實現這部分
//     std::string timeString = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
//     std::cout << "Time remaining: " << timeString << std::endl;
// }

