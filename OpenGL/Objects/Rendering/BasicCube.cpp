//
//  BasicCube.cpp
//  OpenGL
//
//  Created by James Kelly on 24/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#include "BasicCube.hpp"


BasicCube::BasicCube() :
shader("Resources/Shaders/shader.vert", "Resources/Shaders/shader.frag")
{
    if (shader.CompilationWasSuccessful())
    {
        
    }
}
