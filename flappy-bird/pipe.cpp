#include "pipe.h"

Pipe::Pipe(sf::Vector2f position) {
    m_width = getRandomInt(20, 60);
    m_height = getRandomInt(5, height - 60);
    m_position = position;
    m_hitColor = sf::Color::Red;
    m_defaultColor = sf::Color(138, 43, 226);
    m_position.y += m_height / 2;
    m_pipe.setSize(sf::Vector2f(m_width, m_height));
    m_pipe.setOrigin(m_width/2, m_height/2);
    m_pipe.setPosition(m_position); 
    m_pipe.setFillColor(m_defaultColor);
    m_speed = 0.f;
}

Pipe::Pipe(float width, float height, sf::Vector2f position) {
    m_width = width;
    m_height = height;
    m_position = position;
    m_hitColor = sf::Color::Red;
    m_defaultColor = sf::Color(138, 43, 226);
    m_pipe.setSize(sf::Vector2f(m_width, m_height));
    m_pipe.setPosition(m_position);
    m_pipe.setOrigin(m_width/2, m_height/2);
    m_pipe.setFillColor(m_defaultColor);
    m_speed = 0.f;
}

Pipe::~Pipe() {
}

void Pipe::update() {
    m_position.x -= 10.f;
    m_pipe.setPosition(m_position);
}

void Pipe::show(sf::RenderWindow& window) {
    window.draw(m_pipe);
}

void Pipe::setPosition(sf::Vector2f position) {
    m_position = position;
}

sf::Vector2f Pipe::getPosition() {
    return m_position;
}

bool Pipe::isOffscreen() {
    return (m_position.x < (-m_width/2.f));
}

bool Pipe::hit(Bird& bird) {
    sf::Vector2f birdPosition = bird.getPosition();
    if(birdPosition.x > m_position.x - (m_width/2)  && birdPosition.x < m_position.x + (m_width/2)) {
        if(birdPosition.y < m_height) {
            m_pipe.setFillColor(m_hitColor);
            return true;
        }
    }
    m_pipe.setFillColor(m_defaultColor);
    return false;
}
