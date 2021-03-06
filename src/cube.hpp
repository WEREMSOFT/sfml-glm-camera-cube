#pragma once

#include <SFML/Graphics.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <vector>

#include "canvas.hpp"
#include "camera.hpp"

class Cube
{
    std::vector<glm::vec3> cube;

public:
    glm::mat4 translate;
    glm::mat4 rotation;
    glm::mat4 transform;

    void updateTransform()
    {
        transform = translate * rotation;
    }

    Cube() : translate(1.0), rotation(1.0)
    {
        updateTransform();
    }

    void initCube(int sideSize, float step)
    {
        cube.reserve(sideSize * sideSize * sideSize);
        float halfSize = sideSize / 2.f;

        // SHUT UP CLANG TIDY, I KNOW WHAT I'M DOING!!!
        for (float x = -halfSize; x < halfSize; x += step)
            for (float y = -halfSize; y < halfSize; y += step)
                for (float z = -halfSize; z < halfSize; z += step)
                    if (z == -halfSize || z == halfSize - step ||
                        y == -halfSize || y == halfSize - step ||
                        x == -halfSize || x == halfSize - step)
                        cube.emplace_back((glm::vec3){x, y, z});
    }

    void rotate(float angle, glm::vec3 axis)
    {
        rotation = glm::rotate(glm::mat4(1.0), angle, axis);
    }

    void draw(Canvas &canvas, Camera camera)
    {
        updateTransform();
        auto size = cube.size();
        for (int i = 0; i < size; i++)
        {
            auto tempVertex = glm::project(cube[i], transform, camera.transform, camera.renderPlane);
            canvas.setPixel(tempVertex.x, tempVertex.y, (sf::Color){0, 0, 0, 255});
        }
    }
};