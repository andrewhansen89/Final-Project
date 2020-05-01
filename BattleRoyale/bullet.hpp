#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "rectObj.hpp"
#include "ResourcePath.hpp"


class Bullet : public RectObject{
private:
    bool isFlipped;
public:
    Bullet(sf::Vector2f p, bool i) : RectObject("Bullet.png", p) { isFlipped = i;}

    void update(int speed) {
        if (!isFlipped)
            this->sprite.move(speed, 0);
        else
            this->sprite.move(-speed, 0);
    }
};
