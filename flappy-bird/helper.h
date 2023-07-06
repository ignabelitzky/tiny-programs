#pragma once

#include <random>
#include <ctime>
#include <iostream>
#include <fstream>

float getRandomFloat(float min, float max);

int getRandomInt(int min, int max);

void saveMaxScore(int maxScore);

int retrieveMaxScore();
