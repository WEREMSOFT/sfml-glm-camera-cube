#pragma once
#include "constants.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

class Camera
{
    glm::mat4 projection;
    glm::vec3 position;
    float fov;

public:
    glm::vec4 renderPlane;
    glm::mat4 transform;

    void setPosition(glm::vec3 pPosition)
    {
        position = pPosition;
        updateTransform();
    }

    void updateTransform()
    {
        transform = projection * glm::translate(glm::mat4(1.0), position);
    }

    Camera(float pFov = 60.f, glm::vec3 pPosition = (glm::vec3){0, 0, -50.f}) : fov(pFov), position(pPosition)
    {
        projection = glm::perspective(glm::radians(fov), (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f, 100.f);
        updateTransform();
        renderPlane = glm::vec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
};
