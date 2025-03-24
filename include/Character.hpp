#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
    explicit Character(const std::string& ImagePath);

    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    // TODO: Implement the collision detection
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Character>& other) const;

    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.
    
    //// 關卡選擇的部分的箱子處理
    void SetVisible(bool visible) { m_Visible = visible; }
    //void SetScale(const glm::vec2& scale) { m_Transform.scale = scale; }
    //[[nodiscard]] const glm::vec2& GetScale() const { return m_Transform.scale; }


private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
    //bool m_Visible = true;
};


#endif //CHARACTER_HPP
