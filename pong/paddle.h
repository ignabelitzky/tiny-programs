#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
    public:
        Paddle(int width, int height, sf::Vector2f position);
        ~Paddle();
        void moveUp();
        void moveDown();
        void render(sf::RenderWindow& window);
        sf::Vector2f getPosition();
    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_paddle;
        int m_width;
        int m_height;
        float m_speed;
};
