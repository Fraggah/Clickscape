#include "Enemy.h"
#include <iostream>

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::setTexture(sf::Texture& enemyTexture) {
    sprite.setTexture(enemyTexture);
    sprite.setScale(0.7, 0.7);
}

void Enemy::eraseTimeAction(int lifes) {
    lifes--;
}

int Enemy::clickAction() {
    int points = 50;
    std::cout << "Enemy";
    return points;
}