#pragma once

#include <SFML/Graphics.hpp>

class FPSCounter
{
    sf::Text fps;
    sf::Font font;
    sf::Clock clock;

public:
    FPSCounter()
    {
        font.loadFromFile("resources/JetBrainsMono-Regular.ttf");
        fps.setFont(font);
        fps.setString("This is a test!!!");
        fps.setCharacterSize(24);
    }

    void draw(sf::RenderWindow *window)
    {
        char fpsText[500] = "";
        float currentTime = clock.restart().asSeconds();
        float fpsC = 1.f / (currentTime);
        snprintf(fpsText, 100, "fps: %f", fpsC);
        sf::String strFPS(fpsText);
        fps.setString(strFPS);

        window->draw(fps);
    }
};