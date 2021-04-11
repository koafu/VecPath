#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "grid.h"
#include "node.h"

Grid::Grid(int width, int height, int resolution, int i_target_x, int i_target_y)
    : resolution(resolution)
{
    cols = width / resolution;
    rows = height / resolution;

    grid_array = new Node[cols * rows];
    vector_field = new sf::Vector2f[cols * rows];

    walls_placed = false;

    build();
    update_neighbors();

    target = &grid_array[cols * i_target_y + i_target_x];
    target->rect.setFillColor(sf::Color(63, 136, 196, 255));
}

Grid::~Grid()
{
    delete[] grid_array;
    delete[] vector_field;
}

void Grid::build()
{
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            grid_array[cols * y + x] = Node(x, y, resolution);
        }
    }
}

void Grid::update_neighbors()
{
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            grid_array[cols * y + x].add_neighbors(grid_array, cols, rows);
        }
    }
}

void Grid::update_heatmap()
{
    std::cout << "updating heatmap...\n";
    target->score = 0;

    std::vector<Node*> open_set;
    std::vector<Node*> closed_set;
    open_set.reserve(cols * rows);
    closed_set.reserve(cols * rows);

    open_set.push_back(target);

    while(!open_set.empty())
    {
        Node* current = min_score(open_set);
        auto it = std::find(std::begin(open_set), std::end(open_set), current);
        int current_index = it - open_set.begin();
        open_set.erase(open_set.begin() + current_index);
        closed_set.push_back(current);

        for(auto& neighbor : current->neighbors)
        {
            if(!neighbor->wall)
            {
                if(!std::count(closed_set.begin(), closed_set.end(), neighbor))
                {
                    double alt = current->score + dist(current, neighbor);
                    if(alt < neighbor->score)
                    {
                        neighbor->score = alt;
                    }
                    if(!std::count(open_set.begin(), open_set.end(), neighbor))
                    {
                        open_set.push_back(neighbor);
                    }
                }
            }
        }
    }
    double max = max_score(closed_set);
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            if(grid_array[cols * y + x].score <= max && &grid_array[cols * y + x] != target)
            {
                int brightness = (int) (255 / max) * grid_array[cols * y + x].score;
                grid_array[cols * y + x].rect.setFillColor(sf::Color(brightness, brightness, brightness, 255));
            }
        }
    }
}

void Grid::update_field()
{
    std::cout << "updating field...\n";
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            Node* node = &grid_array[cols * y + x];
            Node* min_neighbor = min_score(node->neighbors);
            node->vec = sf::Vector2f(min_neighbor->x, min_neighbor->y)
                - sf::Vector2f(x, y);
            node->line[0] = sf::Vertex(sf::Vector2f(x * resolution, y * resolution));
            node->line[1] = sf::Vertex(sf::Vector2f(x * resolution + node->vec.x * (resolution - 2),
                            y * resolution + node->vec.y * (resolution - 2)));
        }
    }
}

void Grid::draw(sf::RenderWindow &window)
{
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            window.draw(grid_array[cols * y + x].rect);
            window.draw(grid_array[cols * y + x].line, 2, sf::Lines);
        }
    }
}

Node* Grid::min_score(std::vector<Node*> &set)
{
    int min = 9999999;
    Node* current;
    for(auto& node : set)
    {
        if(node->score < min)
        {
            current = node;
            min = node->score;
        }
    }
    return current;
}

double Grid::max_score(std::vector<Node*> &set)
{
    double max = 0;
    for(auto& node : set)
    {
        if(node->score > max)
        {
            max = node->score;
        }
    }
    return max;
}

double Grid::dist(Node* a, Node* b)
{
    double dstX = pow(std::abs(a->x - b->x), 2);
    double dstY = pow(std::abs(a->y - b->y), 2);
    return std::sqrt(dstX + dstY);
}
