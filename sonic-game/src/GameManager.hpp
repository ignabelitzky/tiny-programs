#pragma once

#include <SFML/Graphics.hpp>
#include "params.hpp"
#include "Sonic.hpp"

class GameManager {
    public:
        GameManager();
        void run();
    private:
        sf::RenderWindow m_window;
        bool m_isRunning;
        Sonic m_player;

        void processEvents();
        void update();
        void render();
};
