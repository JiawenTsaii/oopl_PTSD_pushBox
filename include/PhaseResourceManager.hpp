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

	// �]�m�ڸ`�I��k SetRoot(�o�ӬOGameObject���ޥ�)(�]�m�ڵ��I�O���F��K�޲z�Ҧ���GameObject)
	// SetRoot method to set the root node (this is a reference to GameObject) (setting the root node is to facilitate the management of all GameObjects)
	// �٨S���ܲM���o�b�F�� �W�������O���Ocopilot���ڼg�� �������� ����A���s��s�@�U
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

private:
    std::shared_ptr<BackgroundImage> m_Background;
    //std::shared_ptr<TaskText> m_TaskText;

    std::vector<std::shared_ptr<Character>> m_LevelBoxes;

    //Util::GameObject* m_pRoot = nullptr;
    Util::Renderer m_pRoot;

    int m_Phase = 0;    // 0: menu

    int m_AddedBoxCount = 0;
    static const int MAX_BOXES = 30;

};

#endif //PHASE_MANGER_HPP