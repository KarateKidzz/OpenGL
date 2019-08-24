//
//  WorldObject.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "WorldObject.hpp"

WorldObject::WorldObject() : WorldObject::WorldObject(glm::vec3(0.0f, 0.0f, 0.0f))
{

}

WorldObject::WorldObject(glm::vec3 pos) : WorldObject::WorldObject(pos, glm::vec3(0.0f, 0.0f, 0.0f))
{

}

WorldObject::WorldObject(glm::vec3 pos, glm::vec3 rot) : Transform(pos, rot)
{
    Start();
}
