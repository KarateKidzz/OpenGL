//
//  Loader.h
//  OpenGL
//
//  Created by James Kelly on 29/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Loader_h
#define Loader_h

#include <string>

/// Provides basic variables for checking if a class successfully loaded its data and returns an error message if it failed
struct Loader
{
    const bool& Successful;
    const std::string& ErrorMessage;
    
    Loader() :
    Successful(success),
    ErrorMessage(errorMessage)
    {
        
    }
    
protected:
    bool success;
    std::string errorMessage;
};

#endif /* Loader_h */
