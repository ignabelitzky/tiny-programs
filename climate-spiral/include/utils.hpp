#ifndef UTILS_HPP
#define UTILS_HPP

#include "constants.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void load_data_from_file(std::string filename, std::vector<std::vector<float>> &data, std::vector<std::string> &labels);

// Map a value from one range to another
float map(float value, float fromMin, float fromMax, float toMin, float toMax);

#endif