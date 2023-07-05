#include <SFML/Graphics.hpp>
#include "params.h"
#include "paddle.h"
#include "ball.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Pong clone");
    window.setVerticalSyncEnabled(true);

    // Create paddles
    int paddleWidth = 20;
    int paddleHeight = 100;
    Paddle leftPaddle(paddleWidth, paddleHeight, sf::Vector2f(50.f, height / 2.f - paddleHeight / 2.f));
    Paddle rightPaddle(paddleWidth, paddleHeight, sf::Vector2f(width - 50.f - paddleWidth, height / 2.f - paddleHeight / 2.f));

    // Create ball
    int ballRadius = 10;
    sf::Vector2f ballPosition(width / 2, height / 2);
    sf::Vector2f ballVelocity(7.f, 7.f);
    Ball ball(ballRadius, ballPosition, ballVelocity);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Move paddles
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0)
            leftPaddle.moveUp();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + paddleHeight < height)
            leftPaddle.moveDown();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0)
            rightPaddle.moveUp();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + paddleHeight < height)
            rightPaddle.moveDown();
        
        // Update ball position
        ball.update();

        ballPosition = ball.getPosition();

        // Check for collisions with paddles
        if(ballPosition.x - ballRadius < leftPaddle.getPosition().x + paddleWidth &&
                ballPosition.y + ballRadius > leftPaddle.getPosition().y &&
                ballPosition.y - ballRadius < leftPaddle.getPosition().y + paddleHeight) {
            ball.setVelocity(sf::Vector2f(-ball.getVelocity().x, ball.getVelocity().y));
        }
        if(ballPosition.x + ballRadius > rightPaddle.getPosition().x && 
                ballPosition.y + ballRadius > rightPaddle.getPosition().y &&
                ballPosition.y - ballRadius < rightPaddle.getPosition().y + paddleHeight) {
            ball.setVelocity(sf::Vector2f(-ball.getVelocity().x, ball.getVelocity().y));
        }

        // Check for collision with window edges
        if(ballPosition.x + ballRadius > width || ballPosition.x - ballRadius < 0) {
            ball.setVelocity(sf::Vector2f(-ball.getVelocity().x, ball.getVelocity().y)); 
        }
        if(ballPosition.y + ballRadius > height || ballPosition.y - ballRadius < 0) { 
            ball.setVelocity(sf::Vector2f(ball.getVelocity().x, -ball.getVelocity().y)); 
        }
        
        window.clear();

        leftPaddle.render(window);
        rightPaddle.render(window);
        ball.render(window);
        window.display();
    }
    return 0;
}
