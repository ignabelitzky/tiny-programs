#include "Car.hpp"

Car::Car() {
    loadTexture(TEXTURE_DIR + std::string("f1_red.png"));
    m_speed = 200.f;
    m_lane = Lane::CENTER;
}

Car::~Car() {
}

void Car::loadTexture(const std::string& textureFile) {
    if(!m_texture.loadFromFile(textureFile)) {
        std::cout << "Error: Cannot load texture file.\n";
    }
    m_sprite.setTexture(m_texture);
}

void Car::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    m_sprite.setPosition(m_position);
}

void Car::moveLeft() {
    if(m_lane != Lane::LEFT) {
        m_position.x -= m_speed;
        m_sprite.setPosition(m_position);
        m_lane = decrementLane(m_lane);
    }
}

void Car::moveRight() {
    if(m_lane != Lane::RIGHT) {
        m_position.x += m_speed;
        m_sprite.setPosition(m_position);
        m_lane = incrementLane(m_lane);
    }
}

void Car::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

Lane Car::incrementLane(Lane lane) {
    Lane result = lane;
    switch(lane) {
        case Lane::LEFT:
            result = Lane::CENTER;
            break;
        case Lane::CENTER:
            result = Lane::RIGHT;
            break;
        default:
            break;
    }
    return result;
}

Lane Car::decrementLane(Lane lane) {
    Lane result = lane;
    switch(lane) {
        case Lane::RIGHT:
            result = Lane::CENTER;
            break;
        case Lane::CENTER:
            result = Lane::LEFT;
            break;
        default:
            break;
    }
    return result;
}
