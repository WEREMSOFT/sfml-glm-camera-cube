#pragma once
#include <stdio.h>

#include "fpsCounter.hpp"
#include "constants.hpp"
#include "canvas.hpp"
#include "cube.hpp"

#include <SFML/Graphics.hpp>

#include <glm/vec3.hpp>

#include <vector>

class Program
{
    sf::RenderWindow *window;
    Canvas canvas;
    FPSCounter fpsCounter;
    Cube cube;

    void checkForExitConditions(void)
    {
        static sf::Event evt;
        while (window->pollEvent(evt))
        {
            if (evt.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window->close();
        }
    }

public:
    Program()
    {
        window = new sf::RenderWindow(
            sf::VideoMode(SCREEN_WIDTH * WINDOW_SIZE_FACTOR,
                          SCREEN_HEIGHT * WINDOW_SIZE_FACTOR),
            "3D CAMERA!!!");
        window->setFramerateLimit(60);
        cube.initCube(100, 2);
    }

    void runMainLoop(void)
    {

        while (window->isOpen())
        {
            checkForExitConditions();
            cube.draw(canvas);
            canvas.draw(window);
            fpsCounter.draw(window);
            window->display();
        }
    }
};
