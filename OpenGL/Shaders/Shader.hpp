//
//  Shader.hpp
//  OpenGL
//
//  Created by James Kelly on 21/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
public:
    
    Shader (const char *vertexShaderPath, const char *fragmentShaderPath);
    
    /// Returns true if the shaders correctly compiled
    bool CompilationWasSuccessful () const;
    
    /// Sets OpenGL to use this shader program
    void Select ();
    
    GLuint GetShaderID () const;
    
protected:
    
    /// Reads the shader file's text
    std::string ReadShader (const char *path, bool &success) const;
    
    GLuint shaderProgram, vertexShader, fragmentShader;
    
private:
    
    Shader() {}   // Hide default constructor
    
    // result checking
    bool foundVertexShader, foundFragmentShader;
    GLint vertexShaderResult, fragmentShaderResult, shaderProgramResult;
    char vertexShaderLog[512];
    char fragmentShaderLog[512];
    char shaderProgramLog[512];
};

#endif /* Shader_hpp */
