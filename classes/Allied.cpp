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

int Allied::eraseTimeAction(sf::Sound sonido[5]) {
    //nada
    return 0;
}

int Allied::clickAction(sf::Sound sonido[5]) {
    int points = -100;
    std::cout << "Ally";
    sonido[3].play();
    return points;
}
