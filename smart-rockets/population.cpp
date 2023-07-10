#include "population.h"

Population::Population(int size) {
    for(int i = 0; i < size; ++i) {
        Rocket rocket;
        m_rockets.push_back(rocket);
    }
}

Population::~Population() {
    m_rockets.clear();
    m_matingPool.clear();
}

void Population::evaluate(sf::Vector2f targetPos) {
    float maxFit = 0.0f;
    for(size_t i = 0; i < m_rockets.size(); ++i) {
        m_rockets[i].calcFitness(targetPos);
        if(m_rockets[i].getFitness() > maxFit) {
            maxFit = m_rockets[i].getFitness();
        }
    }
    for(size_t i = 0; i < m_rockets.size(); ++i) {
        m_rockets[i].setFitness(m_rockets[i].getFitness() / maxFit);
    }
    m_matingPool.clear();
    for(size_t i = 0; i < m_rockets.size(); ++i) {
        float n = m_rockets[i].getFitness() * 100;
        for(size_t j = 0; j < n; ++j) {
            m_matingPool.push_back(m_rockets[i]);
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
    size_t n = m_rockets.size();
    m_rockets.clear();
    for(size_t i = 0; i < n; ++i) {
        DNA parentA = getRandomElement(m_matingPool).getDNA();
        DNA parentB = getRandomElement(m_matingPool).getDNA();
        DNA child = parentA.crossover(parentB);
        child.mutation();
        m_rockets.push_back(Rocket(child));
    }
}

void Population::run(sf::RenderWindow& window, sf::Vector2f targetPos) {
    for(size_t i = 0; i < m_rockets.size(); ++i) {
        m_rockets[i].update(targetPos);
        m_rockets[i].show(window);
    }
}

int Population::size() {
    return m_rockets.size();
}
