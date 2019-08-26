//
//  Camera.hpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include "../Vectors/Transform.hpp"
#include "../Objects/WorldObject.hpp"
#include "../Objects/Component.hpp"
#include "../Application/Input.hpp"

/// Represents a position and rotation that can be moved by the user and return a View Matrix
class Camera : public Component
{
public:
    Camera(float movementSpeed, float mouseSensitivity);
    glm::mat4 GetViewMatrix() const;
    void Awake() override;
    void Update (const float& deltaTime) override;
    
private:
    float movementSpeed;
    float mouseSensitivity;
    
    glm::mat4 view;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    
    void UpdateView ();
    void CalculateVectors ();
};

#endif /* Camera_hpp */
