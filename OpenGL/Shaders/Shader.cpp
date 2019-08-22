//
//  Shader.cpp
//  OpenGL
//
//  Created by James Kelly on 21/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Shader.hpp"


Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) :
foundVertexShader(false),
foundFragmentShader(false),
vertexShaderResult(false),
fragmentShaderResult(false),
shaderProgramResult(false),
vertexShader(0),
fragmentShader(0),
shaderProgram(0)
{
    // get source files
    std::string vertexText = ReadShader(vertexShaderPath, foundVertexShader);
    std::string fragmentText = ReadShader(fragmentShaderPath, foundFragmentShader);
    
    const GLchar* vertexSource = vertexText.c_str();
    const GLchar* fragmentSource = fragmentText.c_str();
    
    if (!foundVertexShader || !foundFragmentShader)
    {
        return;
    }
    
    // create vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    
    // check result
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderResult);
    if (!vertexShaderResult)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertexShaderLog);
        std::cerr << vertexShaderLog << std::endl;
    }
    
    // create fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    
    // check result
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderResult);
    if (!fragmentShaderResult)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentShaderLog);
        std::cerr << fragmentShaderLog << std::endl;
    }
    
    // create shader program
    shaderProgram = glCreateProgram();
    
    // link shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // check result
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramResult);
    if(!shaderProgramResult)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, shaderProgramLog);
        std::cerr << shaderProgramLog << std::endl;
    }
    
    // delete shaders as they're connected to the program now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

bool Shader::CompilationWasSuccessful() const {
    return foundVertexShader && foundFragmentShader && vertexShaderResult && fragmentShaderResult && shaderProgramResult;
}

void Shader::Select() { 
    glUseProgram(shaderProgram);
}

std::string Shader::ReadShader(const char *path, bool &success) const
{
    std::string content;
    std::ifstream fileStream;
    
    fileStream.open(path);
    
    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
        success = false;
        return nullptr;
    }
    
    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    
    fileStream.close();
    
    success = true;
    
    return content;
}

GLuint Shader::GetShaderID() const
{
    return shaderProgram;
}
