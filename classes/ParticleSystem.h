#include <SFML/Graphics.hpp>
#include <vector>

struct Particle {
    sf::Vector2f velocity;
    sf::CircleShape shape;
};

class ParticleSystem {
public:
    ParticleSystem();
    void update();
    void draw(sf::RenderWindow& window);
    void emitParticles(const sf::Vector2i& position, const sf::Color& color);
    sf::Color randomColor();
private:
    std::vector<Particle> particles;
};
