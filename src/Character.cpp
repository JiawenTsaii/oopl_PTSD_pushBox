#include "Character.hpp"
#include "Util/Image.hpp"

Character::Character(const std::string& ImagePath) {
    SetImage(ImagePath);
    ResetPosition();
}

void Character::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

bool Character::IfCollides(const std::shared_ptr<Character>& other) const {
    // 取得 this 的邊界框
    int this_width = m_Drawable->GetSize().x;
    int this_height = m_Drawable->GetSize().y;
    const glm::vec2& this_pos = GetPosition();

    // 取得 other 的邊界框
    int other_width = other->m_Drawable->GetSize().x;
    int other_height = other->m_Drawable->GetSize().y;
    const glm::vec2& other_pos = other->GetPosition();

    // 檢查 this 和 other 的邊界框是否重疊
    bool collisionX = this_pos.x < other_pos.x + other_width && this_pos.x + this_width > other_pos.x;
    bool collisionY = this_pos.y < other_pos.y + other_height && this_pos.y + this_height > other_pos.y;

    return collisionX && collisionY;
}