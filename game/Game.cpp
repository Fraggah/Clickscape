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
	// 
	//Cargas
	if (!music.openFromFile("./sounds/theme.ogg"));
	if (!trap.openFromFile("./sounds/trap.ogg"));
	if (!menuMusic.openFromFile("./sounds/menu.ogg"));
	if (!tmenu.loadFromFile("./assets/player1.png"));
	if (!tmenu2.loadFromFile("./assets/player2.png"));
	if (!textureMira.loadFromFile("./assets/player1.png"));
	if (!textureMira2.loadFromFile("./assets/player2.png"));
	if (!tlmao.loadFromFile("./assets/trap.png"));

	//Menu... deberia ir en interfaz, no llego a pasarlo
	smenu.setTexture(tmenu);
	smenu.setScale(0.3f, 0.3f);
	smenu2.setTexture(tmenu2);
	smenu2.setScale(0.3f, 0.3f);
	sf::Vector2u size = tmenu.getSize();
	sf::Vector2u size2 = tmenu.getSize();
	smenu.setOrigin((size.x / 2) + 20, (size.y / 2) + 20);
	smenu2.setOrigin((size2.x / 2), (size2.y / 2));

	lmao.setTexture(tlmao);

	//Shaders
	sf::RectangleShape lv1rect(sf::Vector2f(1920, 1080));
	sf::RectangleShape lv2rect(sf::Vector2f(window.getSize()));
	sf::RectangleShape lv3rect(sf::Vector2f(window.getSize()));

	
	if (!bshader.loadFromFile("./shaders/bshader.frag", sf::Shader::Fragment)) {
		std::cout << "Error al cargar el shader" << std::endl;
	}

	if (!sbshader.loadFromFile("./shaders/startbshader.frag", sf::Shader::Fragment)) {
		std::cout << "Error al cargar el shader" << std::endl;
	}

	if (!lv3shader.loadFromFile("./shaders/lv3shader.frag", sf::Shader::Fragment)) {
		std::cout << "Error al cargar el shader" << std::endl;
	}

	//Instancias
	Enemy enemy;
	Level level;	
	Interface interface;
	Crosshair crosshair(textureMira, textureMira2);
	ParticleSystem particleSystem;

	//seteo
	interface.setFont();
	interface.setLifes(tmenu);
	level.setSounds();

	//Titulo... deberia ir en interfaz, pero no llego XD
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
		
		sf::Time elapsed = clock.getElapsedTime();

		// Enlace de Uniform Shaders
		sbshader.setUniform("u_time", clock.getElapsedTime().asSeconds());
		sbshader.setUniform("u_resolution", sf::Glsl::Vec2(window.getSize().x, window.getSize().y));
		bshader.setUniform("u_time", elapsed.asSeconds());
		bshader.setUniform("u_resolution", sf::Vector2f(1920, 1080));
		lv3shader.setUniform("time", elapsed.asSeconds());
		lv3shader.setUniform("resolution", sf::Vector2f(1920, 1080));

		//Menu
		if (ismenu) {
			smenu.setPosition((window.getSize().x) / 2, (window.getSize().y) / 2);
			smenu2.setPosition(((window.getSize().x) / 2) - 20, ((window.getSize().y) / 2) - 22);

			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (smenu.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
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

			if (level.lifes == 0) {
				isgame = false;
				isend = true;
			}
			if (cflash.getElapsedTime() > sf::seconds(120)){
				isgame = false;
				notend = true;
			}

		}

		if (isend) {
			window.setMouseCursorVisible(true);
			music.stop();
			menuMusic.play();
			interface.setGameover(level.points);
			smenu.setPosition(980, 700);
			smenu2.setPosition(960, 680);
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (smenu.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					isend = false;
					isgame = true;
					music.play();
					level.reset();
					cflash.restart();
				}
			}
		}

		if (notend) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			particleSystem.emitParticles(mousePos, particleSystem.randomColor());
			particleSystem.update();
			crosshair.updatePosition(window, elapsed.asSeconds());
			eyestext.setFont(font);
			eyestext.setString("NO DEBERIAS ESTAR AQUI...");
			eyestext.setCharacterSize(150);
			if (cflash.getElapsedTime() > sf::seconds(125)) {
				trap.play();
			}
		}

		//Dibujado

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
		if (isend) {
			interface.drawFinal(window);
			window.draw(smenu2);
			window.draw(smenu);
		}

		if (notend) {
			if (cflash.getElapsedTime() > sf::seconds(125)) {
				window.draw(lmao);
			}
			particleSystem.draw(window);
			window.draw(crosshair.sprite2);
			window.draw(crosshair.sprite);
			window.draw(eyestext);
		}

		window.display();
	}
}