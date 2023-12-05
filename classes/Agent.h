#pragma once
#include <SFML/Graphics.hpp>

class Agent
{
public:
    sf::Sprite sprite;
    Agent();
    ~Agent();
    void setTexture(sf::Texture& texture);
};

