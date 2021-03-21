#include "node.h"

Node::Node(int x, int y, int resolution)
    : x(x), y(y)
{
    score = 999999;
    wall = false;

    rect.setPosition(x * resolution, y * resolution);
    rect.setSize(sf::Vector2f(resolution, resolution));
    rect.setFillColor(sf::Color(255,255,255,255));

    //vec.x = 0; vec.y = 0;
}

Node::~Node()
{
}

void Node::add_neighbors(Node grid[], int cols, int rows)
{
    neighbors.clear();

    // adjacent neighbors
    if(y-1 >= 0)
    {
        neighbors.push_back(&grid[cols * (y-1) + x]);
    }
    if(y+1 < rows)
    {
        neighbors.push_back(&grid[cols * (y+1) + x]);
    }
    if(x-1 >= 0)
    {
        neighbors.push_back(&grid[cols * y + (x-1)]);
    }
    if(x+1 < cols)
    {
        neighbors.push_back(&grid[cols * y + (x+1)]);
    }

    // diagonal neighbors
    if(x-1 >= 0 && y-1 >= 0)
    {
        neighbors.push_back(&grid[cols * (y-1) + (x-1)]);
    }
    if(x+1 < cols && y-1 >= 0)
    {
        neighbors.push_back(&grid[cols * (y-1) + (x+1)]);
    }
    if(x-1 >= 0 && y+1 < rows)
    {
        neighbors.push_back(&grid[cols * (y+1) + (x-1)]);
    }
    if(x+1 < cols && y+1 < rows)
    {
        neighbors.push_back(&grid[cols * (y+1) + (x+1)]);
    }
}
