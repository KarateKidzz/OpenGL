//
//  Input.hpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <GLFW/glfw3.h>

/// Represents a static location of all user inputs on the current frame
class Input
{
public:
    Input(GLFWwindow* window);
    static void Update ();
    static float MouseXOffset();
    static float MouseYOffset();
    static float ScrollXOffset();
    static float ScrollYOffset();
    
    static bool GetKeyDown (int key);
    
    static void Quit ();
    
private:
    static GLFWwindow* window;
    
    static float mouseXOffset;
    static float mouseYOffset;
    static float scrollXOffset;
    static float scrollYOffset;
    
    static float lastMouseX;
    static float lastMouseY;
    
    static bool firstMouseMovement;
    
    static void MouseMoveCallback (GLFWwindow* window, double xPosition, double yPosition);
    static void ScrollMoveCallback (GLFWwindow* window, double xOffset, double yOffset);
};

#endif /* Input_hpp */
