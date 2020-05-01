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
    bool checkColl(Bullet bullet); // Check if the player's collided with a bullet
    void respawn() { this->setPos(sf::Vector2f(rand() % 740 + 10, 550)); }
    bool checkFeet(std::vector<Platform*> p); // Returns true if the player is on a platform, false if the player is not
    void move(sf::Vector2f distance);
};
