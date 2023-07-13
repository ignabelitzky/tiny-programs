#pragma once

// Window
constexpr int windowWidth = 1920;
constexpr int windowHeight = 1000;

// Sonic
constexpr int sonicXPos = 200;
constexpr int sonicYPos = windowHeight / 2;
constexpr float jumpSpeed = 80.0f;
constexpr float bounceFactor = 0.5f;
constexpr float sonicRadius = 50.0f;
constexpr float sonicGravity = 9.8f;
constexpr int jumpSpritesCount = 8;
constexpr int runSpritesCount = 16;
constexpr float frameDuration = 0.08f;

// World
constexpr int groundLevel = windowHeight-50;
constexpr int skyLevel = 100;
constexpr float floorSpeed = 20.0f;

// Enemy
constexpr float enemyRadius = 70.0f;
constexpr float enemyVelocity = floorSpeed;
constexpr int enemySpritesCount = 5;
