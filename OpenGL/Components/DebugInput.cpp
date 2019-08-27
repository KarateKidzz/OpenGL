//
//  DebugInput.cpp
//  OpenGL
//
//  Created by James Kelly on 27/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "DebugInput.hpp"
#include "../Application/Input.hpp"
#include <glad/glad.h>

void DebugInput::Update(const float &deltaTime) { 
    if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
        Input::Quit();
    if (Input::GetKeyDown(GLFW_KEY_1))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (Input::GetKeyDown(GLFW_KEY_2))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (Input::GetKeyDown(GLFW_KEY_3))
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}
