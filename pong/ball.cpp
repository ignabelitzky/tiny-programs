#include "ball.h"

Ball::Ball(int radius, sf::Vector2f position, sf::Vector2f velocity) {
    m_radius = radius;
    m_ball.setRadius(m_radius);
    m_ball.setOrigin(radius, radius);
    m_ball.setPosition(position.x - m_radius, position.y - m_radius);
    m_position = m_ball.getPosition();
    m_velocity = velocity;
}

Ball::~Ball() {
}

void Ball::setPosition(sf::Vector2f position) {
    m_ball.setPosition(position.x, position.y);
    m_position = position;
}

sf::Vector2f Ball::getPosition() {
    return m_position;
}

void Ball::update() {
    m_position += m_velocity;
    m_ball.setPosition(m_position);
}

void Ball::setVelocity(sf::Vector2f velocity) {
    m_velocity = velocity;
}

sf::Vector2f Ball::getVelocity() {
    return m_velocity;
}

void Ball::render(sf::RenderWindow& window) {
    window.draw(m_ball);
}
