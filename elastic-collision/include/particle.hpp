#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include <SFML/Graphics.hpp>
#include <utility>

class Particle
{
public:
    Particle();
    ~Particle();
    void setPosition(float x, float y);
    void setVelocity(float vx, float vy);
    void setAcceleration(float ax, float ay);
    void setMass(float mass);
    void setRadius(float radius);
    void setColor(sf::Color color);
    std::pair<float, float> getPosition();
    std::pair<float, float> getVelocity();
    std::pair<float, float> getAcceleration();
    float getMass();
    float getRadius();
    sf::Color getColor();
    void update();
    void edges();
    void collide(Particle *other);
    void draw(sf::RenderWindow &window);

private:
    sf::CircleShape m_shape;
    sf::Color m_color;
    std::pair<float, float> m_position;
    std::pair<float, float> m_velocity;
    std::pair<float, float> m_acceleration;
    float m_mass;
    float m_radius;
};

#endif