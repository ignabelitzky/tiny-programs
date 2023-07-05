#include "population.h"

Population::Population(int size) {
    for(int i = 0; i < size; ++i) {
        Rocket rocket;
        rockets.push_back(rocket);
    }
}

Population::~Population() {
}

void Population::evaluate(sf::Vector2f targetPos) {
    float maxFit = 0.0f;
    for(size_t i = 0; i < this->rockets.size(); ++i) {
        this->rockets[i].calcFitness(targetPos);
        if(this->rockets[i].getFitness() > maxFit) {
            maxFit = this->rockets[i].getFitness();
        }
    }
    for(size_t i = 0; i < this->rockets.size(); ++i) {
        this->rockets[i].setFitness(this->rockets[i].getFitness() / maxFit);
    }
    this->matingPool.clear();
    for(size_t i = 0; i < this->rockets.size(); ++i) {
        float n = this->rockets[i].getFitness() * 100;
        for(size_t j = 0; j < n; ++j) {
            this->matingPool.push_back(this->rockets[i]);
        }
    }
}

template<typename T>
static T getRandomElement(const std::vector<T>& vec)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dis(0, vec.size() - 1);

    std::size_t randomIndex = dis(gen);
    return vec[randomIndex];
}

void Population::selection() {
    std::vector<Rocket> newRockets;
    for(size_t i = 0; i < this->rockets.size(); ++i) {
        DNA parentA = getRandomElement(this->matingPool).getDNA();
        DNA parentB = getRandomElement(this->matingPool).getDNA();
        DNA child = parentA.crossover(parentB);
        child.mutation();
        newRockets.push_back(Rocket(child));
    }
    this->rockets = newRockets;
}

void Population::run(sf::RenderWindow& window, sf::Vector2f targetPos) {
    for(size_t i = 0; i < this->rockets.size(); ++i) {
        this->rockets[i].update(targetPos);
        this->rockets[i].show(window);
    }
}

int Population::size() {
    return this->rockets.size();
}
