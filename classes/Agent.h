#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_set>
#include <ctime>

struct Position {
    int posx;
    int posy;
};

class Agent
{
public:
    sf::Clock deleteTimer;
    sf::Sprite sprite;
    std::vector<Position> positions = {
    {325, 200}, {725, 200}, {1125, 200}, {1525, 200},
    {325, 500}, {725, 500}, {1125, 500}, {1525, 500},
    {325, 800}, {725, 800}, {1125, 800}, {1525, 800}
    };
    std::unordered_set<int> usedIndex;
    int randomIndex = std::rand() % 12;
    Agent();
    virtual ~Agent();
    virtual void setTexture(sf::Texture& texture);
    void setPositions();
    virtual int eraseTimeAction(sf::Sound sonido[5]);
    virtual int clickAction(sf::Sound sonido[5]);
};

