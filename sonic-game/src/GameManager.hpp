#pragma once

#include <SFML/Graphics.hpp>
#include "params.hpp"
#include "helper.hpp"
#include "Sonic.hpp"
#include "Floor.hpp"
#include "Enemy.hpp"

class GameManager {
    public:
        GameManager();
        void run();
    private:
        sf::RenderWindow m_window;
        bool m_isRunning;

        Sonic m_player;
        Floor m_floor;
        std::vector<Enemy> m_enemies;

        sf::Clock m_clock;
        sf::Time m_elapsed;
        sf::Time m_frameDuration;

        sf::Clock m_enemyClock;
        sf::Time m_enemyElapsed;
        float m_limitSeconds;

        int m_score;
        int m_maxScore;

        sf::Text m_scoreText;
        sf::Font m_font;

        void processEvents();
        void update();
        void render();
};
