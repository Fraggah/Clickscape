#pragma once
#include "SFML/Graphics.hpp"

class Interface
{
public:
    sf::Font font;
    sf::Text text;
    sf::Text scorefinal;
    sf::Text gameOver;
    sf::Text yourScore;
    sf::Text tlife;
    sf::Sprite life;
    Interface();
    ~Interface();
    void setFont();
    void setGameover(int points);
    void setText(int points, int lifes);
    void setLifes(sf::Texture texture);
    void draw(sf::RenderWindow& window);
    void drawFinal(sf::RenderWindow& window);
};

//Manejo de la interfaz... aunque hay cosas que quedaron sueltas en la clase game