#pragma once
#include <SFML/Graphics.hpp>

class Explosion
{
public:
	sf::Clock clock;
	sf::Sprite sprite;
	Explosion();
	~Explosion();
	void setTexture();
};

