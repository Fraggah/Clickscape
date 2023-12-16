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


int Enemy::eraseTimeAction(sf::Sound sonido[5]) {
    std::cout << "eliminado";
    sonido[4].play();
    return -1;
}

int Enemy::clickAction(sf::Sound sonido[5]) {
    int points = 50;
    std::cout << "Enemy";
    sonido[std::rand() % 3].play();
    return points;
}

void Enemy::drawEnemyDestroy(sf::RenderWindow& window) {
    for (const auto& e : this->explosions) {
        window.draw(e->sprite);
    }
}