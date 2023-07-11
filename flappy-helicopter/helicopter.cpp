#include "helicopter.h"

Helicopter::Helicopter(int radius, sf::Vector2f position) {
    m_texture.loadFromFile("./resources/images/helicopter.png");
    m_isAlive = true;
    m_upForce = 2.5f;
    m_radius = radius;
    m_gravity = 0.5f;
    m_velocity = sf::Vector2f(0.f, 0.f);
    m_helicopter.setRadius(m_radius);
    m_helicopter.setOrigin(m_radius, m_radius);
    m_helicopter.setPosition(position.x - m_radius, position.y - m_radius);
    m_position = m_helicopter.getPosition();
}

Helicopter::~Helicopter() {
}

void Helicopter::up() {
    m_velocity.y += -m_gravity * m_upForce;
}

void Helicopter::update() {
    if(m_isAlive) {
        m_velocity.y += m_gravity;
        m_position += m_velocity;
        if(m_position.y > height - m_radius || m_position.y < m_radius) {
            m_velocity = sf::Vector2f(0.f, 0.f);
            m_isAlive = false;
        }
    }
    m_helicopter.setPosition(m_position);
}

void Helicopter::show(sf::RenderWindow& window) {
    m_helicopter.setTexture(&m_texture);
    window.draw(m_helicopter);
}

void Helicopter::setPosition(sf::Vector2f position) {
    m_helicopter.setPosition(position.x, position.y);
    m_position = position;
}

sf::Vector2f Helicopter::getPosition() {
    return m_position;
}

bool Helicopter::isAlive() {
    return m_isAlive;
}

void Helicopter::revive() {
    m_isAlive = true;
}
