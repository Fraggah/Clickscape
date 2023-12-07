#pragma once
#ifndef ALLIED_H
#define ALLIED_H
#include "Agent.h"

class Allied : public Agent {
public:
    Allied();
    ~Allied();
    void setTexture(sf::Texture& alliedTexture) override;
    void eraseTimeAction(int lifes) override;
    virtual int clickAction() override;
};
#endif