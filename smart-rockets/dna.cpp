#include "dna.h"

static float rndFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

static int rndNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

static sf::Vector2f rndVector() {
    float min = -1.0f, max = 1.0f;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return sf::Vector2f(dis(gen), dis(gen));
}

DNA::DNA() {
    for(int i = 0; i < lifespan; ++i) {
        this->genes.push_back(rndVector());
    }
}

// Copy constructor
DNA::DNA(const DNA& other) : genes(other.genes) {}


// Assignment operator
DNA& DNA::operator=(const DNA& other) {
    if(this != &other) {
        genes = other.genes;
    }
    return *this;
}

DNA::DNA(std::vector<sf::Vector2f> genes) {
    this->genes = genes;
}

DNA::~DNA() {
    genes.clear();
}

sf::Vector2f DNA::getGene(int index) {
    return this->genes.at(index);
}

DNA DNA::crossover(DNA partnerDNA) {
    std::vector<sf::Vector2f> newgenes;
    size_t mid = rndNumber(0, this->genes.size() - 1);
    for(size_t i = 0; i < this->genes.size(); ++i) {
        if(i > mid) {
            newgenes.push_back(this->genes[i]);
        } else {
            newgenes.push_back(partnerDNA.genes[i]);
        }
    }
    return DNA(newgenes);
}

void DNA::mutation() {
    for(size_t i = 0; i < this->genes.size(); ++i) {
        if(rndFloat(0.0f, 1.0f) < 0.01f) {
            this->genes[i] = rndVector();
        }
    }
}
