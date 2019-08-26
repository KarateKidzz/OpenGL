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
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../Objects/Component.hpp"
#include "../Shaders/Shader.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 TexCoord;
    
    inline Vertex(glm::vec3 pos)
    {
        Position = pos;
    }
};

struct Texture
{
    unsigned int id;
    std::string type;
    
    inline Texture(unsigned int id, std::string type)
    {
        this->id = id;
        this->type = type;
    }
};

class Mesh : public Component
{
public:
    Mesh(std::vector<Vertex> &verticies, std::vector<unsigned int> &indicies, std::vector<Texture>& textures);
    
    std::vector<Vertex> Verticies;
    std::vector<unsigned int> Indices;
    std::vector<Texture> Textures;
    
    void Draw (const Shader& shader, const int tex);
    
private:
    unsigned int VAO, VBO, EBO;
    void SetupMesh();
};

#endif /* Mesh_hpp */
