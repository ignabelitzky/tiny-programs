#pragma once

#include <SFML/Graphics.hpp>
#include "params.hpp"

class GameManager {
    public:
        GameManager();
        void run();
    private:
        sf::RenderWindow m_window;
        bool m_isRunning;

        void processEvents();
        void update();
        void render();
};
