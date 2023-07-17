#pragma once

#define SOUND_DIR "./assets/sounds/"
#define FONT_DIR "./assets/fonts/"

constexpr int width = 1600;
constexpr int height = 900;
constexpr int winGoal = 5;

// Paddles
constexpr int paddleWidth = 20;
constexpr int paddleHeight = 100;

// Ball
constexpr int ballRadius = 10;
const sf::Vector2f ballInitialPosition(width/2.f, height/2.f);
const sf::Vector2f ballInitialVelocity(-7.f, 7.f);
