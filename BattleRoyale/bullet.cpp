#include "bullet.hpp"

void Bullet::update() {
    if (!isFlipped)
        this->sprite.move(bulletSpeed, 0);
    else
        this->sprite.move(-bulletSpeed, 0);
}
