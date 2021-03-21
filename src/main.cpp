#include <SFML/Graphics.hpp>
#include <iostream>
#include "grid.h"

int main()
{
    const unsigned int WIDTH = 1280;
    const unsigned int HEIGHT = 720;

    const unsigned int resolution = 20;

    Grid grid(WIDTH, HEIGHT, resolution, 32, 18);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "VecPath", sf::Style::Titlebar | sf::Style::Close);
    sf::Color background(0,0,0);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Return)
                    {
                        if(!grid.walls_placed)
                        {
                            grid.walls_placed = true;
                            grid.update_heatmap();
                            grid.update_field();
                            //std::cout << grid.grid_array[0].score << "\n";
                        }
                    }
            }
        }

        if(!grid.walls_placed)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                if(position.x >= 0 && position.x < WIDTH-1
                        && position.y >= 0 && position.y < HEIGHT-1)
                {
                    int ix = (int) position.x / grid.resolution;
                    int iy = (int) position.y / grid.resolution;
                    grid.grid_array[grid.cols * iy + ix].wall = true;
                    grid.grid_array[grid.cols * iy + ix].rect.setFillColor(sf::Color(0,0,0));
                }
            }
        }
        window.clear(background);
        grid.draw(window);
        window.display();
    }
    return 0;
}
