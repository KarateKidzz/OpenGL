//
//  DebugInput.hpp
//  OpenGL
//
//  Created by James Kelly on 27/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef DebugInput_hpp
#define DebugInput_hpp

#include "../Objects/Component.hpp"

class DebugInput : public Component
{
public:
    void Update(const float& deltaTime) override;
};

#endif /* DebugInput_hpp */
