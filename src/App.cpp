#include "App.hpp"

App::App()
{
    m_BGM = std::make_shared<Util::BGM>(RESOURCE_DIR"/BGM/BGM_ground.mp3");
    m_BGM->Play();
}