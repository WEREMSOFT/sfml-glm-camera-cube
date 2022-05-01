#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "constants.hpp"
#include <string.h>

class Canvas
{
    sf::Texture canvasT;
    sf::Sprite canvasS;
    sf::Image canvasI;
    sf::Image canvasIO;

public:
    Canvas()
    {
        canvasI.create(SCREEN_WIDTH, SCREEN_HEIGHT, (sf::Color){255, 0, 0, 255});
        canvasIO.create(SCREEN_WIDTH, SCREEN_HEIGHT, (sf::Color){255, 0, 0, 255});

        canvasT.loadFromImage(canvasI);
        canvasS.setTexture(canvasT);
        canvasS.scale(WINDOW_SIZE_FACTOR, WINDOW_SIZE_FACTOR);
    }

    void draw(sf::RenderWindow *window)
    {
        canvasT.loadFromImage(canvasI);
        window->draw(canvasS);
    }

    void setPixel(int x, int y, sf::Color color)
    {
        int tempX = fmin(SCREEN_WIDTH, fmax(x, 0));
        if (tempX != x)
            return;

        int tempY = fmin(SCREEN_HEIGHT, fmax(y, 0));
        if (tempY != y)
            return;

        canvasI.setPixel(x, y, color);
    }

    void clear()
    {
        void *dest = (void *)canvasI.getPixelsPtr();
        void *src = (void *)canvasIO.getPixelsPtr();
        memcpy(dest, src, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
    }
};