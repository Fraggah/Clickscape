#include "Level.h"
#include "../classes/Agent.h"
#include "iostream"
#include <SFML/Audio.hpp>

Level::Level() {
}

Level::~Level() {

}

void Level::setSounds() {
	if (!buffer[0].loadFromFile("./sounds/enemy1.ogg")) {
		std::cout << "error al cargar sonido enemy1";
	}
	if (!buffer[1].loadFromFile("./sounds/enemy2.ogg")) {
		std::cout << "error al cargar sonido enemy1";
	}
	if (!buffer[2].loadFromFile("./sounds/enemy3.ogg")) {
		std::cout << "error al cargar sonido enemy1";
	}
	if (!buffer[3].loadFromFile("./sounds/allied.ogg")) {
		std::cout << "error al cargar sonido enemy1";
	}
	if (!buffer[4].loadFromFile("./sounds/enemyx.ogg")) {
		std::cout << "error al cargar sonido enemy1";
	}
	for (int i = 0;i < 5; i++) {
		kill[i].setBuffer(buffer[i]);
		kill[i].setVolume(60);
	}
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
	for (Agent* agent : agents) {
		if (Allied* allied = dynamic_cast<Allied*>(agent)) {
			allies.push_back(allied);
		}
	}
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
	for (Agent* agent : agents) {
		if (Enemy* enemy = dynamic_cast<Enemy*>(agent)) {
			enemies.push_back(enemy);
		}
	}
}

void Level::deleteAtTime() {
	for (auto it = agents.begin(); it != agents.end(); ++it) {
		if ((*it)->deleteTimer.getElapsedTime() > sf::seconds(levTime)) {
			sf::Vector2f position = (*it)->sprite.getPosition();
			int resta = (*it)->eraseTimeAction(kill);
			lifes += resta;
			delete* it;
			it = agents.erase(it);
			break;
		}
	}
	
}

void Level::deleteAgent(const sf::Event& event, const sf::RenderWindow& window) {
	float expansion = 50.0f; //agrando la zona de deteccion del click  IA

	for (auto it = agents.begin(); it != agents.end(); ++it) {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::FloatRect bounds = (*it)->sprite.getGlobalBounds();
			bounds.left -= expansion;  //IA
			bounds.top -= expansion;  //IA
			bounds.width += 2 * expansion;  //IA
			bounds.height += 2 * expansion;  //IA

			if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {  //static_cast implementado por IA
				int suma = (*it)->clickAction(kill);
				points += suma;
				delete* it;
				it = agents.erase(it);
				break;
			}
		}
	}
}


void Level::levelUp() {
	if (lUp.getElapsedTime() > sf::seconds(37.5f)) {
		levTime /= 2;
		lUp.restart();
	}
}

void Level::reset() {
	lifes = 3;
	points = 0;
	levTime = 3;
	agents.clear();
	enemies.clear();
	allies.clear();
	lUp.restart();
}

void Level::draw(sf::RenderWindow& window) {
	for (const auto& a : this->agents) {
		window.draw(a->sprite);
	}
}

// la clase level se encarga de las acciones de crear enemigos, y aliados, maneja los puntos, vida y dificultad