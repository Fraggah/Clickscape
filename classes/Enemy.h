#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Agent.h"

class Enemy : public Agent {
public:
    Enemy();
    ~Enemy();
    void setTexture(sf::Texture& enemyTexture) override;
};

#endif