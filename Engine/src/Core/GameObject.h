#pragma once

#include "Core.h"
#include "Object.h"
#include "../Components/Transform.h"

namespace AsquiEngine
{

class GameObject final : public Object
{
public:
    EntityId GetId() const { return m_Id; }
    
    Transform GetTransform() const;
    
private:
    GameObject() : m_Id(Id::New()) {}
    static Ref<GameObject> New();
    
private:
    EntityId m_Id;
    
    friend class Engine;
    friend class EntityManager;
    friend class Object;
};

}
