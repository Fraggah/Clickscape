#include "Agent.h"

#include <cstdlib>

Agent::Agent() {
}

Agent::~Agent() {

}

void Agent::setTexture(sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setScale(0.7f, 0.7f);
    sprite.setPosition(rand() % 1800 + 50, rand() % 950 + 50);
}
