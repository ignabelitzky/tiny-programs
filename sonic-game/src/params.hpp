#pragma once

// Window
constexpr int windowWidth = 1600;
constexpr int windowHeight = 900;

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
constexpr int groundLevel = windowHeight-150;
constexpr int skyLevel = 100;
