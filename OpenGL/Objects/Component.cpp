//
//  Component.cpp
//  OpenGL
//
//  Created by James Kelly on 26/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Component.hpp"
#include "WorldObject.hpp"

Component::Component() : Transform(nullptr){
}

Component::Component(WorldObject *worldObject) : Component::Component() {
    worldObject->AttachComponent(this);
}

WorldObject &Component::GetWorldObject() const
{
    return *worldObject;
}

void Component::AssignWorldObject (WorldObject* worldObject)
{
    this->worldObject = worldObject;
    Transform = &worldObject->Transform;
    Awake();
//    Start();
}
