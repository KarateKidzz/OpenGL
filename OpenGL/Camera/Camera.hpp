//
//  Camera.hpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "../Objects/WorldObject.hpp"
#include "../Application/Input.hpp"

/// Represents a position and rotation that can be moved by the user and return a View Matrix
class Camera : WorldObject
{
public:
    glm::mat4 GetViewMatrix();
    void Update (const float& deltaTime) override;
};

#endif /* Camera_hpp */
