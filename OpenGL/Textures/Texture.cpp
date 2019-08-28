//
//  Texture.cpp
//  OpenGL
//
//  Created by James Kelly on 27/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "Texture.hpp"

#include "stb_image.h"

Texture::Texture(const char *file) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(file, &width, &height, &numChannels, 0);
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, numChannels == 3 ? GL_RGB : GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        success = true;
    }
    else
    {
        success = false;
    }
    
    stbi_image_free(data);
}

const GLuint Texture::GetID() const { 
    return ID;
}

const bool Texture::Successful() const
{
    return success;
}
