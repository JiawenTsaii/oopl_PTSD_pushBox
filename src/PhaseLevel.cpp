#include "PhaseLevel.hpp"
#include "Util/Image.hpp"
#include "Core/Context.hpp"
#include <string>

PhaseLevel::PhaseLevel() {
    m_Background = std::make_shared<Character>();
    m_Background->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/bg_level_new.png"));
    m_Background->SetZIndex(0.0f);
    m_Root.AddChild(m_Background);
}

void PhaseLevel::Update() {
    m_Root.Update();
}

void PhaseLevel::AddBox() {
    if (m_BoxCount >= 30) return;

    // 創建新箱子
    auto box = std::make_shared<Character>();
    std::string boxPath = RESOURCE_DIR "/box" + std::to_string(m_BoxCount + 1) + ".png";
    box->SetDrawable(std::make_shared<Util::Image>(boxPath));

    // 設定箱子位置
    float yOffset = m_BoxCount * 50.0f;  // 每個箱子向下50f
    box->SetPosition({ 100.0f, 200.0f + yOffset });
    box->SetZIndex(1.0f + m_BoxCount * 0.1f);  // 箱子在背景的上面

    // 把箱子加上去
    m_Root.AddChild(box);
    m_Boxes.push_back(box);
    m_BoxCount++;
}
