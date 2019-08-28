//
//  Transform.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Transform.hpp"
#include <iostream>

const glm::vec3 Transform::WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

Transform::Transform() : Transform::Transform(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

Transform::Transform(glm::vec3 pos) : Transform::Transform(pos, glm::vec3(0.0f, 0.0f, 0.0f))
{
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot) : Transform::Transform(pos, rot, glm::vec3(1,1,1))
{
    
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) :
Position(pos),
Rotation(rot),
Scale(scale),
Forward(forward),
Right(right),
Up(up)
{
    
}

void Transform::CalculateDirection()
{
    glm::vec3 forwardLocal;
    
    // uses the z axis as the front
    // credit: Alex ABaronov in the comments: https://learnopengl.com/Getting-started/Camera
    forwardLocal.x = sin(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.x));
    forwardLocal.y = sin(glm::radians(Rotation.x));
    forwardLocal.z = -cos(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.x));
    
    forward = glm::normalize(forwardLocal);
    right = glm::normalize(glm::cross(forward, Transform::WorldUp));
    up = glm::normalize(glm::cross(right, forward));
}

