//
//  Display.hpp
//  OpenGL
//
//  Created by James Kelly on 20/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Display_hpp
#define Display_hpp

#include <glad/glad.h>
#include <iostream>

class GLFWwindow;

class Display
{
public:
    
    /// Creates a Dipslay with the specified parameters. Window creation happens during Create()
    Display (const int width, const int height, const char *title);
    
    /// Creates the OpenGL Window and returns whether it succeeded
    bool Create();
    
    /// Returns true if the window is destroyed or should close
    bool ShouldClose ();
    
    /// Clears the screen to black
    void Clear ();
    
    /// Renders objects on screen
    void Render ();
    
    /// Clears the window and updates input events
    void Update ();
    
    /// Returns the underlying OpenGL Window
    GLFWwindow* GetWindow () const;
    
protected:
    
    /// Main OpenGL Window
    GLFWwindow *window;
    
    int width;
    int height;
    const char *title;
    
private:
    
    Display() {}    // Hide default constructor
    
    static void FrameBufferSizeCallback (GLFWwindow *window, int width, int height);
    
};

#endif /* Display_hpp */
