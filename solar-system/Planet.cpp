#include "Planet.hpp"

Planet::Planet(float radius, float distance, float orbitSpeed) :
    m_shape(radius)
{
    m_radius = radius;
    m_angle = 0.f;
    m_distance = distance;
    m_orbitSpeed = orbitSpeed;

    m_shape.setFillColor(sf::Color::White);
    m_shape.setOrigin(m_radius, m_radius);
    m_shape.setPosition(sf::Vector2f(WIDTH/2.f, HEIGHT/2.f));
}

Planet::~Planet() {
}

sf::CircleShape Planet::getShape() {
    return m_shape;
}

sf::Vector2f Planet::getPosition() {
    return m_shape.getPosition();
}

void Planet::setPosition(float x, float y) {
    m_shape.setPosition(x, y);
}

void Planet::setFillColor(sf::Color color) {
    m_shape.setFillColor(color);
}

void Planet::setOrigin(float x, float y) {
    m_shape.setOrigin(x, y);
}

float Planet::getDistance() {
    return m_distance;
}

void Planet::setAngle(float angle) {
    m_angle = angle;
}

float Planet::getAngle() {
    return m_angle;
}

void Planet::spawnMoons(int total) {
    for(int i = 0; i < total; ++i) {
        Planet moon(getRandomFloat(m_radius * 0.3f, m_radius * 0.8),
                getRandomFloat(m_radius * 3, HEIGHT/2.f), getRandomFloat(0.1f, 1.0f));
        moon.setOrigin(m_radius * 0.5f, m_radius * 0.5f);
        moon.setAngle(getRandomFloat(0.f, 360.f));
        float distance = moon.getDistance();
        float angle = moon.getAngle();
        float delta_x = distance * std::cos(angle * M_PI / 180.f);
        float delta_y = distance * std::sin(angle * M_PI / 180.f);
        moon.setPosition(m_shape.getPosition().x + delta_x, m_shape.getPosition().y + delta_y);
        m_moons.push_back(moon);
    }
}

std::vector<Planet> Planet::getMoons() {
    return m_moons;
}

void Planet::update() {
    for(size_t i = 0; i < m_moons.size(); ++i) {
        float distance = m_moons.at(i).getDistance();
        float angle = m_moons.at(i).getAngle();
        float delta_x = distance * std::cos(angle * M_PI / 180.f);
        float delta_y = distance * std::sin(angle * M_PI / 180.f);
        m_moons.at(i).setPosition(m_shape.getPosition().x + delta_x, m_shape.getPosition().y + delta_y);
    }
}


void Planet::orbit() {
    m_angle += m_orbitSpeed;
    for(size_t i = 0; i < m_moons.size(); ++i) {
        m_moons.at(i).orbit();
    }
    update();
}
