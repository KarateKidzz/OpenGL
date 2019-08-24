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
    float velocity = MovementSpeed * deltaTime;
    
    if (Input::GetKeyDown(GLFW_KEY_W))
        Transform.Position += Transform.Forward() * velocity;
    if (Input::GetKeyDown(GLFW_KEY_S))
        Transform.Position -= Transform.Forward() * velocity;
    if (Input::GetKeyDown(GLFW_KEY_A))
        Transform.Position += Transform.Right() * velocity;
    if (Input::GetKeyDown(GLFW_KEY_D))
        Transform.Position += Transform.Right() * velocity;
}
