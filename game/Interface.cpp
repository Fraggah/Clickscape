#include "Interface.h"

Interface::Interface() {

}

Interface::~Interface() {

}

void Interface::setText(int points, int lifes) {
    font.loadFromFile("./assets/Prompt-Regular.ttf");
    text.setFont(font);
    std::string score = std::to_string(points);
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

void Interface::draw(sf::RenderWindow& window) {
    window.draw(text);
    window.draw(tlife);
    window.draw(life);
}