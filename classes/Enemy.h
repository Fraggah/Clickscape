#pragma once

#include "Agent.h"
#include "Explosion.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Enemy : public Agent {
public:
    sf::Time timer = sf::seconds(1);
    Enemy();
    ~Enemy();
    void setTexture(sf::Texture& enemyTexture) override;
    virtual int eraseTimeAction(sf::Sound sonido[5]) override;
    virtual int clickAction(sf::Sound sonido[5]) override;
    void drawEnemyDestroy(sf::RenderWindow& window);
private:
    std::vector<Explosion*> explosions;
};

