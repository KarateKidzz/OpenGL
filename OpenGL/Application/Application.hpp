//
//  Application.hpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <memory>
#include <string>
#include "../Utils/NonCopyable.h"
#include "OpenGLLoader.hpp"
#include "../Windows/Display.hpp"
#include "../Camera/Camera.hpp"
#include "Input.hpp"
#include "../Shaders/Shader.hpp"


/// Handles all runtime processing
class Application : NonCopyable
{
public:
    Application();
    
    /// Main execution. Returns exit code of the application
    const int Execute ();
    
private:
    // dynamically create our objects to do error checks before creating the next object
    std::unique_ptr<OpenGLLoader> openGLLoader;
    std::unique_ptr<Input> input;

    GLFWwindow* window;
    
    // application settings
    int screenWidth, screenHeight;
    std::string screenTitle;
    
    // runtime variables
    float deltaTime, lastFrame;
};

#endif /* Application_hpp */
