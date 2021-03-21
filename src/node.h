#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Node 
{
    int x, y;
    int score;
    bool wall;

    std::vector<Node*> neighbors = std::vector<Node*>(8);

    sf::RectangleShape rect;
    sf::Vector2f vec;
    sf::Vertex line[2];

    Node() = default;
    Node(int x, int y, int resolution);
    ~Node();

    void add_neighbors(Node grid[], int cols, int rows);
};
