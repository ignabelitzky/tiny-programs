#include "target.h"

Target::Target(sf::Vector2f position, float radius) {
    m_texture.loadFromFile("./resources/images/bull_eye.png");
    m_radius = radius;
    m_position = position;
    m_target.setOrigin(m_radius, m_radius);
    m_target.setTexture(&m_texture);
    m_target.setRadius(m_radius);
    m_target.setPosition(m_position);
}

Target::~Target() {
}

void Target::update() {
    m_target.setPosition(m_position);
    m_target.setOrigin(m_radius, m_radius);
    m_target.setRadius(m_radius);
    m_target.setTexture(&m_texture);
}

void Target::show(sf::RenderWindow& window) {
    m_target.setTexture(&m_texture);
    window.draw(m_target);
}

void Target::setPosition(sf::Vector2f position) {
    m_position = position;
    m_target.setPosition(m_position);
}

sf::Vector2f Target::getPosition() {
    return m_position;
}

void Target::setRadius(float radius) {
    m_radius = radius;
    m_target.setRadius(m_radius);
    m_target.setOrigin(m_radius, m_radius);
}

float Target::getRadius() {
    return m_radius;
} 
