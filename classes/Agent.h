#pragma once
#include <SFML/Graphics.hpp>

class Agent
{
public:
    sf::Sprite sprite;
    Agent(const sf::Texture& texture);
    void spawn();
    bool handleClick(const sf::Event& event, const sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

private:
    sf::Vector2f lastSpawnPosition;
};

