#include "player.hpp"

bool Player::checkColl(Bullet bullet) {
    if (bullet.intersects(this->getSprite())) { // if the sprites collide
        this->move(sf::Vector2f(0,10000)); // move the player off of the map coordinates
        return true;
        std::cout << "Hit target : ";
    }
    return false;
}

bool Player::checkFeet(std::vector<Platform*> p) {
   
    for(auto it: p) { // for all of the elements in the vector
        if (this->intersects(it->getSprite()) && this->getBottom() >= it->getTop() - 1)
            return true;
    }
    return false;
}

void Player::move(sf::Vector2f distance) {
    
    if ((this->getX() + distance.x > 0 && this->getX() + distance.x < 800)&(this->getY() + distance.y > 0 && this->getY() + distance.y < 600))
        sprite.move(distance);
}
