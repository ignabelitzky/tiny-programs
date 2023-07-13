#pragma once

#include <random>
#include <ctime>
#include <iostream>
#include <fstream>

float getRandomFloat(float min, float max);

void saveMaxScore(int maxScore);

int retrieveMaxScore();
