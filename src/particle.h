#pragma once

struct Particle
{
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;

    double max_speed;
    double max_force;
};
