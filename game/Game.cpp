#include "Game.h"
#include "Level.h"
#include "../classes/ParticleSystem.h"
#include "../classes/Crosshair.h"
#include "../classes/Agent.h"
#include <SFML/Audio.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(1920, 1080), "Game") {
    window.setFramerateLimit(60);
}

Game::~Game() {
}

void Game::run() {
    //Start

    sf::Music music;
    if (!music.openFromFile("./sounds/theme.ogg"));

    sf::Sprite smenu;
    sf::Texture tmenu;
    if (!tmenu.loadFromFile("./assets/player1.png"));
    sf::Sprite smenu2;
    sf::Texture tmenu2;
    if (!tmenu2.loadFromFile("./assets/player2.png"));
    smenu.setTexture(tmenu);
    smenu.setScale(0.4f, 0.4f);
    smenu2.setTexture(tmenu2);
    smenu2.setScale(0.4f, 0.4f);
    sf::Vector2u size = tmenu.getSize();
    sf::Vector2u size2 = tmenu.getSize();
    smenu.setOrigin((size.x / 2) + 5, (size.y / 2) + 5);
    smenu2.setOrigin((size2.x / 2), (size2.y / 2));


    smenu.setPosition((window.getSize().x) / 2, (window.getSize().y) / 2);
    smenu2.setPosition(((window.getSize().x) / 2)-20, ((window.getSize().y) / 2)-22);

    sf::Texture textureMira;
    if (!textureMira.loadFromFile("./assets/player1.png"));

    sf::Texture textureMira2;
    if (!textureMira2.loadFromFile("./assets/player2.png"));

    sf::RectangleShape background(sf::Vector2f(1920, 1080));

    sf::Shader bshader;
    if (!bshader.loadFromFile("./shaders/bshader.frag", sf::Shader::Fragment)) {
        std::cout << "Error al cargar el shader" << std::endl;
    }

    sf::Shader sbshader;
    if (!sbshader.loadFromFile("./shaders/startbshader.frag", sf::Shader::Fragment)) {
        std::cout << "Error al cargar el shader" << std::endl;
    }

    sf::RectangleShape rect(sf::Vector2f(window.getSize()));

    sf::Clock cflash;
    sf::Time flashtime = sf::seconds(37.5);

    sf::Clock spawn;
    sf::Time spawnTime = sf::seconds(2);

    Level level;

    Crosshair crosshair(textureMira, textureMira2);
    sf::Clock clock;
    int puntos = 0;

    ParticleSystem particleSystem;

    bool ismenu = true;
    bool isgame = false;

    sf::Font font;
    sf::Text text;

    font.loadFromFile("./assets/Prompt-Regular.ttf");
    text.setFont(font);
    text.setString("Clickscape");
    text.setCharacterSize(50);
    text.setPosition(825, 300);

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

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            particleSystem.emitParticles(mousePos, particleSystem.randomColor());
            particleSystem.update();

            if (spawn.getElapsedTime() > spawnTime) {
                level.createAgent();
                spawn.restart();
            }
            crosshair.updatePosition(window, elapsed.asSeconds());
            level.deleteAgent(event, window);
        }


            window.clear();
            
            if (cflash.getElapsedTime() < flashtime) {
                window.draw(rect, &sbshader);
            }
            else {
                window.draw(background, &bshader);
            }


            if (ismenu) {
                window.draw(text);
                window.draw(smenu2);
                window.draw(smenu);
            }
            if (isgame) {
                particleSystem.draw(window);
                level.draw(window);
                window.draw(crosshair.sprite2);
                window.draw(crosshair.sprite);
            }
            window.display();
    }
}