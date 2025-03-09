#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
    void SetScale(float x, float y);
    void SetPosition(float x, float y);
};

#endif //CHARACTER_HPP