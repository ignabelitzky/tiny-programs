#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <string>
#include <chrono>

std::wstring map;

float playerX = 8.0f;
float playerY = 8.0f;
float playerA = 0.0f;

int screenWidth = 0;
int screenHeight = 0;

int mapHeight = 16;
int mapWidth = 16;

float FOV = 3.14159 / 4.0;
float depth = 16.0f;

bool quit = false;

int input = 0;

auto tp1 = std::chrono::system_clock::now();
auto tp2 = std::chrono::system_clock::now();

#endif
