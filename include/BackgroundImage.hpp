#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

#include <iostream>

class BackgroundImage : public Util::GameObject {
public:
    BackgroundImage() : GameObject(
        std::make_unique<Util::Image>(RESOURCE_DIR"/bg_menu.png"), -10) {
        std::cout << "Creating BackgroundImage" << std::endl;
    }

    void NextPhase(const int phase) {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(ImagePath(phase));
    }

	void SetImage(const std::string& filepath) {
		auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
		temp->SetImage(filepath);
	}

private:
    inline std::string ImagePath(const int phase) {
        return RESOURCE_DIR"/phase" + std::to_string(phase) + ".png";
    }
};

#endif //BACKGROUND_IMAGE_HPP