//
//  Display.cpp
//  OpenGL
//
//  Created by James Kelly on 20/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Display.hpp"

Display::Display(const int width, const int height, const char *title) :
    width(width),
    height(height),
    title(title),
    window(nullptr)
{
}

bool Display::ShouldClose()
{
    return window == nullptr || glfwWindowShouldClose(window);
}

bool Display::Create() {
    
    // return if window already exists
    if (window != nullptr)
    {
        return false;
    }
    
    // Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // removes backwards compatability as we don't need it
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // Create window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    
    // Unsuccessful window creation catch
    if (window == nullptr)
    {
        return false;
    };
    
    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    
    
    return true;
}



GLFWwindow* Display::GetWindow () const
{
    return window;
}

void Display::FrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{ 
    glViewport(0, 0, width, height);
}

void Display::Clear()
{ 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Render()
{
    
}


void Display::Update()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
