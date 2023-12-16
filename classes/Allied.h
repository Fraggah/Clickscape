#pragma once

#include "Agent.h"
#include <SFML/Audio.hpp>

class Allied : public Agent {
public:
    Allied();
    ~Allied();
    void setTexture(sf::Texture& alliedTexture) override;
    virtual int eraseTimeAction(sf::Sound sonido[5]) override;
    virtual int clickAction(sf::Sound sonido[5]) override;
};
