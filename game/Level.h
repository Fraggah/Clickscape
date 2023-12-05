#pragma once
#include <vector>
#include "../classes/Agent.h"

class Level
{
public:
	sf::Texture textureA;
	Level();
	~Level();
	void createAgent();
	void deleteAgent(const sf::Event& event, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
private:
	std::vector<Agent> agents;
};

