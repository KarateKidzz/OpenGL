//
//  Texture.hpp
//  OpenGL
//
//  Created by James Kelly on 27/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#define STB_IMAGE_IMPLEMENTATION


#include <glad/glad.h>



class Texture
{
public:
    Texture(const char* file);
    const GLuint GetID () const;
    const bool Successful () const;
    
private:
    bool success;
    GLuint ID;
    int width, height, numChannels;
};

#endif /* Texture_hpp */
