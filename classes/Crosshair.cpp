#include "Crosshair.h"
#include <cmath>

Crosshair::Crosshair(const sf::Texture& texture, const sf::Texture& texture2) {
    sprite.setTexture(texture);
    sprite.setScale(0.4f, 0.4f);
    sprite2.setTexture(texture2);
    sprite2.setScale(0.4f, 0.4f);
    sf::Vector2u size = texture.getSize();
    sf::Vector2u size2 = texture2.getSize();
    sprite.setOrigin((size.x / 2)+5,(size.y / 2)+5);
    sprite2.setOrigin(size2.x / 2, size2.y / 2); // Asegúrate de que el sprite2 también tenga su origen centrado
}

void Crosshair::updatePosition(const sf::RenderWindow& window, float elapsedTime) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sprite.setPosition(mousePos.x, mousePos.y);
    sprite2.setPosition(mousePos.x, mousePos.y);

    // Hacer que sprite2 rote constantemente
    float rotationSpeed1 = 0.3f; // Ajusta esto para cambiar la velocidad de rotación
    float rotationSpeed2 = 0.3f; // Ajusta esto para cambiar la velocidad de rotación
    float direction = sin(elapsedTime); // Cambia la dirección de la rotación con el tiempo
    sprite.rotate(rotationSpeed1);
    sprite2.rotate(rotationSpeed2 * direction * elapsedTime);
}