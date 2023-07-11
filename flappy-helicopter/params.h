#pragma once

constexpr int width = 1600;
constexpr int height = 900;

// Bird properties
constexpr int helicopterRadius = 50;
constexpr int helicopterStartPositionX = 140;
constexpr int helicopterStartPositionY = height/2;


// Pipe properties
constexpr int pipeStartPositionX = width;
constexpr int pipeStartPositionY = 0;
constexpr int minPipeWidth = 30;
constexpr int maxPipeWidth = 80;
constexpr int minPipeHeight = 30;
constexpr int maxPipeHeight = height - 5 * helicopterRadius;
