#pragma once

#include "Core.h"
#include "Object.h"

namespace AsquiEngine
{

class Component : public Object
{
public:
    Component() {}
    
protected:
    WeakRef<GameObject> gameObject;
    
    friend class Engine;
    friend class EntityManager;
};

}
