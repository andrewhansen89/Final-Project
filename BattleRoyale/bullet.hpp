#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "rectObj.hpp"
#include "ResourcePath.hpp"


class Bullet : public RectObject{
private:
    bool isFlipped;
    int bulletSpeed;
public:
    Bullet(sf::Vector2f p, bool i) : RectObject("Bullet.png", p) {
        bulletSpeed = 6;
        isFlipped = i;
    }

    void update();
};
