#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "bullet.hpp"
#include "platform.hpp"
#include <vector>

class Player : public RectObject {
private:
    bool isDead;
<<<<<<< HEAD
    bool isFiring;
    bool isJumping;
    float jumpHeight;
    sf::Vector2f currentVelocity;
    sf::Vector2f direction;
    float maxVelocity;
    float acceleration;
    float drag;
    int groundHeight;
    float gravitySpeed;
    float multiplier;
    int timesJumped;
    int maxTimesJumped;
public:
    // Create the player
    Player();
=======
public:
    // Create the player and draw it to the window
    Player() : RectObject("Soldier.png", sf::Vector2f(rand() % 740 + 10, 550)) { isDead = false; }
>>>>>>> parent of f22fa5c... finished consolidating code
    bool getIsDead() { return isDead; }
    void setIsDead(bool d) { isDead = d; }
<<<<<<< HEAD
    bool checkColl(Bullet bullet, Player enemy); // Check if the player's collided with a bullet
    void respawn() { this->setPos(sf::Vector2f(rand() % 740 + 10, 550)); }
    bool checkFeet(std::vector<Platform*> p); // Returns true if the player is on a platform, false if the player is not
    void move(sf::Vector2f distance);
<<<<<<< HEAD
    void move(float dt);
    void update(float dt, sf::Event e, sf::RenderWindow &w);
    void checkDrag(float dt);
    void allowGravity(std::vector<Platform*> p);
    void checkBullets(Player enemy, sf::RenderWindow &w);
=======
    
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
            if (this->intersects(it->getSprite()) && this->getBottom() > it->getTop())
                return true;
        }
        return false;
    }
>>>>>>> parent of a6af7a6... Updated project
=======
>>>>>>> parent of f22fa5c... finished consolidating code
};
