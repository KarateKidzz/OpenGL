//
//  Model.cpp
//  OpenGL
//
//  Created by James Kelly on 29/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Model.hpp"
#include "Mesh.hpp"
#include "../Shaders/Shader.hpp"
#include <glm/vec3.hpp>

Model::Model(std::string &path)
{
    LoadModel(path);
}

void Model::Draw(Shader &shader) { 
    for (const Mesh& mesh : meshes)
    {
        mesh.Draw(shader);
    }
}

void Model::LoadModel(std::string &path) {
    
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        success = false;
        errorMessage = importer.GetErrorString();
        return;
    }
    
    directory = path.substr(0, path.find_last_of('/'));
    
    ProcessNode(scene->mRootNode, scene);
    
    success = true;
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indicies;
    std::vector<MeshTexture> textures;
    
    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        
        vertex.Position = vector;
        
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoord = vec;
        }
        else
        vertex.TexCoord = glm::vec2(0.0f, 0.0f);
        
        vertices.push_back(vertex);
    }
    
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indicies.push_back(face.mIndices[j]);
    }
    
    if (mesh->mMaterialIndex >= 0)
    {
        
    }
    
    return Mesh(vertices, indicies, textures);
}

std::vector<MeshTexture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) { 
    return std::vector<MeshTexture>();
}


