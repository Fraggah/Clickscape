#include "Explosion.h"
#include <iostream>
Explosion::Explosion() {

}

Explosion::~Explosion() {

}

void Explosion::setTexture() {
	sf::Texture texplosion;
	if (!texplosion.loadFromFile("./assets/explosion.png")) {
		std::cout << "no carga explosion text";
	};
	sprite.setTexture(texplosion);
}

//no llegué a implementar explociones ecuando los bombas rojas explotan..