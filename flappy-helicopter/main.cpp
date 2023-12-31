#include <iostream>
#include <SFML/Graphics.hpp>
#include "params.h"
#include "helper.h"
#include "helicopter.h"
#include "pipe.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Flappy Helicopter");
    window.setVerticalSyncEnabled(true);

    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("./resources/images/stars.jpg")) {
        std::cout << "Error: Cannot open background image.\n";
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    bool gameOver = false;
    int score = 0;
    int maxScore = retrieveMaxScore();

    sf::Font font;
    if(!font.loadFromFile("./resources/fonts/retroGaming.ttf")) {
        std::cerr << "Couldn't load the font.\n";
        return 1;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setString("Score: " + std::to_string(score));

    sf::FloatRect textBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(textBounds.left + textBounds.width/2, textBounds.top - textBounds.height);

    float centerX = width / 2;
    float topY = 0.0f;

    scoreText.setPosition(centerX, topY);


    sf::Text gameoverText;
    gameoverText.setFont(font);
    gameoverText.setCharacterSize(70);
    gameoverText.setFillColor(sf::Color::White);
    gameoverText.setString("Your score: " + std::to_string(score) +
            "\nMax Score: " + std::to_string(maxScore) +
            "\nspace to restart.\nEscape to exit.");

    // Calculate the position to center the text
    sf::FloatRect textRect = gameoverText.getLocalBounds();
    gameoverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); 
    gameoverText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

    sf::Clock clock;
    sf::Time elapsedtime;
    
    // Time to generate new pipe
    float limitSecond = getRandomFloat(1.f, 2.f);
    
    // Helicopter start position
    sf::Vector2f helicopterPosition(helicopterStartPositionX, helicopterStartPositionY);

    // Pipe start position
    sf::Vector2f pipePosition(pipeStartPositionX, pipeStartPositionY);
     
    
    Helicopter helicopter(helicopterWidth, helicopterHeight, helicopterPosition);
    std::vector<Pipe> pipes;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
        window.clear();

        window.draw(backgroundSprite);

        if(!gameOver) {
            // Get the elapsed time
            elapsedtime = clock.getElapsedTime();

            if(elapsedtime.asSeconds() >= limitSecond) {
                Pipe pipe(pipePosition);
                pipes.push_back(pipe);
           
                // Reset the clock
                clock.restart();
                limitSecond = getRandomFloat(0.5f, 1.5f);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                helicopter.up();
            }

            helicopter.update();
            if(!helicopter.isAlive()) {
                gameOver = true;
            }

            for(std::vector<Pipe>::iterator it = pipes.begin(); it != pipes.end();  ) {
                it->update();
                if(it->isOffscreen()) {
                    it = pipes.erase(it);
                    ++score;
                    scoreText.setString("Score: " + std::to_string(score));
                } else {
                    if(it->hit(helicopter)) {
                        gameOver = true;
                    }
                    it->show(window);
                    ++it;
                }
            }
            helicopter.show(window);
            window.draw(scoreText);
        } else {
            if(score > maxScore) {
                maxScore = score;
                gameoverText.setString("Your score: " + std::to_string(score) +
                        "\nMax Score: " + std::to_string(maxScore) +
                        "\nSpace to restart.\nEscape to exit.");
                saveMaxScore(maxScore);
                window.draw(gameoverText);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                // Restart the game
                gameOver = false;
                score = 0;
                scoreText.setString("Score: " + std::to_string(score));
                helicopter.setPosition(sf::Vector2f(helicopterStartPositionX, helicopterStartPositionY));
                helicopter.revive();
                helicopter.show(window);
                pipes.clear();
            }
            gameoverText.setString("Your score: " + std::to_string(score) +
                    "\nMax Score: " + std::to_string(maxScore) +
                    "\nSpace to restart.\nEscape to exit.");
            window.draw(gameoverText);
        }

        window.display();
    }
    return 0;
}
