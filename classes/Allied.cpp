#include "Allied.h"

Allied::Allied() {
}

Allied::~Allied() {
}

void Allied::setTexture(sf::Texture& alliedTexture) {
    sprite.setTexture(alliedTexture);
    sprite.setScale(0.7, 0.7);
}
