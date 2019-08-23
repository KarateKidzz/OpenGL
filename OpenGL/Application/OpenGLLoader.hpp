//
//  OpenGLLoader.hpp
//  OpenGL
//
//  Created by James Kelly on 22/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef OpenGLLoader_hpp
#define OpenGLLoader_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../Windows/Display.hpp"

/// Handles static loading of glfw and glad. Loads the first window
class OpenGLLoader
{
public:
    OpenGLLoader();
    OpenGLLoader(int windowWidth, int windowHeight, const char* windowTitle);
    
    ~OpenGLLoader();
    
    bool LoadingSuccessful () const;
    
    std::string GetErrorMessage () const;
    
    Display Display;
    
private:
    static void glfwErrorCallback(int error, const char* description);
    
    bool loadSuccessful;
    std::string errorMessage;
};

#endif /* OpenGLLoader_hpp */
