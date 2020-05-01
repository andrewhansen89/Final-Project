#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "ResourcePath.hpp"

class RectObject {
protected:
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Texture tex;
    sf::Sprite sprite;
    bool isFlipped;
public:
    RectObject(std::string file_name, sf::Vector2f p) {
        if(!tex.loadFromFile(resourcePath() + file_name)) {
            return EXIT_FAILURE;
        }
        sprite.setTexture(tex);
        pos = p;
        sprite.setPosition(pos);
        size.x = tex.getSize().x;
        size.y = tex.getSize().y;
        isFlipped = false;
    }
    
    // Moves the player based on the vector's distance
    void move(sf::Vector2f distance) { sprite.move(distance); }
    
    void getLength() { return size.x; }
    
    void getWidth() { return size.y; }
    
    void flipRight() { sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y)); }
       
    void flipLeft() { sprite.setTextureRect(sf::IntRect(size.x, 0, -size.x, size.y)); }
    
    void setIsFlipped(bool i) { isFlipped = i; }
    
    int getY() { return sprite.getPosition().y; }
    
    int getX() {
         if(isFlipped == true)
             return this->getLeft();
         else
             return this->getRight();
    }
    
    int getRight() { return sprite.getPosition().x + size.x; }

    int getLeft() { return sprite.getPosition().x; }

    int getTop() { return sprite.getPosition().y; }

    int getBottom() { return sprite.getPosition().y + size.y; }

    void setPos(sf::Vector2f newPos) { sprite.setPosition(newPos); }
    
    sf::Vector2f getPos() { return pos; }
    
    // virtual void update(float dt) = 0;
    void draw(sf::RenderWindow &window) { window.draw(sprite); }
    
    sf::Sprite getSprite() { return sprite; }
    
    bool intersects(sf::Sprite s) { return sprite.getGlobalBounds().intersects(s.getGlobalBounds()); }
};


