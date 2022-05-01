#pragma once
#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define WINDOW_SIZE_FACTOR 3

class Canvas
{
    sf::Texture canvasT;
    sf::Sprite canvasS;

public:
    sf::Image canvasI;
    Canvas()
    {
        canvasI.create(SCREEN_WIDTH, SCREEN_HEIGHT, (sf::Color){255, 0, 0, 255});
        canvasT.loadFromImage(canvasI);
        canvasS.setTexture(canvasT);
        canvasS.scale(WINDOW_SIZE_FACTOR, WINDOW_SIZE_FACTOR);
    }

    void draw(sf::RenderWindow *window)
    {
        canvasT.loadFromImage(canvasI);
        window->draw(canvasS);
    }
};

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
