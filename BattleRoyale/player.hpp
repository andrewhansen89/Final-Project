#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "bullet.hpp"
#include "platform.hpp"
#include <vector>

class Player : public RectObject {
private:
    std::vector<Bullet> bulletVec;
    bool isDead;
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
public:
    // Create the player
    Player() : RectObject("Soldier.png", sf::Vector2f(rand() % 740 + 10, 550)) {
        isDead = false;
        isFiring = false;
        isJumping = false;
        jumpHeight = 150.f;
        maxVelocity = 8.f;
        acceleration = 2.f;
        drag = 0.5;
        groundHeight = 550;
        gravitySpeed = 0;
        multiplier = 60.f;

    }
    bool getIsDead() { return isDead; }
    void setIsDead(bool d) { isDead = d; }
    bool checkColl(Bullet bullet); // Check if the player's collided with a bullet
    void respawn() { this->setPos(sf::Vector2f(rand() % 740 + 10, 550)); }
    bool checkFeet(std::vector<Platform*> p); // Returns true if the player is on a platform, false if the player is not
    void move(sf::Vector2f distance);
    void move(float dt);
    void update(float dt, sf::Event e, sf::RenderWindow &w);
    void checkDrag(float dt);
    void allowGravity(std::vector<Platform*> p);
    void checkBullets(Player enemy, sf::RenderWindow &w);
};
