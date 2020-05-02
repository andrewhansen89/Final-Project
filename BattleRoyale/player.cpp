#include "player.hpp"

Player::Player() : RectObject("Soldier.png", sf::Vector2f(rand() % 740 + 10, 550)) {
    isDead = false;
    isFiring = false;
    isJumping = false;
    jumpHeight = 150.f;
    maxVelocity = 7.f;
    acceleration = 2.f;
    drag = 0.5f;
    groundHeight = 550;
    gravitySpeed = 0;
    multiplier = 60.f;
    timesJumped = 0;
    maxTimesJumped = 2;
}

bool Player::checkColl(Bullet bullet, Player enemy) {

    if (enemy.intersects(bullet.getSprite())) { // if the sprites collide
        enemy.move(sf::Vector2f(10000,10000)); // move the player off of the map coordinates
        return true;
        std::cout << "Hit target : ";
    }
    return false;
}

bool Player::checkFeet(std::vector<Platform*> p) {
   
    for(auto it: p) { // for all of the elements in the vector
        if (this->intersects(it->getSprite()) && this->getBottom() >= it->getTop() - 1) {
            gravitySpeed = 0;
            return true;
        }
    }
    return false;
}

<<<<<<< HEAD
void Player::move(sf::Vector2f distance) { sprite.move(distance); }

void Player::move(float dt) {
    
    this->move(sf::Vector2f(currentVelocity.x * dt * multiplier, currentVelocity.y));
    currentVelocity.y = 0.f;
}

void Player::update(float dt, sf::Event e, sf::RenderWindow &w) {
    
    direction = sf::Vector2f(0, 0);
    if ((e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::W) && (isJumping == false && timesJumped < maxTimesJumped)) { // If the player presses W, jump.
        isJumping = true;
        timesJumped++;
        gravitySpeed = 4;
        direction.y = -1.f;
        currentVelocity.y = -jumpHeight;
    }
    if (e.type == sf::Event::KeyPressed && e.key.code ==  sf::Keyboard::D) { // If the player presses D then move right
        this->flipRight();
        isFlipped = false;
        direction.x = 1.f;
        if (currentVelocity.x < maxVelocity)
            currentVelocity.x += acceleration * direction.x * dt * multiplier;
    }
    if (e.type == sf::Event::KeyPressed && e.key.code ==  sf::Keyboard::A) { // If the player presses A, move left
        this->flipLeft();
        isFlipped = true;
        direction.x = -1.f;
    }
    if (currentVelocity.x > -maxVelocity)
       currentVelocity.x += acceleration * direction.x * dt * multiplier;
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
        isFiring = true;
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R ) {
        if (this->getIsDead())
            this->respawn();
    }
    if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)) // stop running the game
        w.close();

    checkDrag(dt);
}

void Player::checkDrag(float dt) {

    if(currentVelocity.x > 0.f) {
        currentVelocity.x -= drag * dt * multiplier;
        if (currentVelocity.x < 0.f)
            currentVelocity.x = 0.f;
    }
    else if (currentVelocity.x < 0.f) {
        currentVelocity.x += drag * dt * multiplier;
        if (currentVelocity.x > 0.f)
            currentVelocity.x = 0.f;
    }
    if(currentVelocity.y > 0.f) {
        currentVelocity.y -= drag * dt * multiplier;
        if (currentVelocity.y < 0.f)
            currentVelocity.y = 0.f;
    }
    else if (currentVelocity.y < 0.f) {
        currentVelocity.y += drag * dt * multiplier;
        if (currentVelocity.y > 0.f)
            currentVelocity.y = 0.f;
    }
}

void Player::allowGravity(std::vector<Platform*> p) {
    
    if (this->checkFeet(p) == false && this->getTop() < groundHeight){
        gravitySpeed = 4;
        this->move(sf::Vector2f(0, gravitySpeed));
        isJumping = false;
    }
    else {
        isJumping = false;
        gravitySpeed = 0;
        timesJumped = 0;
    }
}

void Player::checkBullets(Player enemy, sf::RenderWindow &w) {
    
    if (isFiring == true) {
        Bullet newBullet(sf::Vector2f(this->getX(), this->getTop() + 10), isFlipped);
        bulletVec.push_back(newBullet);
        isFiring = false;
    }
    // Looping through the bullet vector and updating all of them
    for (int i = 0; i < bulletVec.size(); i++) {
        bulletVec[i].draw(w);
        bulletVec[i].update();
    }
    // Checking for collisions
    for (int i = 0; i < bulletVec.size(); i++) {
        if(this->checkColl(bulletVec[i], enemy))
            enemy.setIsDead(true);
    }
=======
void Player::move(sf::Vector2f distance) {
    
    if ((this->getX() + distance.x > 0 && this->getX() + distance.x < 800)&(this->getY() + distance.y > 0 && this->getY() + distance.y < 600))
        sprite.move(distance);
>>>>>>> parent of f22fa5c... finished consolidating code
}
