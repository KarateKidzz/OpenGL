//
//  Component.hpp
//  OpenGL
//
//  Created by James Kelly on 26/08/2019.
//  Copyright © 2019 James Kelly. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

class WorldObject;

/// A class that can be attached to a WorldObject to provide functionality
class Component
{
    friend class WorldObject;
    
public:
    Component();
    Component(WorldObject* worldObject);
    WorldObject& GetWorldObject () const;
    
protected:
    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update() {}
    
    // owning object of this component
    class WorldObject* worldObject;
    
private:
    /// Sets this component's WorldObject. Automatically calls Start()
    void AssignWorldObject (WorldObject* worldObject);
    
};

#endif /* Component_hpp */
