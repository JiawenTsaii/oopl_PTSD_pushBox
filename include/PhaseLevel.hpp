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
    std::vector<std::shared_ptr<Character>> m_Boxes;  // ���Ӭ����c�l���F�F
    int m_BoxCount = 0;  // �����ثe�w�g���h�ֽc�l
};

#endif
