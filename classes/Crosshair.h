#pragma once
#include <SFML/Graphics.hpp>

class Crosshair {
public:
    sf::Sprite sprite;
    Crosshair(const sf::Texture& texture);
    void updatePosition(const sf::RenderWindow& window);
};
