//
//  Input.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Input.hpp"

float Input::mouseXOffset = 0;
float Input::mouseYOffset = 0;
float Input::scrollXOffset = 0;
float Input::scrollYOffset = 0;
float Input::lastMouseX = 0;
float Input::lastMouseY = 0;
bool Input::firstMouseMovement = true;
GLFWwindow* Input::window = nullptr;

Input::Input( GLFWwindow* window)
{
    if (Input::window == nullptr)
    {
        Input::window = window;
    }
    
    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetScrollCallback(window, ScrollMoveCallback);
}

float Input::MouseXOffset() { 
    return mouseXOffset;
}

float Input::MouseYOffset() { 
    return mouseYOffset;
}

float Input::ScrollXOffset() { 
    return scrollXOffset;
}

float Input::ScrollYOffset() { 
    return scrollYOffset;
}

bool Input::GetKeyDown (int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void Input::MouseMoveCallback(GLFWwindow *window, double xPosition, double yPosition) { 
    if (firstMouseMovement)
    {
        lastMouseX = xPosition;
        lastMouseY = yPosition;
        firstMouseMovement = false;
    }
}

void Input::ScrollMoveCallback(GLFWwindow *window, double xOffset, double yOffset) { 
    scrollXOffset = xOffset;
    scrollYOffset = yOffset;
}

