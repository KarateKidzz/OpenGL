//
//  Transform.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Transform.hpp"


Transform::Transform() : Transform::Transform(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

Transform::Transform(glm::vec3 pos) : Transform::Transform(pos, glm::vec3(0.0f, 0.0f, 0.0f))
{
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot) : position(pos), rotation(rot), worldUp(0.0f, 1.0f, 0.0f)
{
    
}

void Transform::UpdateVectors()
{
    // Calculate the new Front vector
    glm::vec3 frontLocal;
    frontLocal.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    frontLocal.y = sin(glm::radians(rotation.x));
    frontLocal.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    forward = glm::normalize(frontLocal);
    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(forward, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, forward));
}

glm::vec3 &Transform::Position() { 
    return position;
}

glm::vec3 &Transform::Rotation() {
    // because we are giving reference to the full structure the values could change at any time
    // if we calculated the vectors before passing the reference, the vectors would stay the same as nothing changed
    // and if we did some hack to pass reference and then update, an update could happen anywhere else
    // so this solution means we flag the vectors to be updated and the next time they're accessed we update them
    requireVectorUpdate = true;
    return rotation;
}

const glm::vec3 &Transform::GetUpVector()
{
    if  (requireVectorUpdate)
    {
        UpdateVectors();
    }
    return up;
}

const glm::vec3 &Transform::GetForwardVector()
{
    if  (requireVectorUpdate)
    {
        UpdateVectors();
    }
    return forward;
}

const glm::vec3 &Transform::GetRightVector()
{
    if  (requireVectorUpdate)
    {
        UpdateVectors();
    }
    return right;
}

