#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "params.hpp"
#include "helper.hpp"
#include "Sonic.hpp"
#include "Floor.hpp"
#include "Enemy.hpp"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER,
};

class GameManager {
    public:
        GameManager();
        ~GameManager();
        void run();
    private:
        sf::RenderWindow m_window;
        bool m_isRunning;
        GameState m_gameState;

        sf::Music m_backgroundMusic;

        Sonic m_player;
        int m_lives;
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

        sf::Font m_menuFont;
        sf::Text m_startGameText;
        sf::Text m_restartText;
        sf::Text m_quitText;
        int m_selectedOption;


        void processEvents();
        void handleMenuInput(sf::Keyboard::Key key);
        void handleGameOverInput(sf::Keyboard::Key key);
        void updateMenu();
        void updatePlaying();
        void updateGameOver();
        void render();
        void drawMenu();
        void drawGameOverMenu();
        void resetGame();
};
