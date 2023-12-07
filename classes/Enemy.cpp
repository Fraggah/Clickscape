#include "Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::setTexture(sf::Texture& enemyTexture) {
    sprite.setTexture(enemyTexture);
    sprite.setScale(0.7, 0.7);
}
