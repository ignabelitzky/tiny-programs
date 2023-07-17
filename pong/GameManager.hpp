#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "params.hpp"
#include "helper.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

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
        void handleGameOverInput(sf::Keyboard::Key key);
        void updateMenu();
        void updatePlaying();
        void updateGameOverMenu();
        void drawMenu();
        void drawPlaying();
        void drawGameOverMenu();
        void render();
        void resetRound();
        void resetGame();
        void loadBackgroundMusic(std::string fileName);
        void loadFonts();
        void setTexts();
    private:
        sf::RenderWindow m_window;
        bool m_isRunning;
        GameState m_gameState;
        Paddle m_playerOne;
        Paddle m_playerTwo;
        Ball m_ball;
        int m_scorePlayerOne;
        int m_scorePlayerTwo;
        sf::Font m_font;
        sf::Text m_startGameText;
        sf::Text m_winnerText;
        sf::Text m_restartText;
        sf::Text m_quitText;
        sf::Text m_scorePlayerOneText;
        sf::Text m_scorePlayerTwoText;
        sf::Music m_backgroundMusic;
        int m_selectedOption;
};
