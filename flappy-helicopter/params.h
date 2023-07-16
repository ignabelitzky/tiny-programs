#pragma once

constexpr int width = 1920;
constexpr int height = 1000;

// Bird properties
constexpr int helicopterWidth = 150;
constexpr int helicopterHeight = 75;
constexpr int helicopterStartPositionX = 250;
constexpr int helicopterStartPositionY = height/2;


// Pipe properties
constexpr int pipeStartPositionX = width;
constexpr int pipeStartPositionY = 0;
constexpr int minPipeWidth = 80;
constexpr int maxPipeWidth = 160;
constexpr int minPipeHeight = 30;
constexpr int maxPipeHeight = height - 3 * helicopterHeight;
