//
//  Mesh.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(std::vector<Vertex> &verticies, std::vector<unsigned int> &indicies) :
Verticies(verticies),
Indices(indicies)
{
    SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> &verticies, std::vector<unsigned int> &indicies, std::vector<MeshTexture> &textures) :
Verticies(verticies),
Indices(indicies),
Textures(textures)
{
    SetupMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::SetupMesh() {
    /*
        VBO - Vertex Buffer Object
     : stores vertex data
     
        VAO - Vertex Array Object
     : stores buffer and vertex info
     
        EBO - Element Buffer Object
     : stores indicies to eliminate rendering the same vertex twice (or more)
     
    */
    
    // Creates the objects used in rendering
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind objects
    // OpenGL works like a state machine so we set the state and make changes to it
    // The state can then change again when we're doing something else
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Fills the buffer with data
    // The buffer is bound so this call will affect it
    // Because it's bound, we don't need to reference it
    glBufferData(GL_ARRAY_BUFFER, Verticies.size() * sizeof(Vertex), &Verticies[0], GL_STATIC_DRAW);
    
    // Bind the EBO (select) and fill its buffer with data. In this case the indicies
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);
    
    // Tell OpenGL how to read our buffer data (what each element means)
    
    // Vertex positions
    glEnableVertexAttribArray(0);
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    // Vertex normals
    glEnableVertexAttribArray(1);
    glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    // Vertex texture coordinates
    glEnableVertexAttribArray(2);
    glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
    
    glBindVertexArray(0);
}

void Mesh::Draw(const Shader &shader) const
{
    shader.Select();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Transform->Position);
    model = glm::rotate(model, glm::radians(Transform->Rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(Transform->Rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(Transform->Rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, Transform->Scale);
    glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), "model"), 1, GL_FALSE, &model[0][0]);
    
    for (MeshTexture mt : Textures)
    {
        glActiveTexture(GL_TEXTURE0 + mt.TextureUnit);
        glBindTexture(GL_TEXTURE_2D, mt.TextureID);
    }
    
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, tex);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<int>(Indices.size()) , GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(0);
    
    shader.Deselect();
}



