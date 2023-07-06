#include "bird.h"

Bird::Bird(int radius, sf::Vector2f position) {
    m_color = sf::Color::Yellow;
    m_isAlive = true;
    m_upForce = 2.5f;
    m_radius = radius;
    m_gravity = 0.5f;
    m_velocity = sf::Vector2f(0.f, 0.f);
    m_bird.setRadius(m_radius);
    m_bird.setOrigin(m_radius, m_radius);
    m_bird.setPosition(position.x - m_radius, position.y - m_radius);
    m_bird.setFillColor(m_color);
    m_position = m_bird.getPosition();
}

Bird::~Bird() {
}

void Bird::up() {
    m_velocity.y += -m_gravity * m_upForce;
}

void Bird::update() {
    if(m_isAlive) {
        m_velocity.y += m_gravity;
        m_position += m_velocity;
        if(m_position.y > height - m_radius || m_position.y < m_radius) {
            m_velocity = sf::Vector2f(0.f, 0.f);
            m_isAlive = false;
        }
    }
    m_bird.setPosition(m_position);
}

void Bird::show(sf::RenderWindow& window) {
    window.draw(m_bird);
}

void Bird::setPosition(sf::Vector2f position) {
    m_bird.setPosition(position.x, position.y);
    m_position = position;
}

sf::Vector2f Bird::getPosition() {
    return m_position;
}

bool Bird::isAlive() {
    return m_isAlive;
}

void Bird::revive() {
    m_isAlive = true;
}
