#pragma once
#include <vector>
#include "../classes/Agent.h"
#include "../classes/Enemy.h"
#include "../classes/Allied.h"
#include "../classes/Explosion.h"
#include <SFML/Audio.hpp>


class Level
{
public:
	sf::SoundBuffer buffer[5];
	sf::Sound kill[5];
	sf::Clock lUp;
	float levTime = 3;
	int points = 0;
	int lifes = 3;
	sf::Texture textureA;
	sf::Texture textureE;
	sf::Time del = sf::seconds(levTime);
	Level();
	~Level();
	void setSounds();
	void createAllied();
	void createEnemy();
	void deleteAtTime();
	void deleteAgent(const sf::Event& event, const sf::RenderWindow& window);
	void levelUp();
	void reset();
	void draw(sf::RenderWindow& window);
private:
	std::vector<Agent*> agents;
	std::vector<Enemy*> enemies;
	std::vector<Allied*> allies;
	//Estuve estudiando el uso de vectores con polimorfismo
	//Aplicaque un dinamic cast para tener a las clases hijas en otros vectores
	//por si desp queria seguir el juego y aplicar nuevas acciones
};

