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
        Transform.Position += forward * velocity;
    if (Input::GetKeyDown(GLFW_KEY_S))
        Transform.Position -= forward * velocity;
    if (Input::GetKeyDown(GLFW_KEY_A))
        Transform.Position -= right * velocity;
    if (Input::GetKeyDown(GLFW_KEY_D))
        Transform.Position += right * velocity;
    if (Input::GetKeyDown(GLFW_KEY_E))
        Transform.Position += up * velocity;
    if (Input::GetKeyDown(GLFW_KEY_Q))
        Transform.Position -= up * velocity;
    
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
    CalculateVectors();
    
    UpdateView();
}

void Camera::UpdateView()
{
    view = glm::lookAt(Transform.Position, Transform.Position + forward, up);
}

void Camera::CalculateVectors()
{
    glm::vec3 forwardLocal;
    forwardLocal.x = cos(glm::radians(Transform.Rotation.y)) * cos(glm::radians(Transform.Rotation.x));
    forwardLocal.y = sin(glm::radians(Transform.Rotation.x));
    forwardLocal.z = sin(glm::radians(Transform.Rotation.y)) * cos(glm::radians(Transform.Rotation.x));
    forward = glm::normalize(forwardLocal);
    right = glm::normalize(glm::cross(forward, Transform::WorldUp));
    up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Camera::GetViewMatrix() const
{
    return view;
}

Camera::Camera(glm::vec3 pos, float movementSpeed, float mouseSensitivity) : WorldObject(pos), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity) {
    CalculateVectors();
}

