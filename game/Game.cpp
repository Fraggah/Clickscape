#include "Game.h"
#include "../classes/Crosshair.h"
#include "../classes/Agent.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

struct Particle {
    sf::Vector2f velocity;
    sf::CircleShape shape;
};

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

    std::vector<Particle> particles;

    while (window.isOpen()) {  //Update
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time elapsed = clock.getElapsedTime();
        bshader.setUniform("u_time", elapsed.asSeconds());
        bshader.setUniform("u_resolution", sf::Vector2f(1920, 1080));

        // Genera un color aleatorio
        sf::Color randomColor(std::rand() % 100, std::rand() % 50, std::rand() % 256);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        int offsetX = std::rand() % 111 - 60; // Rango de -60 a +50
        int offsetY = std::rand() % 111 - 60; // Rango de -60 a +50

        mousePos.x += offsetX;
        mousePos.y += offsetY;

        for (int i = 0; i < 10; ++i) {
            Particle p;
            p.velocity = sf::Vector2f((std::rand() % 100 - 50) / 30.f, (std::rand() % 100 - 50) / 30.f);
            p.shape.setPosition((sf::Vector2f)mousePos);
            p.shape.setRadius(std::rand() % 3);
            p.shape.setFillColor(randomColor);
            particles.push_back(p);
        }

        // Actualizar partículas
        for (auto& p : particles) {
            p.shape.move(p.velocity);
            sf::Color c = p.shape.getFillColor();
            if (c.a > 0) c.a-=3;
            p.shape.setFillColor(c);
        }

        //Eliminar
        for (auto it = particles.begin(); it != particles.end(); /* no increment here */) {
            if (it->shape.getFillColor().a == 0) {
                it = particles.erase(it);
            }
            else {
                ++it;
            }
        }


        if (agent.handleClick(event, window)) {
            puntos++;
            if (puntos >= 5)
                window.close();
        }

        crosshair.updatePosition(window, elapsed.asSeconds());

        window.clear();
        window.draw(background, &bshader);
        for (const auto& p : particles) {
            window.draw(p.shape);
        }
        window.draw(agent.sprite);
        window.draw(crosshair.sprite2);
        window.draw(crosshair.sprite);
        window.display();
    }
}