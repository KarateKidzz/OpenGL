//
//  Model.hpp
//  OpenGL
//
//  Created by James Kelly on 29/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Utilities/Loader.h"

class Shader;
class Mesh;
class MeshTexture;

class Model : public Loader
{
public:
    Model (std::string& path);
    void Draw(Shader& shader);

    std::vector<Mesh> meshes;
    
private:
    
    std::string directory;
    
    void LoadModel(std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif /* Model_hpp */
