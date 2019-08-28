//
//  Mesh.hpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glad/glad.h>
#include <string>
#include <vector>
#include "../Objects/Component.hpp"
#include "../Shaders/Shader.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

struct MeshTexture
{
    unsigned int TextureUnit;
    unsigned int TextureID;
    
    MeshTexture(unsigned int textureUnit, unsigned int textureID)
    {
        TextureUnit = textureUnit;
        TextureID = textureID;
    }
    
};

class Mesh : public Component
{
public:
    Mesh(std::vector<Vertex> &verticies, std::vector<unsigned int> &indicies);
    ~Mesh();
    
    std::vector<Vertex> Verticies;
    std::vector<unsigned int> Indices;
    std::vector<MeshTexture> Textures;
    
    void Draw (const Shader& shader, const int tex);
    
private:
    unsigned int VAO, VBO, EBO;
    void SetupMesh();
};

#endif /* Mesh_hpp */
