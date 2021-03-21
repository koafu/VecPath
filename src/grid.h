#pragma once
#include <SFML/Graphics.hpp>
#include "node.h"

class Grid
{
public:
    int cols, rows;
    int resolution;
    
    Node* grid_array = nullptr;
    sf::Vector2f* vector_field = nullptr;
    Node* target;

    bool walls_placed;

    Grid() = default;
    Grid(int width, int height, int resolution, int init_target_x, int init_target_y);
    ~Grid();

    void build();
    void update_neighbors();
    void update_heatmap();
    void update_field();
    void draw(sf::RenderWindow &window);

private:
    Node* min_score(std::vector<Node*> &set);
    double max_score(std::vector<Node*> &set);
    double dist(Node* a, Node* b);
};
