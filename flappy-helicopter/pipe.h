#pragma once

#include <SFML/Graphics.hpp>
#include "params.h"
#include "helper.h"
#include "helicopter.h"

class Pipe {
    public:
        Pipe(sf::Vector2f position);
        Pipe(float width, float height, sf::Vector2f position);
        ~Pipe();
        void update();
        void show(sf::RenderWindow& window);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        bool isOffscreen();
        bool hit(Helicopter& helicopter);
    private:
        sf::RectangleShape m_pipe;
        sf::Texture m_texture;
        sf::Vector2f m_position;
        float m_speed;
        float m_width;
        float m_height;
        sf::Color m_hitColor;
};
