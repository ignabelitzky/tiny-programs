#ifndef UTILS_HPP
#define UTILS_HPP

#include "circle.hpp"
#include "params.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class Circle;

// vector math functions
float dot(const sf::Vector2f &v1, const sf::Vector2f &v2);
float magnitude_squared(const sf::Vector2f &v);

// kinematics functions
void handle_boundary_collision(float &pos, float &vel, float min_bound, float max_bound);
void apply_gravity(sf::Vector2f &position, sf::Vector2f &velocity, sf::CircleShape &shape, float deltaTime);
void collide(Circle &thisShape, Circle &otherShape);
bool detect_collisions(const sf::CircleShape &thisShape, const sf::CircleShape &otherShape);

#endif
