#pragma once
#include "SFML/Graphics.hpp"

class Interface
{
public:
    sf::Font font;
    sf::Text text;
    sf::Text tlife;
    sf::Sprite life;
    Interface();
    ~Interface();
    void setText(int points, int lifes);
    void setLifes(sf::Texture texture);
    void draw(sf::RenderWindow& window);
};

