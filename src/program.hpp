#pragma once
#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "constants.hpp"
#include "canvas.hpp"

class Program
{
    sf::RenderWindow *window;
    Canvas canvas;
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
    }

    void runMainLoop(void)
    {
        while (window->isOpen())
        {
            checkForExitConditions();
            canvas.canvasI.setPixel(160, 120, (sf::Color){0, 0, 0, 255});
            canvas.draw(window);
            window->display();
        }
    }
};
