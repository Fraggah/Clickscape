#pragma once
#include <vector>
#include "../classes/Agent.h"
#include "../classes/Enemy.h"
#include "../classes/Allied.h"

class Level
{
public:
	int points = 0;
	int lifes = 10;
	sf::Texture textureA;
	sf::Texture textureE;
	sf::Time del = sf::seconds(2);
	Level();
	~Level();
	void createAllied();
	void createEnemy();
	void deleteAtTime();
	void deleteAgent(const sf::Event& event, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
private:
	std::vector<Agent*> agents;
};

