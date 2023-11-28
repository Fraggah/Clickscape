#include "Crosshair.h"

Crosshair::Crosshair(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2, size.y / 2);
}

void Crosshair::updatePosition(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sprite.setPosition(mousePos.x, mousePos.y);
}
