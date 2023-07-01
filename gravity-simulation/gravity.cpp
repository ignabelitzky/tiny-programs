#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

class GravitySource {
    sf::Vector2f pos;
    float strength;
    sf::CircleShape s;
    public:
        GravitySource(float pos_x, float pos_y, float strength) {
            pos.x = pos_x;
            pos.y = pos_y;
            this->strength = strength;
            s.setPosition(pos);
            s.setFillColor(sf::Color::White);
            s.setRadius(20);
        }

        void render(sf::RenderWindow& wind) {
            wind.draw(s);
        }

        sf::Vector2f get_pos() {
            return pos;
        }

        float get_strength() {
            return strength;
        }
};

class Particle {
    private:
        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::CircleShape s;

    public:
        Particle(float pos_x, float pos_y, float vel_x, float vel_y) {
            pos.x = pos_x;
            pos.y = pos_y;
            vel.x = vel_x;
            vel.y = vel_y;
            s.setPosition(pos);
            s.setFillColor(sf::Color::White);
            s.setRadius(1.5f);
        }

        void render(sf::RenderWindow& wind) {
            s.setPosition(pos);
            wind.draw(s);
        }

        void update_physics(GravitySource &s) {
            float distance_x = s.get_pos().x - pos.x;
            float distance_y = s.get_pos().y - pos.y;

            float distance = std::sqrt(distance_x * distance_x + distance_y * distance_y);

            float inverse_distance = 1.f / distance;

            float normalized_x = inverse_distance * distance_x;
            float normalized_y = inverse_distance * distance_y;

            float inverse_square_dropoff = inverse_distance * inverse_distance;

            float acceleration_x = normalized_x * s.get_strength() * inverse_square_dropoff;
            float acceleration_y = normalized_y * s.get_strength() * inverse_square_dropoff;

            vel.x += acceleration_x;
            vel.y += acceleration_y;

            pos.x += vel.x;
            pos.y += vel.y;
        }

        sf::Vector2f get_pos() {
            return pos;
        }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "My Program");
    window.setVerticalSyncEnabled(true);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> velDist(1.0f, 5.0f);
    std::uniform_real_distribution<float> posXDist(0.0f, 1600.0f);
    std::uniform_real_distribution<float> posYDist(0.0f, 900.0f);

    GravitySource source(800, 450, 7000);
    std::vector<Particle> particles;
    for(int i = 0; i < 500; ++i) {
        Particle p(posXDist(gen), posYDist(gen), velDist(gen), velDist(gen));
        particles.push_back(p);
    }

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        for(int i = 0; i < particles.size(); ++i) {
            particles.at(i).update_physics(source);
            particles.at(i).render(window);
        }
        source.render(window);
        window.display();
    }
    return 0;
}
