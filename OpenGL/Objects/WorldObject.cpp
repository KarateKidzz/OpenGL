//
//  WorldObject.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "WorldObject.hpp"
#include "Component.hpp"

WorldObject::WorldObject() : WorldObject::WorldObject(glm::vec3(0.0f, 0.0f, 0.0f))
{

}

WorldObject::WorldObject(glm::vec3 pos) : WorldObject::WorldObject(pos, glm::vec3(0.0f, 0.0f, 0.0f))
{

}

WorldObject::WorldObject(glm::vec3 pos, glm::vec3 rot) : WorldObject::WorldObject(pos, rot, glm::vec3(1.0f, 1.0f, 1.0f))
{
}

WorldObject::WorldObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : Transform(pos, rot, scale)
{
}


void WorldObject::Update(const float &deltaTime)
{
    for (const std::unique_ptr<Component*>& c : Components)
    {
        if (*c != nullptr)
        {
            Component* component = *c;
            component->Update(deltaTime);
        }
    }
}


void WorldObject::AttachComponent(Component *component) {
    for (const std::unique_ptr<Component*>& c : Components)
    {
        // if the pointer already exists, return and don't add it
        // else, we will fall out of the loop and add it
        if (*c == component)
        {
            return;
        }
    }
    Components.push_back(std::make_unique<Component*>(component));
    component->AssignWorldObject(this);
}
