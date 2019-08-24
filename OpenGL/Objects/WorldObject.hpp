//
//  WorldObject.hpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef WorldObject_hpp
#define WorldObject_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Vectors/Transform.hpp"
#include "../Application/Application.hpp"

/// Represents a class that can be inherited from to give a world position and rotation. Should act as the base class for all objects in the scene
class WorldObject
{
    friend Application;
    
public:
    WorldObject();
    WorldObject(glm::vec3 pos);
    WorldObject(glm::vec3 pos, glm::vec3 rot);
    Transform Transform;
    
protected:
    virtual void Start() {}
    virtual void Update(const float& deltaTime) {}
};

#endif /* WorldObject_hpp */
