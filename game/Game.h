#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
    sf::Font font;
    sf::Text text;
    sf::Clock clock;
    sf::Clock cflash;
    sf::Time lvtime = sf::seconds(37.5);
    sf::Time lvtime2 = sf::seconds(75);
    sf::Shader sbshader;
    sf::Shader bshader;
    sf::Shader lv3shader;
    sf::Texture textureMira2;
    sf::Texture textureMira;
    sf::Texture texture;
    sf::Sprite smenu2;
    sf::Sprite lmao;
    sf::Texture tlmao;
    sf::Texture tmenu2;
    sf::Music music;
    sf::Music menuMusic;
    sf::Music trap;
    sf::Text eyestext;
    bool ismenu = true;
    bool isgame = false;
    bool isend = false;
    bool notend = false;
    sf::Sprite smenu;
    sf::Texture tmenu;
    Game();
    ~Game();
    void run();
    sf::Clock spawn;
    sf::Time spawnTime = sf::seconds(1);

private:
    sf::RenderWindow window;
};

