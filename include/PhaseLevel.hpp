#ifndef PHASE_LEVEL_HPP
#define PHASE_LEVEL_HPP

#include "Core/Phase.hpp"
#include "Character.hpp"
#include <vector>
#include <memory>

class PhaseLevel : public Phase {
public:
    PhaseLevel();
    void Update() override;
    void AddBox();

private:
    std::shared_ptr<Character> m_Background;
    std::vector<std::shared_ptr<Character>> m_Boxes;  // 拿來紀錄箱子的東東
    int m_BoxCount = 0;  // 紀錄目前已經有多少箱子
};

#endif
