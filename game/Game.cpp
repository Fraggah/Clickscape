#include "Game.h"
#include "../classes/ParticleSystem.h"
#include "../classes/Crosshair.h"
#include "../classes/Agent.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

Game::Game() : window(sf::VideoMode(1920, 1080), "Game") {
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
}

Game::~Game() {
}

void Game::run() {
    //Start
    sf::Texture textureA;
    if (!textureA.loadFromFile("./assets/et.png"));

    sf::Texture textureMira;
    if (!textureMira.loadFromFile("./assets/player1.png"));

    sf::Texture textureMira2;
    if (!textureMira2.loadFromFile("./assets/player2.png"));

    sf::RectangleShape background(sf::Vector2f(1920, 1080));

    sf::Shader bshader;
    if (!bshader.loadFromFile("./shaders/bshader.frag", sf::Shader::Fragment)) {
        std::cout << "Error al cargar el shader" << std::endl;
    }

    Agent agent(textureA);
    Crosshair crosshair(textureMira, textureMira2);
    sf::Clock clock;
    int puntos = 0;

    ParticleSystem particleSystem;

    while (window.isOpen()) {  //Update
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time elapsed = clock.getElapsedTime();
        bshader.setUniform("u_time", elapsed.asSeconds());
        bshader.setUniform("u_resolution", sf::Vector2f(1920, 1080));

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        particleSystem.emitParticles(mousePos, particleSystem.randomColor());
        particleSystem.update();

        if (agent.handleClick(event, window)) {
            puntos++;
            if (puntos >= 5)
                window.close();
        }

        crosshair.updatePosition(window, elapsed.asSeconds());

        window.clear();
        window.draw(background, &bshader);
        particleSystem.draw(window);
        window.draw(agent.sprite);
        window.draw(crosshair.sprite2);
        window.draw(crosshair.sprite);
        window.display();
    }
}