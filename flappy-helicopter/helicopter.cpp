#include "helicopter.h"

Helicopter::Helicopter(int width, int height, sf::Vector2f position) :
    m_helicopter(sf::Vector2f(width, height)),
    m_textureRect(0, 0, 0, 0),
    m_gravity(0.5f),
    m_upForce(2.5f),
    m_velocity(0.f, 0.f),
    m_isAlive(true),
    m_elapsedTime(0.0f),
    m_frameDuration(0.05f)
{
    m_texture.loadFromFile("./resources/images/helicopter_sheet.png");
    m_textureSize = m_texture.getSize();
    m_textureWidth = m_textureSize.x;
    m_textureHeight = m_textureSize.y / 4;    // Assuming the sprite sheet has 4 images of equal height
    m_textureRect.width = m_textureWidth;
    m_textureRect.height = m_textureHeight;

    sf::FloatRect bounds = m_helicopter.getLocalBounds();
    m_helicopter.setOrigin(bounds.width / 2, bounds.height / 2);
    m_helicopter.setPosition(position);
    m_position = m_helicopter.getPosition();
}

void Helicopter::up() {
    m_velocity.y += -m_gravity * m_upForce;
}

void Helicopter::update() {
    m_elapsedTime += m_clock.restart().asSeconds();
    if (m_elapsedTime >= m_frameDuration) {
        unsigned int imageIndex = m_textureRect.top + m_textureHeight; // Increment by textureHeight
        if (imageIndex >= m_textureSize.y) {
            imageIndex -= m_textureSize.y; // Wrap around to the top if it exceeds textureSize
        }
        m_textureRect.top = imageIndex;
        m_elapsedTime = 0.0f;
    }

    m_helicopter.setTexture(&m_texture);
    m_helicopter.setTextureRect(m_textureRect);
    //m_helicopter.setScale(sf::Vector2f(0.8, 0.5));

    if (m_isAlive) {
        m_velocity.y += m_gravity;
        m_position += m_velocity;
        if (m_position.y > height || m_position.y < 0) {
            m_velocity = sf::Vector2f(0.f, 0.f);
            m_isAlive = false;
        }
    }

    m_helicopter.setPosition(m_position);
}

void Helicopter::show(sf::RenderWindow& window) {
    window.draw(m_helicopter);
}

void Helicopter::setPosition(sf::Vector2f position) {
    m_helicopter.setPosition(position);
    m_position = m_helicopter.getPosition();
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
