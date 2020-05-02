#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "rectObj.hpp"
#include "ResourcePath.hpp"


class Bullet : public RectObject{
private:
    bool isFlipped;
public:
<<<<<<< HEAD
    Bullet(sf::Vector2f p, bool i) : RectObject("Bullet.png", p) {
        bulletSpeed = 6;
        isFlipped = i;
    }

    void update();
=======
    Bullet(sf::Vector2f p, bool i) : RectObject("Bullet.png", p) { isFlipped = i;}

    void update(int speed) {
        if (!isFlipped)
            this->sprite.move(speed, 0);
        else
            this->sprite.move(-speed, 0);
    }
>>>>>>> parent of f22fa5c... finished consolidating code
};
