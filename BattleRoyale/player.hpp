#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "bullet.hpp"
#include "platform.hpp"
#include <vector>

class Player : public RectObject {
private:
    bool isDead;
public:
    // Create the player and draw it to the window
    Player() : RectObject("Soldier.png", sf::Vector2f(rand() % 740 + 10, 550)) { isDead = false; }
   
    bool getIsDead() { return isDead; }
    void setIsDead(bool d) { isDead = d; }
    
    bool checkColl(Bullet bullet) { // Check if the player's collided with a bullet
        if (bullet.intersects(this->getSprite())) {
            this->move(sf::Vector2f(10000,10000));
            isDead = true;
        }
    }
    
    bool respawn() { this->setPos(sf::Vector2f(rand() % 740 + 10, 550)); }
    // Returns true if the player is on a platform, false if the player is not
    
    bool checkFeet(std::vector<Platform*> p) {
        // Check platforms and make sure that the player is between the length of the platform, and right on top of it
        for(auto it: p) {
            if (this->intersects(it->getSprite()) && this->getBottom() >= it->getTop() - 1)
                return true;
        }
        return false;
    }
};
