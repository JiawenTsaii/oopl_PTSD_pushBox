#ifndef PHASEMENU_HPP
#define PHASEMENU_HPP

#include "Phase.hpp"
#include "Util/Renderer.hpp"

class PhaseMenu : public Phase {
public:
    PhaseMenu();
    void Update() override;

private:
    Util::Renderer m_Root;
};

#endif //PHASEMENU_HPP