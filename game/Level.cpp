#include "Level.h"
#include "../classes/Agent.h"
#include "iostream"


Level::Level() {

}

Level::~Level() {

}

void Level::createAllied() {
	Allied* a = nullptr;
	a = new Allied();
	if (!textureA.loadFromFile("./assets/allied.png")) {
		std::cout << "textura no cargada level" << std::endl;
	}
	a->setTexture(textureA);
	a->setPositions();
	this->agents.push_back(a);
}

void Level::createEnemy() {
	Enemy* e = nullptr;
	e = new Enemy();
	if (!textureE.loadFromFile("./assets/enemy.png")) {
		std::cout << "textura no cargada level" << std::endl;
	}
	e->setTexture(textureE);
	e->setPositions();
	this->agents.push_back(e);
}

void Level::deleteAtTime() {
	for (auto it = agents.begin(); it != agents.end(); ++it) {
		if ((*it)->deleteTimer.getElapsedTime() > del) {
			(*it)->eraseTimeAction(lifes);
			delete* it;
			it = agents.erase(it);
			break;
		}
	}
}

void Level::deleteAgent(const sf::Event& event, const sf::RenderWindow& window) {
    for (auto it = agents.begin(); it != agents.end(); ++it) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if ((*it)->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) { 
				int suma = (*it)->clickAction();
				points += suma;
				delete* it;
				it = agents.erase(it);
                break;
            }
        }
    }
}

void Level::draw(sf::RenderWindow& window) {
	for (const auto& a : this->agents) {
		window.draw(a->sprite);
	}
}