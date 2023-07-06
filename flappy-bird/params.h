#pragma once

constexpr int width = 1600;
constexpr int height = 900;

// Bird properties
constexpr int birdRadius = 30;
constexpr int birdStartPositionX = 140;
constexpr int birdStartPositionY = height/2;


// Pipe properties
constexpr int pipeStartPositionX = width;
constexpr int pipeStartPositionY = 0;
constexpr int minPipeWidth = 20;
constexpr int maxPipeWidth = 80;
constexpr int minPipeHeight = 20;
constexpr int maxPipeHeight = height - 2 * birdRadius;
