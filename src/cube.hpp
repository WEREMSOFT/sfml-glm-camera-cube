#pragma once

#include <SFML/Graphics.hpp>
#include <glm/vec3.hpp>
#include <vector>

#include "canvas.hpp"

class Cube
{
    std::vector<glm::vec3> cube;

public:
    void initCube(int sideSize, float step)
    {
        cube.reserve(sideSize * sideSize * sideSize);
        float halfSize = sideSize / 2.f;
        // SHUT UP CLANG TIDY, I KNOW WHAT I'M DOING!!!
        for (float x = -halfSize; x < halfSize; x += step)
            for (float y = -halfSize; y < halfSize; y += step)
                for (float z = -halfSize; z < halfSize; z += step)
                    cube.emplace_back((glm::vec3){x, y, z});
    }
    void draw(Canvas &canvas)
    {
        auto size = cube.size();
        for (int i = 0; i < size; i++)
        {
            canvas.setPixel(cube[i].x, cube[i].y, (sf::Color){0, 0, 0, 255});
        }
    }
};