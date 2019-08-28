#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Windows/Display.hpp"
#include "Shaders/Shader.hpp"
#include "Application/OpenGLLoader.hpp"
#include "Application/Input.hpp"
#include "Camera/Camera.hpp"
#include "Rendering/Mesh.hpp"
#include "Textures/Texture.hpp"
#include "Components/DebugInput.hpp"


/*
 For my future self:
 
 glad.h is the OpenGL Loading Library. Through this library we point to OpenGL functions.
 
 glfw3.h is an API for creating windows and handling user input.
 
 */

const GLint WIDTH = 800, HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const Vertex Cube [] =
{
    // Positions            // Normals                  // Texture Coordinates
    
    // Front
    glm::vec3(-1, -1, -1),  glm::vec3(0.f, 0.f, -1.f),   glm::vec2(0.f, 0.f),
    glm::vec3(1, -1, -1),   glm::vec3(0.f, 0.f, -1.f),   glm::vec2(1.f, 0.f),
    glm::vec3(1, 1, -1),    glm::vec3(0.f, 0.f, -1.f),   glm::vec2(1.f, 1.f),
    glm::vec3(-1, 1, -1),   glm::vec3(0.f, 0.f, -1.f),   glm::vec2(0.f, 1.f),
    
    // Right
    glm::vec3(1, -1, -1),   glm::vec3(1.f, 0.f, 0.f),  glm::vec2(0.f, 0.f),
    glm::vec3(1, -1, 1),    glm::vec3(1.f, 0.f, 0.f),  glm::vec2(1.f, 0.f),
    glm::vec3(1, 1, 1),     glm::vec3(1.f, 0.f, 0.f),  glm::vec2(1.f, 1.f),
    glm::vec3(1, 1, -1),    glm::vec3(1.f, 0.f, 0.f),  glm::vec2(0.f, 1.f),
    
    // Back
    glm::vec3(-1, -1, 1),   glm::vec3(0.f, 0.f, 1.f),  glm::vec2(1.f, 0.f),
    glm::vec3(-1, 1, 1),    glm::vec3(0.f, 0.f, 1.f),  glm::vec2(1.f, 1.f),
    glm::vec3(1, 1, 1),     glm::vec3(0.f, 0.f, 1.f),  glm::vec2(0.f, 1.f),
    glm::vec3(1, -1, 1),    glm::vec3(0.f, 0.f, 1.f),  glm::vec2(0.f, 0.f),
    
    // Left
    glm::vec3(-1, -1, 1),    glm::vec3(-1.f, 0.f, 0.f),  glm::vec2(0.f, 0.f),
    glm::vec3(-1, -1, -1),   glm::vec3(-1.f, 0.f, 0.f),  glm::vec2(1.f, 0.f),
    glm::vec3(-1, 1, -1),    glm::vec3(-1.f, 0.f, 0.f),  glm::vec2(1.f, 1.f),
    glm::vec3(-1, 1, 1),     glm::vec3(-1.f, 0.f, 0.f),  glm::vec2(0.f, 1.f),
    
    // Top
    glm::vec3(-1, 1, -1),   glm::vec3(0.f, 1.f, 0.f),  glm::vec2(1.f, 1.f),
    glm::vec3(1, 1, -1),    glm::vec3(0.f, 1.f, 0.f),  glm::vec2(0.f, 1.f),
    glm::vec3(1, 1, 1),     glm::vec3(0.f, 1.f, 0.f),  glm::vec2(0.f, 0.f),
    glm::vec3(-1, 1, 1),    glm::vec3(0.f, 1.f, 0.f),  glm::vec2(1.f, 0.f),
    
    // Bottom
    glm::vec3(-1, -1, -1),   glm::vec3(0.f, -1.f, 0.f),  glm::vec2(0.f, 0.f),
    glm::vec3(1, -1, -1),    glm::vec3(0.f, -1.f, 0.f),  glm::vec2(1.f, 0.f),
    glm::vec3(1, -1, 1),     glm::vec3(0.f, -1.f, 0.f),  glm::vec2(1.f, 1.f),
    glm::vec3(-1, -1, 1),    glm::vec3(0.f, -1.f, 0.f),  glm::vec2(0.f, 1.f)
};

const unsigned int indices [] =
{
    // front
    0, 1, 3, 3, 1, 2,
    // right
    4, 5, 6, 6, 7, 4,
    // back
    8, 9, 11, 11, 9, 10,
    // left
    12, 13, 15, 15, 13, 14,
    // top
    16, 17, 19, 19, 17, 18,
    // bottom
    20, 21, 23, 23, 21, 22
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
    
    Shader lightShader ("Resources/Shaders/light.vert", "Resources/Shaders/light.frag");
    
    if (!lightShader.CompilationWasSuccessful())
    {
        std::cerr << "Failed to load shaders" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // Texture
    Texture texture("Resources/Textures/container.jpg");
    
    if (!texture.Successful())
    {
        std::cerr << "Failed to load texture" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    
    shader.Select(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shader.GetShaderID(), "texture1"), 0);
    
    shader.setVec3("material.ambient",  0.2f, 0.2f, 0.2f);
    shader.setVec3("material.diffuse",  1.0f, 1.0f, 1.0f);
    shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    shader.setFloat("material.shininess", 32.0f);
    
    shader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
    shader.setVec3("light.diffuse",  0.9f, 0.9f, 0.9f); // darken the light a bit to fit the scene
    shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    
    Input input(openGLLoader.Display.GetWindow());
    
    WorldObject cameraObject(glm::vec3(0.0f, 0.0f, 0.f));
    Camera camera (10, 0.1f);
    cameraObject.AttachComponent(&camera);
    
    camera.AddShader(&shader);
    camera.AddShader(&lightShader);
    
    WorldObject cubeObject(glm::vec3(0, 0, 5));
    std::vector<Vertex> v(Cube, Cube + sizeof(Cube) / sizeof(Cube[0]));
    std::vector<unsigned int> i(indices, indices + sizeof indices / sizeof indices[0]);
    
    Mesh mesh(v,i);
    cubeObject.AttachComponent(&mesh);
    
    WorldObject secondCubeObject(glm::vec3(5, 2, 0), glm::vec3(25, 45.f, 0), glm::vec3(.5f,.5f,.5f));
    Mesh secondMesh(v,i);
    secondCubeObject.AttachComponent(&secondMesh);
    
    DebugInput db;
    cameraObject.AttachComponent(&db);
    
    // Main loop
    while(!openGLLoader.Display.ShouldClose())
    {
        // calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        openGLLoader.Display.Clear();
        
        input.Update();
        
        cameraObject.Update(deltaTime);
        
        shader.Select();
        shader.setVec3("light.position", cameraObject.Transform.Position);
        shader.setVec3("viewPos", cameraObject.Transform.Position);
        
        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);
        
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
        
        shader.setVec3("light.ambient", ambientColor);
        shader.setVec3("light.diffuse", diffuseColor);

        mesh.Draw(shader, texture.GetID());

        secondMesh.Draw(lightShader, texture.GetID());
        
        openGLLoader.Display.Render();
        openGLLoader.Display.Update();
    }
    
    return EXIT_SUCCESS;
}
