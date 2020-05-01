#pragma once

#include <SFML/Graphics.hpp>
#include "rectObj.hpp"


class Platform : public RectObject {
public:
    Platform(std::string file_name, sf::Vector2f pos) : RectObject(file_name, pos) { }
};

class SmallPlatform : public Platform {
public:
    SmallPlatform(sf::Vector2f pos) : Platform("Platform-Small.png", pos) { }
};

class MidPlatform : public Platform {
public:
    MidPlatform(sf::Vector2f pos) : Platform("Platform-Mid.png", pos) { }
};

class FullPlatform : public Platform {
public:
    FullPlatform(sf::Vector2f pos) : Platform("Platform-Full.png", pos) { }
};



