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
    float mouseSensitivity = 5.f;
    glm::vec2 mouseLast;

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

    void handleMouse(float deltaTime)
    {
        auto mouseCur = getMousePosition();
        // Y coordinates are inverted, soooo....
        glm::vec2 deltaMouse(mouseLast.x - mouseCur.x, mouseLast.y - mouseCur.y);
        mouseLast = mouseCur;
        deltaMouse *= mouseSensitivity * deltaTime;
        camera.yaw += deltaMouse.x;
        camera.pitch += deltaMouse.y;

        if (camera.pitch > 89.0)
            camera.pitch = 89.0;

        if (camera.pitch < -89.0)
            camera.pitch = -89.0;

        printf("%.2f %.2f\n", camera.yaw, camera.pitch);

        // I HAVE NO IDEA WHAT I'M DOING HERE!!
        glm::vec3 target;
        target.x = glm::cos(glm::radians(camera.yaw)) * glm::cos(glm::radians(camera.pitch));
        target.y = glm::sin(glm::radians(camera.pitch));
        target.z = glm::sin(glm::radians(camera.yaw)) * glm::cos(glm::radians(camera.pitch));
        target = glm::normalize(target) + camera.position;
        printf("%.2f %.2f %.2f\n", target.x, target.y, target.z);
        camera.setLookAt(target);
    }

    void handleInput(float deltaTime)
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

        handleMouse(deltaTime);

        camera.setPosition(cameraPosition);
        camera.updateTransform();
    }

    glm::vec2 getMousePosition()
    {
        auto mousePosition = sf::Mouse::getPosition();
        return glm::vec2(mousePosition.x, mousePosition.y);
    }

public:
    Program()
    {
        window = new sf::RenderWindow(
            sf::VideoMode(SCREEN_WIDTH * WINDOW_SIZE_FACTOR,
                          SCREEN_HEIGHT * WINDOW_SIZE_FACTOR),
            "3D CAMERA!!!");
        window->setFramerateLimit(60);
        cube.initCube(30, 2);
        mouseLast = getMousePosition();
    }

    void runMainLoop(void)
    {
        sf::Clock clock;
        float cubeRotation = 0;
        while (window->isOpen())
        {
            auto time = clock.restart();
            checkForExitConditions();
            handleInput(time.asSeconds());
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
