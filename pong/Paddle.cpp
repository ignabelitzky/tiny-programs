#include "Paddle.hpp"

Paddle::Paddle(int width, int height, sf::Vector2f position) {
    m_width = width;
    m_height = height;
    m_position = position;
    m_speed = 8.f;
    m_paddle.setSize(sf::Vector2f(m_width, m_height));
    m_paddle.setFillColor(sf::Color::White);
    m_paddle.setPosition(position.x, position.y);
}

Paddle::~Paddle() {
}

void Paddle::moveUp() {
    m_paddle.move(0.f, -m_speed);
    m_position = m_paddle.getPosition();
}

void Paddle::moveDown() {
    m_paddle.move(0.f, m_speed);
    m_position = m_paddle.getPosition();
}

void Paddle::render(sf::RenderWindow& window) {
    window.draw(m_paddle);
}

sf::Vector2f Paddle::getPosition() {
    return m_position;
}

sf::RectangleShape Paddle::getShape() {
    return m_paddle;
}
