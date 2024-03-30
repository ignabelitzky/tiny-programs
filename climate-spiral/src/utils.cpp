#include "../include/utils.hpp"

static bool isValidFloat(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) {
                             return !std::isdigit(c) && c != '.' && c != '-';
                         }) == s.end();
}

void load_data_from_file(std::string filename, std::vector<std::vector<float>> &data, std::vector<std::string> &labels)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ','))
    {
        labels.push_back(token);
    }
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<float> row;
        while (std::getline(iss, token, ','))
        {
            if (isValidFloat(token))
            {
                row.push_back(std::stof(token));
            }
            else
            {
                row.push_back(0.0f);
                std::cerr << "Invalid float value: = " << token << std::endl;
            }
        }
        data.push_back(row);
    }
    for (auto row : data)
    {
        for (auto elem : row)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    file.close();
}

float map(float value, float fromMin, float fromMax, float toMin, float toMax)
{
    float ratio = (value - fromMin) / (fromMax - fromMin);
    float result = toMin + ratio * (toMax - toMin);
    return result;
}