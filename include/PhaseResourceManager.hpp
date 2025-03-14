#ifndef PHASE_MANAGER_HPP
#define PHASE_MANAGER_HPP

#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "BackgroundImage.hpp"
#include "TaskText.hpp"
#include <memory>
#include <vector>
#include <string>

namespace Util {
    class GameObject;  // 前向宣告
}

class PhaseResourceManager {
public:
    PhaseResourceManager();

    // 設置根節點方法
    void SetRoot(Util::GameObject& root);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return { m_Background };
    }

    [[nodiscard]] std::vector<std::shared_ptr<Character>> GetLevelBoxes() const;

    void NextPhase();
    void SetImage(const std::string& filepath);

    void CreateLevelBoxes();

private:
    std::shared_ptr<BackgroundImage> m_Background;
    //std::shared_ptr<TaskText> m_TaskText;

    std::vector<std::shared_ptr<Character>> m_LevelBoxes;

    //Util::GameObject* m_pRoot = nullptr;
    Util::Renderer m_pRoot;

    int m_Phase = 0;    // 0: menu
};

#endif //PHASE_MANGER_HPP