#include "Agent.h"

#include <cstdlib>

Agent::Agent(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setScale(0.7f, 0.7f);
}

Agent::~Agent() {

}

void Agent::spawn() {
    lastSpawnPosition = sprite.getPosition();  // Almacena la posición actual antes de cambiarla
    sprite.setPosition(rand() % 1800 + 50, rand() % 950 + 50);
}

bool Agent::handleClick(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            spawn();
            return true;
        }
    }
    return false;
}

sf::Vector2f Agent::getSize() const {
    return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

sf::Vector2f Agent::getPosition() const {
    return lastSpawnPosition;  // Devuelve la última posición de spawn
}
