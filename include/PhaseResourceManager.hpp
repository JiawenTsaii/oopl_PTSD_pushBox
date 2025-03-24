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
    class GameObject;
}

class PhaseResourceManager {
public:
    PhaseResourceManager();

	// 設置根節點方法 SetRoot(這個是GameObject的引用)(設置根結點是為了方便管理所有的GameObject)
	// SetRoot method to set the root node (this is a reference to GameObject) (setting the root node is to facilitate the management of all GameObjects)
	// 還沒有很清楚這在幹嘛 上面的註記都是copilot幫我寫的 哈哈哈哈 之後再重新研究一下
    void SetRoot(Util::GameObject& root);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return { m_Background };
    }

    [[nodiscard]] std::vector<std::shared_ptr<Character>> GetLevelBoxes() const;

    void NextPhase();
    void SetImage(const std::string& filepath);

    void CreateLevelBoxes();
    void AddNextLevelBox();
    bool AreAllBoxesAdded() const;

    // 關卡選擇的部分的箱子處理
    void ShowLevelBoxes(bool visible);
    //void HighlightBox(int boxNumber);

private:
    std::shared_ptr<BackgroundImage> m_Background;
    std::vector<std::shared_ptr<Character>> m_LevelBoxes;

    Util::Renderer m_pRoot;
    int m_Phase = 0;    // 0: menu

    int m_AddedBoxCount = 0;
    static const int MAX_BOXES = 30;

    // 關卡選擇的部分的箱子處理
    std::chrono::time_point<std::chrono::system_clock> m_HighlightStartTime;
    int m_HighlightedBoxIndex = -1;
    bool m_IsHighlighting = false;
    glm::vec2 m_OriginalBoxSize;

};

#endif //PHASE_MANGER_HPP