#pragma once
#include <SFML/Graphics.hpp>

class Crosshair {
public:
    sf::Sprite sprite;
    sf::Sprite sprite2;
    Crosshair(const sf::Texture& texture, const sf::Texture& texture2);
    void updatePosition(const sf::RenderWindow& window, float elapsedTime);
};
