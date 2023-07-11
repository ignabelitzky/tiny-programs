#include "pipe.h"

Pipe::Pipe(sf::Vector2f position) {
    m_texture.loadFromFile("./resources/images/pipe.png");
    m_width = getRandomInt(minPipeWidth, maxPipeWidth);
    m_height = getRandomInt(minPipeHeight, maxPipeHeight);
    m_position = position;
    m_hitColor = sf::Color::Red;
    m_position.y += m_height / 2;
    m_pipe.setSize(sf::Vector2f(m_width, m_height));
    m_pipe.setOrigin(m_width/2, m_height/2);
    m_pipe.setPosition(m_position); 
    m_speed = 0.f;
}

Pipe::Pipe(float width, float height, sf::Vector2f position) {
    m_texture.loadFromFile("./resources/images/pipe.png");
    m_width = width;
    m_height = height;
    m_position = position;
    m_hitColor = sf::Color::Red;
    m_pipe.setSize(sf::Vector2f(m_width, m_height));
    m_pipe.setPosition(m_position);
    m_pipe.setOrigin(m_width/2, m_height/2);
    m_speed = 0.f;
}

Pipe::~Pipe() {
}

void Pipe::update() {
    m_position.x -= 10.f;
    m_pipe.setPosition(m_position);
}

void Pipe::show(sf::RenderWindow& window) {
    m_pipe.setTexture(&m_texture);
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

bool Pipe::hit(Helicopter& helicopter) {
    sf::Vector2f helicopterPosition = helicopter.getPosition();
    if(helicopterPosition.x > m_position.x - (m_width/2)  && helicopterPosition.x < m_position.x + (m_width/2)) {
        if(helicopterPosition.y < m_height) {
            m_pipe.setFillColor(m_hitColor);
            return true;
        }
    }
    return false;
}
