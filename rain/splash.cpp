#include "splash.h"


// Particle class
Particle::Particle(sf::Vector2f position, float radius) {
    m_radius = radius;
    m_position = position;
    m_particle.setPosition(m_position);
    m_particle.setRadius(m_radius);
    m_velocity = sf::Vector2f(genRandomFloat(100.f, 300.f) * std::cos(genRandomFloat(0.f, 2 * 3.141592f)),
                    genRandomFloat(100.f, 300.f) * std::sin(genRandomFloat(0.f, 2 * 3.141592f)));
    m_color = sf::Color(138, 43, 226);
    m_particle.setFillColor(m_color);

}

Particle::~Particle() {
}

void Particle::update() {
    m_position += m_velocity * 0.01f;
    m_velocity.y += 50.0f * 0.1f;  // Gravity
    m_particle.setPosition(m_position);
}

void Particle::show(sf::RenderWindow& window) {
    window.draw(m_particle);
}

void Particle::setPosition(sf::Vector2f position) {
    m_position = position;
    m_particle.setPosition(m_position);
}

sf::Vector2f Particle::getPosition() {
    return m_position;
}

void Particle::setVelocity(sf::Vector2f velocity) {
    m_velocity = velocity;
}

sf::Vector2f Particle::getVelocity() {
    return m_velocity;
}

void Particle::setColor(sf::Color color) {
    m_color = color;
}


// Splash class
Splash::Splash(sf::Vector2f position) {
    m_position = position;
    for(int i = 0; i < 30; ++i) {
        Particle p(m_position, 1.f);
        m_drops.push_back(p);
    }
}

Splash::~Splash() {
}

void Splash::update() {
    for(size_t i = 0; i < m_drops.size(); ++i) {
        m_drops[i].update();
    }
}

void Splash::show(sf::RenderWindow& window) {
    for(size_t i = 0; i < m_drops.size(); ++i) {
        m_drops[i].show(window);
    }
}

void Splash::setPosition(sf::Vector2f position) {
    m_position = position;
}

sf::Vector2f Splash::getPosition() {
    return m_position;
}
