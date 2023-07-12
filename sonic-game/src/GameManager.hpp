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
        sf::Clock m_clock;
        sf::Time m_elapsed;
        sf::Time m_frameDuration;

        void processEvents();
        void update();
        void render();
};
