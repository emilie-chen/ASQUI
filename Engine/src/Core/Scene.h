#pragma once

#include "Core.h"
#include "Object.h"

namespace AsquiEngine
{

class Engine;
class GameObject;

class Scene : public Object
{
public:
    
private:
    void AddGameObject(Ref<GameObject>);
    void RemoveGameObject(Ref<GameObject>);
    
    Set<Ref<GameObject>> m_AllSceneGameObjects;
    
    friend class Engine;
    friend class EntityManager;
};

}
