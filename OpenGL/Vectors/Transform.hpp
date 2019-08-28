//
//  Transform.hpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/// Represents a position and rotation with additional functionality like LookAt
class Transform
{
public:
    Transform ();
    Transform (glm::vec3 pos);
    Transform (glm::vec3 pos, glm::vec3 rot);
    Transform (glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
    
    /// World space position
    glm::vec3 Position;
    /// World space rotation in eulers
    glm::vec3 Rotation;
    /// World space scale
    glm::vec3 Scale;
    
    static const glm::vec3 WorldUp;
    
private:
};

#endif /* Transform_hpp */
