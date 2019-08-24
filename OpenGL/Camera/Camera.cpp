//
//  Camera.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Camera.hpp"

void Camera::Update(const float& deltaTime)
{
    // process keyboard input
    float velocity = movementSpeed * deltaTime;
    
    if (Input::GetKeyDown(GLFW_KEY_W))
        Transform.Position.x += Transform.Position.x * velocity;
    if (Input::GetKeyDown(GLFW_KEY_S))
        Transform.Position.x -= Transform.Position.x * velocity;
    if (Input::GetKeyDown(GLFW_KEY_A))
        Transform.Position.z += Transform.Position.z * velocity;
    if (Input::GetKeyDown(GLFW_KEY_D))
        Transform.Position.z += Transform.Position.z * velocity;
    
    // process mouse movement
    float mouseX = Input::MouseXOffset() * mouseSensitivity;
    float mouseY = Input::MouseYOffset() * mouseSensitivity;
    
    Transform.Rotation.y += mouseX;
    Transform.Rotation.x += mouseY;
    
    if (Transform.Rotation.x > 89.0f)
        Transform.Rotation.x = 89.0f;
    if (Transform.Rotation.x < -89.0f)
        Transform.Rotation.x = -89.0f;
    
    // recalculate vectors
    glm::vec3 forwardLocal;
    forwardLocal.x = cos(glm::radians(Transform.Rotation.y)) * cos(glm::radians(Transform.Rotation.x));
    forwardLocal.y = sin(glm::radians(Transform.Rotation.y));
    forwardLocal.z = cos(glm::radians(Transform.Rotation.y)) * sin(glm::radians(Transform.Rotation.x));
    forward = glm::normalize(forwardLocal);
    right = glm::normalize(glm::cross(forward, Transform::WorldUp));
    up = glm::normalize(glm::cross(right, forward));
}

void Camera::UpdateView()
{
    view = glm::lookAt(Transform.Position, Transform.Position + forward, up);
}

glm::mat4 Camera::GetViewMatrix() const
{
    return view;
}

Camera::Camera(glm::vec3 pos, float movementSpeed, float mouseSensitivity) : WorldObject(pos), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity) {
    
}

