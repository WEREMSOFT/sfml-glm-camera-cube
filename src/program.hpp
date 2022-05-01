#pragma once
#include <stdio.h>

#include "fpsCounter.hpp"
#include "constants.hpp"
#include "canvas.hpp"
#include "cube.hpp"

#include <SFML/Graphics.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <vector>

class Program
{
    sf::RenderWindow *window;
    Canvas canvas;
    FPSCounter fpsCounter;
    Cube cube;
    Camera camera;
    glm::vec3 cameraPosition = camera.position;
    float cameraSpeed = 50.f;

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

    void handleKeyboardEvents(float deltaTime)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            cameraPosition.x += cameraSpeed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            cameraPosition.x -= cameraSpeed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            cameraPosition.z += cameraSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            cameraPosition.z -= cameraSpeed * deltaTime;
        }

        camera.setPosition(cameraPosition);
        camera.updateTransform();
    }

public:
    Program()
    {
        window = new sf::RenderWindow(
            sf::VideoMode(SCREEN_WIDTH * WINDOW_SIZE_FACTOR,
                          SCREEN_HEIGHT * WINDOW_SIZE_FACTOR),
            "3D CAMERA!!!");
        window->setFramerateLimit(60);
        cube.initCube(30, 1);
    }

    void runMainLoop(void)
    {
        sf::Clock clock;
        float cubeRotation = 0;
        while (window->isOpen())
        {
            auto time = clock.restart();
            checkForExitConditions();
            handleKeyboardEvents(time.asSeconds());
            canvas.clear();
            cubeRotation += 0.5f * time.asSeconds();
            cube.rotate(cubeRotation, glm::vec3(1, 1, 1));
            cube.updateTransform();
            cube.draw(canvas, camera);
            canvas.draw(window);
            fpsCounter.draw(window);
            window->display();
        }
    }
};
