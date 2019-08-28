//
//  Camera.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Camera.hpp"
#include "../Shaders/Shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../Windows/Display.hpp"

#include <iostream>

void Camera::Update(const float& deltaTime)
{
    // process keyboard input
    float velocity = movementSpeed * deltaTime;
    
    if (Input::GetKeyDown(GLFW_KEY_W))
        Transform->Position += forward * velocity;
    if (Input::GetKeyDown(GLFW_KEY_S))
        Transform->Position -= forward * velocity;
    if (Input::GetKeyDown(GLFW_KEY_A))
        Transform->Position -= right * velocity;
    if (Input::GetKeyDown(GLFW_KEY_D))
        Transform->Position += right * velocity;
    if (Input::GetKeyDown(GLFW_KEY_E))
        Transform->Position += up * velocity;
    if (Input::GetKeyDown(GLFW_KEY_Q))
        Transform->Position -= up * velocity;
    
    // process mouse movement
    float mouseX = Input::MouseXOffset() * mouseSensitivity;
    float mouseY = Input::MouseYOffset() * mouseSensitivity;
    
    Transform->Rotation.y += mouseX;
    Transform->Rotation.x += mouseY;
    
    if (Transform->Rotation.x > 89.0f)
        Transform->Rotation.x = 89.0f;
    if (Transform->Rotation.x < -89.0f)
        Transform->Rotation.x = -89.0f;
    
    // recalculate vectors
    CalculateVectors();
    
    UpdateView();
}

void Camera::UpdateView()
{
    view = glm::lookAt(GetWorldObject().Transform.Position, GetWorldObject().Transform.Position + forward, up);
    
    for (const Shader* s : shaders)
    {
        if(s)
        {
            s->Select();
            s->setMat4("view", view);
            s->Deselect();
        }
    }
}

void Camera::CalculateVectors()
{
    glm::vec3 forwardLocal;
    
    // uses the x axis as the front so is 90 degress off (faces +X and not -Z)
//    forwardLocal.x = cos(glm::radians(Transform->Rotation.y)) * cos(glm::radians(Transform->Rotation.x));
//    forwardLocal.y = sin(glm::radians(Transform->Rotation.x));
//    forwardLocal.z = sin(glm::radians(Transform->Rotation.y)) * cos(glm::radians(Transform->Rotation.x));
    
    // uses the z axis as the front
    // credit: Alex ABaronov in the comments: https://learnopengl.com/Getting-started/Camera
    forwardLocal.x = sin(glm::radians(Transform->Rotation.y)) * cos(glm::radians(Transform->Rotation.x));
    forwardLocal.y = sin(glm::radians(Transform->Rotation.x));
    forwardLocal.z = -cos(glm::radians(Transform->Rotation.y)) * cos(glm::radians(Transform->Rotation.x));

    forward = glm::normalize(forwardLocal);
    right = glm::normalize(glm::cross(forward, Transform::WorldUp));
    up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Camera::GetViewMatrix() const
{
    return view;
}

Camera::Camera(float movementSpeed, float mouseSensitivity) : Component::Component(), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity) {
}

void Camera::Awake()
{
    CalculateVectors();
}

void Camera::AddShader(Shader *shader)
{
    shader->Select();
    int w,h;
    Display::GetScreenSize(w, h);
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
    shader->setMat4("projection", projection);
    shader->Deselect();

    shaders.push_back(shader);
}
