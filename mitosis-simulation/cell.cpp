#include "cell.h"

Cell::Cell(sf::Vector2f position, float radius) {
    m_position = position;
    m_radius = radius;
    m_acceleration = genRandomFloat(0.5f, 2.0f);
    m_color = sf::Color(genRandomInt(100, 255), 100, genRandomInt(100, 255), 100);
    m_cell.setRadius(m_radius);
    m_cell.setOrigin(m_radius, m_radius);
    m_cell.setPosition(m_position);
    m_cell.setFillColor(m_color);
}
Cell::Cell(sf::Vector2f position, float radius, sf::Color color) {
    m_position = position;
    m_radius = radius;
    m_color = color;
    m_acceleration = genRandomFloat(0.5f, 2.0f);
    m_cell.setRadius(m_radius);
    m_cell.setOrigin(m_radius, m_radius);
    m_cell.setPosition(m_position);
    m_cell.setFillColor(m_color);
}

Cell::~Cell() {
}

void Cell::show(sf::RenderWindow& window) {
    window.draw(m_cell);
}

void Cell::move() {
    m_velocity = genRandomVector(-5.0f, 5.0f);
    m_position += m_velocity * m_acceleration;
    m_acceleration = genRandomFloat(0.5f, 2.0f);
    m_cell.setPosition(m_position);
}

bool Cell::mousePressed(sf::Vector2i clickPosition) {
    float distance = sqrt(pow(m_position.x - clickPosition.x, 2) + pow(m_position.y - clickPosition.y, 2));
    return distance < m_radius;
}

Cell Cell::mitosis() {
    return Cell(m_position, m_radius * 0.8f, m_color);
}
