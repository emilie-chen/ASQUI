#pragma once

#include "Core.h"
#include "Component.h"
#include "Engine.h"

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
    
    template <typename T>
    typename std::enable_if<std::is_base_of<Component, T>::value, WeakRef<T>>::type GetComponent()
    {
        using_weak_ref(gameObject)
        {
            return engine->GetComponent<T>(_gameObject);
        }
    }
    
    virtual void Start() {}
    virtual void OnUpdate() {}
    
private:
    friend class Engine;
};

}
