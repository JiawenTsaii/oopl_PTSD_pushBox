#ifndef ANIMATED_CHARACTER_HPP
#define ANIMATED_CHARACTER_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"


class AnimatedCharacter : public Util::GameObject {

public:
    explicit AnimatedCharacter(const std::vector<std::string>& AnimationPaths);

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    [[nodiscard]] bool IfAnimationEnds() const;

    /* ----- 我是分割線 ----- */

    void Play() {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Play();
    }

    void Pause() {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Pause();
    }

    void SetCurrentFrame(std::size_t index) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetCurrentFrame(index);
    }

    void SetInterval(int interval) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetInterval(interval);
    }

    std::size_t GetCurrentFrameIndex() const {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return temp->GetCurrentFrameIndex();
    }

    std::size_t GetFrameCount() const {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return temp->GetFrameCount();
    }

    void SetPosition(const glm::vec2& position) {
        m_Transform.translation = position;
    }

    const glm::vec2& GetPosition() const {
        return m_Transform.translation;
    }
};

#endif //ANIMATED_CHARACTER_HPP
