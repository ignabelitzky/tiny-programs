#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Planet.hpp"
#include "params.hpp"

enum SystemState {
    MENU,
    SIMULATION
};

class SystemManager {
    public:
        SystemManager();
        ~SystemManager();
        void run();
    private:
        void processEvents();
        void render();
        void handleMenuInput(sf::Keyboard::Key key);
        void handleSimulationInput(sf::Keyboard::Key key);
        void updateMenu();
        void updateSimulation();
        void drawMenu();
        void drawSimulation();
        void clearSimulation();
        void loadFonts();
        void setTexts();
        void loadPlanets();
    private:
        sf::RenderWindow m_window;
        SystemState m_systemState;
        bool m_isRunning;
        std::vector<Planet> m_planets;
        sf::Font m_font;
        sf::Text m_startText;
        sf::Text m_quitText;
        sf::Texture m_starsTexture;
        std::vector<sf::Texture> m_textures;
        sf::Sprite m_backgroundSprite;
        int m_selectedOption;
};
