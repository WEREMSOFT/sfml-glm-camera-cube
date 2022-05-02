#pragma once
#include "constants.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

class Camera
{
    glm::mat4 projection;
    float fov;

public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec4 renderPlane;
    glm::mat4 transform;

    float yaw = 0;
    float pitch = 0;

    void setPosition(glm::vec3 pPosition)
    {
        position = pPosition;
    }

    void setLookAt(glm::vec3 pTarget)
    {
        target = pTarget;
    }

    void updateTransform()
    {
        transform = projection * glm::lookAt(position, target, glm::vec3(0, 1.f, 0));
    }

    Camera(float pFov = 60.f, glm::vec3 pPosition = (glm::vec3){0, 0, -50.f}) : fov(pFov), position(pPosition)
    {
        projection = glm::perspective(glm::radians(fov), (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f, 100.f);
        setLookAt(glm::vec3(0, 0, 0));
        updateTransform();
        renderPlane = glm::vec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
};
