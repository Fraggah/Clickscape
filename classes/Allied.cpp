#include "Allied.h"
#include <iostream>

Allied::Allied() {
}

Allied::~Allied() {
}

void Allied::setTexture(sf::Texture& alliedTexture) {
    sprite.setTexture(alliedTexture);
    sprite.setScale(0.7, 0.7);
}

void Allied::eraseTimeAction(int lifes) {
    //nada
}

int Allied::clickAction() {
    int points = -100;
    std::cout << "Ally";
    return points;
}