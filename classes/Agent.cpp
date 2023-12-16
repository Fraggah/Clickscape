#include "Agent.h"
#include <iostream>

Agent::Agent() {
    std::srand(static_cast<unsigned>(std::time(0)));  //Intento de no repetir posiciones seguidas pero no funcionó (IA)
    usedIndex.clear();                                //Lo solucioné cambiando la logica de aparicion de elementos
    randomIndex = std::rand() % positions.size();
    usedIndex.insert(randomIndex);
}

Agent::~Agent() {
}

void Agent::setTexture(sf::Texture& texture) {
    sprite.setTexture(texture);
}

void Agent::setPositions() {
    if (usedIndex.size() < positions.size() - 1) {
        int newRandomIndex;
        do {
            newRandomIndex = std::rand() % positions.size();
        } while (usedIndex.count(newRandomIndex) > 0);

        usedIndex.insert(newRandomIndex);
        randomIndex = newRandomIndex;
    }
    else {
        usedIndex.clear();
    }

    sf::Vector2f positionVector(positions[randomIndex].posx, positions[randomIndex].posy);
    sprite.setPosition(positionVector);
}

int Agent::eraseTimeAction(sf::Sound sonido[4]) {
    //nada?
    return 0;
}

int Agent::clickAction(sf::Sound sonido[5]) {
    std::cout << "Agent";
    return 0;
}
