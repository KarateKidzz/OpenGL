#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Windows/Display.hpp"
#include "Shaders/Shader.hpp"
#include "Application/OpenGLLoader.hpp"
#include "Application/Input.hpp"
#include "Camera/Camera.hpp"
#include "Rendering/Mesh.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

/*
 For my future self:
 
 glad.h is the OpenGL Loading Library. Through this library we point to OpenGL functions.
 
 glfw3.h is an API for creating windows and handling user input.
 
 */

void processInput(GLFWwindow* window);                                      // handle input

const GLint WIDTH = 800, HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const Vertex Cube [] =
{
    // Positions            // Normals                  // Texture Coordinates
    
    // Front
    glm::vec3(-1, -1, -1),  glm::vec3(0.f, 0.f, 1.f),   glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(1, -1, -1),   glm::vec3(0.f, 0.f, 1.f),   glm::vec3(1.f, 0.f, 0.f),
    glm::vec3(1, 1, -1),    glm::vec3(0.f, 0.f, 1.f),   glm::vec3(1.f, 1.f, 0.f),
    glm::vec3(-1, 1, -1),   glm::vec3(0.f, 0.f, 1.f),   glm::vec3(0.f, 1.f, 0.f),
    
    // Back
    glm::vec3(-1, -1, 1),   glm::vec3(0.f, 0.f, -1.f),  glm::vec3(1.f, 1.f, 0.f),
    glm::vec3(1, -1, 1),    glm::vec3(0.f, 0.f, -1.f),  glm::vec3(0.f, 1.f, 0.f),
    glm::vec3(1, 1, 1),     glm::vec3(0.f, 0.f, -1.f),  glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(-1, 1, 1),    glm::vec3(0.f, 0.f, -1.f),  glm::vec3(1.f, 0.f, 0.f),
    
    // Top
    glm::vec3(-1, 1, -1),   glm::vec3(0.f, 1.f, 0.f),  glm::vec3(1.f, 1.f, 0.f),
    glm::vec3(1, 1, -1),    glm::vec3(0.f, 1.f, 0.f),  glm::vec3(0.f, 1.f, 0.f),
    glm::vec3(1, 1, 1),     glm::vec3(0.f, 1.f, 0.f),  glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(-1, 1, 1),    glm::vec3(0.f, 1.f, 0.f),  glm::vec3(1.f, 0.f, 0.f),
    
    // Bottom
    glm::vec3(-1, -1, -1),   glm::vec3(0.f, -1.f, 0.f),  glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(1, -1, -1),    glm::vec3(0.f, -1.f, 0.f),  glm::vec3(1.f, 0.f, 0.f),
    glm::vec3(1, -1, 1),     glm::vec3(0.f, -1.f, 0.f),  glm::vec3(1.f, 1.f, 0.f),
    glm::vec3(-1, -1, 1),    glm::vec3(0.f, -1.f, 0.f),  glm::vec3(0.f, 1.f, 0.f),
    
    // Right
    glm::vec3(1, -1, -1),   glm::vec3(1.f, 0.f, 0.f),  glm::vec3(1.f, 1.f, 0.f),
    glm::vec3(1, -1, 1),    glm::vec3(1.f, 0.f, 0.f),  glm::vec3(0.f, 1.f, 0.f),
    glm::vec3(1, 1, 1),     glm::vec3(1.f, 0.f, 0.f),  glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(1, 1, -1),    glm::vec3(1.f, 0.f, 0.f),  glm::vec3(1.f, 0.f, 0.f),
    
    // Left
    glm::vec3(-1, -1, -1),   glm::vec3(-1.f, 0.f, 0.f),  glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(-1, 1, -1),    glm::vec3(-1.f, 0.f, 0.f),  glm::vec3(1.f, 0.f, 0.f),
    glm::vec3(-1, 1, 1),     glm::vec3(-1.f, 0.f, 0.f),  glm::vec3(1.f, 1.f, 0.f),
    glm::vec3(-1, -1, 1),    glm::vec3(-1.f, 0.f, 0.f),  glm::vec3(0.f, 1.f, 0.f)
};

const unsigned int indices [] =
{
    // front
    0, 1, 3, 3, 1, 2,
    // right
    1, 5, 2, 2, 5, 6,
    // back
    5, 4, 6, 6, 4, 7,
    // left
    4, 0, 7, 7, 0, 3,
    // top
    3, 2, 7, 7, 2, 6,
    // bottom
    4, 5, 0, 0, 5, 1
};

int main ()
{
    // OpenGL Loading
    OpenGLLoader openGLLoader(WIDTH, HEIGHT, "OpenGL");
    
    if (!openGLLoader.LoadingSuccessful())
    {
        std::cerr << openGLLoader.GetErrorMessage() << std::endl;
        return EXIT_FAILURE;
    }
    
    // Shader
    Shader shader("Resources/Shaders/shader.vert", "Resources/Shaders/shader.frag");
    
    if (!shader.CompilationWasSuccessful())
    {
        std::cerr << "Failed to load shaders" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // TEXTURES
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("Resources/Textures/container.jpg", &width, &height, &nrChannels, 0);
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    
    stbi_image_free(data);
    
    
    shader.Select(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shader.GetShaderID(), "texture1"), 0);
    
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    unsigned int projLoc  = glGetUniformLocation(shader.GetShaderID(), "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    Input input(openGLLoader.Display.GetWindow());
    WorldObject cameraObject(glm::vec3(0.0f, 0.0f, 3.0f));
    Camera camera (10, 0.1f);
    cameraObject.AttachComponent(&camera);
    
    WorldObject cubeObject(glm::vec3(5, 0, 5));
    std::vector<Vertex> v(Cube, Cube + sizeof(Cube) / sizeof(Cube[0]));

    std::vector<unsigned int> i(indices, indices + sizeof indices / sizeof indices[0]);
    Mesh mesh(v,i);
    cubeObject.AttachComponent(&mesh);
    
    
    // Main loop
    while(!openGLLoader.Display.ShouldClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(openGLLoader.Display.GetWindow());
        
        input.Update();
        cameraObject.Update(deltaTime);
        
        openGLLoader.Display.Clear();
        
        shader.Select();
        
        glm::mat4 view          = camera.GetViewMatrix();
        unsigned int viewLoc  = glGetUniformLocation(shader.GetShaderID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(5,0,0));
        glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), "model"), 1, GL_FALSE, &model[0][0]);

        mesh.Draw(shader, texture);
        
        openGLLoader.Display.Render();
        openGLLoader.Display.Update();
    }
    
    return EXIT_SUCCESS;
}

/// Processes User Input
void processInput (GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}
