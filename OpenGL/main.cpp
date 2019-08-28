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
    
    
    shader.Select();
    
    // set material properties
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);
    shader.setFloat("material.shininess", 64.0f);
    
    // set light properties
    shader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
    shader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // darken the light a bit to fit the scene
    shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    
    shader.setFloat("light.constant",  1.0f);
    shader.setFloat("light.linear",    0.09f);
    shader.setFloat("light.quadratic", 0.032f);
    
    shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
    
    Input input(openGLLoader.Display.GetWindow());
    
    WorldObject cameraObject(glm::vec3(0.0f, 0.0f, -5.f), glm::vec3(0,180,0));
    Camera camera (10, 0.1f);
    cameraObject.AttachComponent(&camera);
    
    camera.AddShader(&shader);
    camera.AddShader(&lightShader);
    
    WorldObject cubeObject(glm::vec3(0, 0, 5));
    std::vector<Vertex> v(Cube, Cube + sizeof(Cube) / sizeof(Cube[0]));
    std::vector<unsigned int> i(indices, indices + sizeof indices / sizeof indices[0]);
    
    Mesh mesh(v,i);
    cubeObject.AttachComponent(&mesh);
    
    WorldObject secondCubeObject(glm::vec3(5, 2, 0), glm::vec3(0, -45, 0), glm::vec3(.5f,.5f,.5f));
    Mesh secondMesh(v,i);
    secondCubeObject.AttachComponent(&secondMesh);
    
    MeshTexture diffuse(0,diffuseTexture.GetID());
    MeshTexture spec(1, specularTexture.GetID());
    
    mesh.Textures.push_back(diffuse);
    mesh.Textures.push_back(spec);
    
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
        
        if (Input::GetKeyDown(GLFW_KEY_Z))
        {
            secondCubeObject.Transform.Rotation.y += 25 * deltaTime;
            if (secondCubeObject.Transform.Rotation.y > 360)
                secondCubeObject.Transform.Rotation.y = 0;
        }
        
        shader.Select();
        shader.setVec3("light.position", secondCubeObject.Transform.Position);
        shader.setVec3("light.direction", glm::radians(secondCubeObject.Transform.Rotation));
        shader.setVec3("viewPos", cameraObject.Transform.Position);

        mesh.Draw(shader);

        secondMesh.Draw(lightShader);
        
        for (std::unique_ptr<Mesh*>& m : meshes)
        {
            Mesh* meshPointer = *m;
            meshPointer->Draw(shader);
            
        }
        
        openGLLoader.Display.Render();
        openGLLoader.Display.Update();
    }
    
    return EXIT_SUCCESS;
}
