#include "Interface.h"

Interface::Interface() {

}

Interface::~Interface() {

}

void Interface::setFont() {
    font.loadFromFile("./assets/Prompt-Regular.ttf");
}

void Interface::setText(int points, int lifes) {
    std::string score = std::to_string(points);
    text.setFont(font);
    text.setString("SCORE " + score);
    text.setCharacterSize(30);
    text.setPosition(50, 50);
    tlife.setFont(font);
    std::string tlifes = std::to_string(lifes);
    tlife.setString("X "+tlifes);
    tlife.setCharacterSize(30);
    tlife.setPosition(1700, 50);
}

void Interface::setLifes(sf::Texture texture) {
    life.setTexture(texture);
    life.setScale(0.1, 0.1);
    life.setPosition(1770, 60);
}

void Interface::setGameover(int points) {
    std::string score = std::to_string(points);
    scorefinal.setFont(font);
    scorefinal.setString(score);
    scorefinal.setCharacterSize(60);
    scorefinal.setPosition(1080, 400);
    gameOver.setFont(font);
    gameOver.setString("GAME OVER");
    gameOver.setCharacterSize(120);
    gameOver.setPosition(600, 200);
    yourScore.setFont(font);
    yourScore.setString("You Score");
    yourScore.setCharacterSize(60);
    yourScore.setPosition(750,400);
}

void Interface::draw(sf::RenderWindow& window) {
    window.draw(text);
    window.draw(tlife);
    window.draw(life); //no se dibuja... no llego a revisar que tiene .. es el sprite que indica cantidad de vidas
}

void Interface::drawFinal(sf::RenderWindow& window) {
    window.draw(scorefinal);
    window.draw(gameOver);
    window.draw(yourScore);
}