#include "Character.hpp"

void Character::SetScale(float x, float y) {
    m_Transform.scale = glm::vec2(x, y);
}

void Character::SetPosition(float x, float y) {
    m_Transform.translation = glm::vec2(x, y);
}