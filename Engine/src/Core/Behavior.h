#pragma once

#include "Core.h"
#include "Component.h"

namespace AsquiEngine
{

class Engine;
class GameObject;
class Transform;

class Behavior : public Component
{
public:
    Behavior() {}
    
    WeakRef<GameObject> GetGameObject()
    {
        return gameObject;
    }
    
    WeakRef<Transform> GetTransform();
    
private:
    WeakRef<GameObject> gameObject;

    friend class Engine;
};

}
