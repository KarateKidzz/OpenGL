//
//  OpenGLLoader.cpp
//  OpenGL
//
//  Created by James Kelly on 22/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "OpenGLLoader.hpp"


OpenGLLoader::OpenGLLoader() : OpenGLLoader::OpenGLLoader(800, 600, "OpenGL")
{

}

OpenGLLoader::OpenGLLoader(int windowWidth, int windowHeight, const char* windowTitle) :
loadSuccessful(false),
errorMessage(""),
Display(windowWidth, windowHeight, windowTitle)
{
    glfwSetErrorCallback(glfwErrorCallback);
    
    if (!glfwInit())
    {
        loadSuccessful = false;
        errorMessage = "Failed to initalise glfw";
        return;
    }
    
    if(!Display.Create())
    {
        loadSuccessful = false;
        errorMessage = "Failed to create window";
        return;
    }
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        loadSuccessful = false;
        errorMessage = "Failed to load glad";
        glfwTerminate();
        return;
    }
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    
    glViewport(0, 0, windowWidth, windowHeight);
    
    loadSuccessful = true;
}

OpenGLLoader::~OpenGLLoader() { 
    glfwTerminate();
}

bool OpenGLLoader::LoadingSuccessful() const
{
    return loadSuccessful;
}

std::string OpenGLLoader::GetErrorMessage() const
{
    return errorMessage;
}

void OpenGLLoader::glfwErrorCallback(int error, const char *description) { 
    fprintf(stderr, "Error: %s\n", description);
}
