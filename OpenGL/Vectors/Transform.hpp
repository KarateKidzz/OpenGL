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
    
    /// World space position
    glm::vec3 Position;
    /// World space rotation in eulers
    glm::vec3 Rotation;
    
private:
    // flag to check if the up, forward and right vectors need to be calculated after a rotation update
    bool requireVectorUpdate;
    
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 worldUp;
    glm::vec3 up;
    glm::vec3 forward;
    glm::vec3 right;
    
    /// Recalculate up, front, right vectors
    void UpdateVectors ();
};

#endif /* Transform_hpp */
