//
//  Component.hpp
//  OpenGL
//
//  Created by James Kelly on 26/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include "../Vectors/Transform.hpp"

class WorldObject;

/// A class that can be attached to a WorldObject to provide functionality
class Component
{
    friend class WorldObject;
    
public:
    Component();
    Component(WorldObject* worldObject);
    WorldObject& GetWorldObject () const;
    Transform* Transform;
    
protected:
    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update(const float& deltaTime) {}
    
    // owning object of this component
    class WorldObject* worldObject;
    
private:
    /// Sets this component's WorldObject. Automatically calls Start(). Call from WorlObject : Do Not Call From This Class
    void AssignWorldObject (WorldObject* worldObject);
    
};

#endif /* Component_hpp */
