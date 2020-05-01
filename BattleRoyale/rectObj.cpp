#include "rectObj.hpp"

RectObject::RectObject(std::string file_name, sf::Vector2f p) {
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

int RectObject::getX() {
     if(isFlipped == true)
         return this->getLeft();
     else
         return this->getRight();
}
