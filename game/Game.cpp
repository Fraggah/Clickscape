#include "Game.h"
#include "../classes/Crosshair.h"
#include "../classes/Agent.h"
#include "SFML/Graphics.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "Game") {
    window.setMouseCursorVisible(false);
}

Game::~Game() {
}

void Game::run() {
    //Start
    window.setMouseCursorVisible(false);

    sf::Texture textureEt;
    if (!textureEt.loadFromFile("./assets/et.png"));
 
    sf::Texture textureMira;
    if (!textureMira.loadFromFile("./assets/crosshair.png"));
      
    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile("./assets/background.jpg"));
     
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    Agent agent(textureEt);
    Crosshair crosshair(textureMira);

    int puntos = 0;

    while (window.isOpen()) {  //Update
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (agent.handleClick(event, window)) {
            puntos++;
            if (puntos >= 5)
                window.close();
        }

        crosshair.updatePosition(window);

        window.clear();
        window.draw(spriteBackground);
        window.draw(agent.sprite);
        window.draw(crosshair.sprite);
        window.display();
    }
}