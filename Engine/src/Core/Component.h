#pragma once

#include "Core.h"
#include "Object.h"

namespace AsquiEngine
{

class Component : public Object
{
public:
    Component() {}
    
    virtual void Start() {}
    virtual void OnUpdate() {}
    
protected:
    WeakRef<GameObject> gameObject;
    
    friend class Engine;
    friend class EntityManager;
};

}
