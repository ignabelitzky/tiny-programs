#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "params.hpp"
#include "helper.hpp"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

class GameManager {
    public:
        GameManager();
        ~GameManager();
        void run();
    private:
        void processEvents();
        void handleMenuInput(sf::Keyboard::Key key);
        void handlePlayingInput(sf::Keyboard::Key key);
        void handleGameOverInput(sf::Keyboard::Key key);
        void updateMenu();
        void updatePlaying();
        void updateGameOver();
        void render();
        void resetGame();
        void loadBackgroundMusic(std::string fileName);
        void loadFonts();
        void setTexts();
    private:
        sf::RenderWindow m_window;
        bool m_isRunning;
        GameState m_gameState;
        int m_score;
        int m_highScore;
        sf::Font m_font;
        sf::Text m_startGameText;
        sf::Text m_restartText;
        sf::Text m_quitText;
        sf::Text m_scoreText;
        sf::Music m_backgroundMusic;
        int m_selectedOption;
};
