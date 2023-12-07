#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game();
    void run();
    sf::Clock spawn;
    sf::Time spawnTime = sf::seconds(1);

private:
    sf::RenderWindow window;
};

