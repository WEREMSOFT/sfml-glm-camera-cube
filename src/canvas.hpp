#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "constants.hpp"

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