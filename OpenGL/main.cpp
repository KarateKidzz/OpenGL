#include <iostream>
#include <string>
#include <memory>
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
    Texture diffuseTexture("Resources/Textures/container2.png");
    
    if (!diffuseTexture.Successful())
    {
        std::cerr << "Failed to load texture" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    Texture specularTexture("Resources/Textures/container2_specular.png");
    
    if (!specularTexture.Successful())
    {
        std::cerr << "Failed to load texture" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    Input input(openGLLoader.Display.GetWindow());
    
    WorldObject cameraObject(glm::vec3(0.0f, 0.0f, -5.f), glm::vec3(0,180,0));
    Camera camera (10, 0.1f);
    cameraObject.AttachComponent(&camera);
    
    std::vector<Vertex> v(Cube, Cube + sizeof(Cube) / sizeof(Cube[0]));
    std::vector<unsigned int> i(indices, indices + sizeof indices / sizeof indices[0]);
    
    MeshTexture diffuse(0,diffuseTexture.GetID());
    MeshTexture spec(1, specularTexture.GetID());
    
    WorldObject lightOne(glm::vec3(3, 0, -3));
    WorldObject lightTwo(glm::vec3(6, 10.0f, 10));
    WorldObject lightThree(glm::vec3(16, 17, 10));
    WorldObject lightFour(glm::vec3(20, 22, 20));
    
    Mesh meshOne(v,i);
    
    meshOne.Textures.push_back(diffuse);
    meshOne.Textures.push_back(spec);
    
    Mesh meshTwo(v,i);
    
    meshTwo.Textures.push_back(diffuse);
    meshTwo.Textures.push_back(spec);
    
    Mesh meshThree(v,i);
    
    meshThree.Textures.push_back(diffuse);
    meshThree.Textures.push_back(spec);
    
    Mesh meshFour(v,i);
    
    meshFour.Textures.push_back(diffuse);
    meshFour.Textures.push_back(spec);
    
    lightOne.AttachComponent(&meshOne);
    lightTwo.AttachComponent(&meshTwo);
    lightThree.AttachComponent(&meshThree);
    lightFour.AttachComponent(&meshFour);
    
                         
    
    shader.Select();
    
    // set material properties
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);
    shader.setFloat("material.shininess", 64.0f);
    
    // set directional light properties
    shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    shader.setVec3("dirLight.ambient",  0.2f, 0.2f, 0.2f);
    shader.setVec3("dirLight.diffuse",  0.5f, 0.5f, 0.5f);
    shader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
    
    //point lights
    shader.setVec3("pointLights[0].position", lightOne.Transform.Position);
    shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.09);
    shader.setFloat("pointLights[0].quadratic", 0.032);
    
    shader.setVec3("pointLights[1].position", lightTwo.Transform.Position);
    shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    shader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[1].constant", 1.0f);
    shader.setFloat("pointLights[1].linear", 0.09);
    shader.setFloat("pointLights[1].quadratic", 0.032);
    
    shader.setVec3("pointLights[2].position", lightThree.Transform.Position);
    shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[2].constant", 1.0f);
    shader.setFloat("pointLights[2].linear", 0.09);
    shader.setFloat("pointLights[2].quadratic", 0.032);
    
    shader.setVec3("pointLights[3].position", lightFour.Transform.Position);
    shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[3].constant", 1.0f);
    shader.setFloat("pointLights[3].linear", 0.09);
    shader.setFloat("pointLights[3].quadratic", 0.032);
    
    // spotLight
    shader.setVec3("spotLight.position", cameraObject.Transform.Position);
    shader.setVec3("spotLight.direction", cameraObject.Transform.Forward);
    shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("spotLight.constant", 1.0f);
    shader.setFloat("spotLight.linear", 0.09);
    shader.setFloat("spotLight.quadratic", 0.032);
    shader.setFloat("spotLight.cutoff", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLight.outerCutoff", glm::cos(glm::radians(15.0f)));
    
    
    
    
    
    camera.AddShader(&shader);
    camera.AddShader(&lightShader);
    
    
    
    
    DebugInput db;
    cameraObject.AttachComponent(&db);
    
    std::vector<std::unique_ptr<WorldObject*>> cubes;
    std::vector<std::unique_ptr<Mesh*>> meshes;
    
    for(int index = 0; index < 10; index++)
    {
        WorldObject* w = new WorldObject(glm::vec3(index*2,index*2,index*2));
        Mesh* m = new Mesh(v,i);
        w->AttachComponent(m);
        
        m->Textures.push_back(diffuse);
        m->Textures.push_back(spec);
        
        cubes.push_back(std::make_unique<WorldObject*>(w));
        meshes.push_back(std::make_unique<Mesh*>(m));
    }
    
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
        shader.setVec3("spotLight.position", cameraObject.Transform.Position);
        shader.setVec3("spotLight.direction", cameraObject.Transform.Forward);
        shader.setVec3("viewPos", cameraObject.Transform.Position);

       
        
        for (std::unique_ptr<Mesh*>& m : meshes)
        {
            Mesh* meshPointer = *m;
            meshPointer->Draw(shader);
            
        }
        
        meshOne.Draw(lightShader);
        meshTwo.Draw(lightShader);
        meshThree.Draw(lightShader);
        meshFour.Draw(lightShader);
        
        openGLLoader.Display.Render();
        openGLLoader.Display.Update();
    }
    
    return EXIT_SUCCESS;
}
