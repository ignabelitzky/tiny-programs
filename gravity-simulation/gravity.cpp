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
            s.setFillColor(sf::Color::Red);
            s.setOrigin(70.0f, 70.0f);
            s.setRadius(70.0f);
            s.setPosition(pos);
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
            s.setFillColor(sf::Color::Yellow);
            s.setOrigin(0.5f, 0.5f);
            s.setRadius(0.5f);
            s.setPosition(pos);
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
    constexpr int width = 1600;
    constexpr int height = 900;
    sf::RenderWindow window(sf::VideoMode(width, height), "Gravity");
    window.setVerticalSyncEnabled(true);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> velDist(0.1f, 1.0f);
    std::uniform_real_distribution<float> posXDist(0.0f, width);
    std::uniform_real_distribution<float> posYDist(0.0f, height);

    GravitySource source(width/2, height/2, 14000);
    std::vector<Particle> particles;
    for(int i = 0; i < 10000; ++i) {
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
        for (auto it = particles.begin(); it != particles.end();) {
            sf::Vector2f position = it->get_pos();
            if (position.x > width/2 - 50.0f && position.x < width/2 + 50.0f &&
                position.y > height/2 - 50.0f && position.y < height/2 + 50.0f) {
                it = particles.erase(it);
            } else {
                it->update_physics(source);
                it->render(window);
                ++it;
            }
        }
        source.render(window);
        window.display();
    }
    return 0;
}
