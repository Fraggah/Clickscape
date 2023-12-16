#include "Game.h"
#include "Level.h"
#include "Interface.h"
#include "../classes/ParticleSystem.h"
#include "../classes/Crosshair.h"
#include "../classes/Agent.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(1920, 1080), "Clickscape") {
	window.setFramerateLimit(60);
}

Game::~Game() {
}

void Game::run() {
	//Start

	if (!music.openFromFile("./sounds/theme.ogg"));
	if (!menuMusic.openFromFile("./sounds/menu.ogg"));
	if (!tmenu.loadFromFile("./assets/player1.png"));

	if (!tmenu2.loadFromFile("./assets/player2.png"));
	smenu.setTexture(tmenu);
	smenu.setScale(0.3f, 0.3f);
	smenu2.setTexture(tmenu2);
	smenu2.setScale(0.3f, 0.3f);
	sf::Vector2u size = tmenu.getSize();
	sf::Vector2u size2 = tmenu.getSize();
	smenu.setOrigin((size.x / 2) + 20, (size.y / 2) + 20);
	smenu2.setOrigin((size2.x / 2), (size2.y / 2));


	smenu.setPosition((window.getSize().x) / 2, (window.getSize().y) / 2);
	smenu2.setPosition(((window.getSize().x) / 2) - 20, ((window.getSize().y) / 2) - 22);

	if (!textureMira.loadFromFile("./assets/player1.png"));

	if (!textureMira2.loadFromFile("./assets/player2.png"));

	sf::RectangleShape lv1rect(sf::Vector2f(1920, 1080));


	if (!bshader.loadFromFile("./shaders/bshader.frag", sf::Shader::Fragment)) {
		std::cout << "Error al cargar el shader" << std::endl;
	}


	if (!sbshader.loadFromFile("./shaders/startbshader.frag", sf::Shader::Fragment)) {
		std::cout << "Error al cargar el shader" << std::endl;
	}

	if (!lv3shader.loadFromFile("./shaders/lv3shader.frag", sf::Shader::Fragment)) {
		std::cout << "Error al cargar el shader" << std::endl;
	}


	sf::RectangleShape lv2rect(sf::Vector2f(window.getSize()));
	sf::RectangleShape lv3rect(sf::Vector2f(window.getSize()));


	sf::Texture texture;
	if (!texture.loadFromFile("./assets/player1.png"));

	Enemy enemy;
	Level level;
	level.setSounds();
	Interface interface;
	Crosshair crosshair(textureMira, textureMira2);


	ParticleSystem particleSystem;

	font.loadFromFile("./assets/Prompt-Regular.ttf");
	text.setFont(font);
	text.setString("Clickscape");
	text.setCharacterSize(50);
	text.setPosition(825, 300);
	menuMusic.play();

	while (window.isOpen()) {  //Update
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		// Menu
		sbshader.setUniform("u_time", clock.getElapsedTime().asSeconds());
		sbshader.setUniform("u_resolution", sf::Glsl::Vec2(window.getSize().x, window.getSize().y));
		if (ismenu) {
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (smenu.getGlobalBounds().contains(mousePos.x, mousePos.y)); {
					ismenu = false;
					isgame = true;
					music.play();
					level.lUp.restart();
					cflash.restart();
				}
			}
		}

		// Game
		if (isgame)
		{
			window.setMouseCursorVisible(false);
			sf::Time elapsed = clock.getElapsedTime();
			bshader.setUniform("u_time", elapsed.asSeconds());
			bshader.setUniform("u_resolution", sf::Vector2f(1920, 1080));
			lv3shader.setUniform("time", elapsed.asSeconds());
			lv3shader.setUniform("resolution", sf::Vector2f(1920, 1080));
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			particleSystem.emitParticles(mousePos, particleSystem.randomColor());
			particleSystem.update();

			if (spawn.getElapsedTime() > sf::seconds(level.levTime)) {
				int randomValue = std::rand() % 2;
				if (randomValue == 0) {
					level.createAllied();
				}
				else {
					level.createEnemy();
				}
				spawn.restart();
			}

			crosshair.updatePosition(window, elapsed.asSeconds());
			level.deleteAgent(event, window);
			level.deleteAtTime();
			interface.setText(level.points, level.lifes);
			level.levelUp();
		}

		window.clear();		

		if (cflash.getElapsedTime() < lvtime) {
			window.draw(lv1rect, &sbshader);
		}
		else {
			window.draw(lv2rect, &bshader);
		}

		if (cflash.getElapsedTime() > lvtime2) {
			window.draw(lv3rect, &lv3shader);
		}
		

		if (ismenu) {
			window.draw(text);
			window.draw(smenu2);
			window.draw(smenu);
		}
		if (isgame) {
			particleSystem.draw(window);
			level.draw(window);
			enemy.drawEnemyDestroy(window);
			window.draw(crosshair.sprite2);
			window.draw(crosshair.sprite);
			interface.draw(window);
		}
		window.display();
	}
}