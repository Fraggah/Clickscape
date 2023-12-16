#include "ParticleSystem.h"
#include <cstdlib>

ParticleSystem::ParticleSystem() {}

void ParticleSystem::emitParticles(const sf::Vector2i& position, const sf::Color& color) {
    for (int i = 0; i < 10; ++i) {
        Particle p;
        p.velocity = sf::Vector2f((std::rand() % 100 - 50) / 30.f, (std::rand() % 100 - 50) / 30.f);
        p.shape.setPosition((sf::Vector2f)position);
        p.shape.setRadius(std::rand() % 3);
        p.shape.setFillColor(color);
        this->particles.push_back(p);
    }
}

void ParticleSystem::update() {
    for (auto& p : this->particles) {
        p.shape.move(p.velocity);
        sf::Color c = p.shape.getFillColor();
        if (c.a > 0) c.a -= 3;
        p.shape.setFillColor(c);
    }

    for (
        auto it = this->particles.begin();
        it != this->particles.end();
        ) {
        if (it->shape.getFillColor().a == 0) {
            it = this->particles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void ParticleSystem::draw(sf::RenderWindow& window) {
    for (const auto& p : this->particles) {
        window.draw(p.shape);
    }
}

sf::Color ParticleSystem::randomColor() {
    return sf::Color(std::rand() % 100, std::rand() % 50, std::rand() % 256);
}
