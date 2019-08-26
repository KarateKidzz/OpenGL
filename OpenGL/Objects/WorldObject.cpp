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

WorldObject::WorldObject(glm::vec3 pos, glm::vec3 rot) : Transform(pos, rot)
{
    Start();
    Component c;
    c.Update();
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
