//
//  Application.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Application.hpp"


Application::Application() :
openGLLoader(nullptr),
input(nullptr),
screenWidth(800),
screenHeight(600),
screenTitle("OpenGL"),
window(nullptr)
{
    // Load OpenGL
    openGLLoader = std::unique_ptr<OpenGLLoader>(new OpenGLLoader(screenWidth,screenHeight, screenTitle.c_str()));
    
    if (!openGLLoader->LoadingSuccessful())
    {
        std::cerr << openGLLoader->GetErrorMessage() << std::endl;
    }
    
    window = openGLLoader->Display.GetWindow();
}


const int Application::Execute() {
    
    while (!glfwWindowShouldClose(window))
    {
        // Delta Time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Update User Input
        input->Update();
    }
    return 0;
}
