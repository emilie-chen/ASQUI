#pragma once

#include "Core.h"
#include "Object.h"

#include <mutex>
#include <thread>
#include <condition_variable>

namespace AsquiEngine
{

class GameObject;
class Scene;
class Component;

class EntityManager : public Object
{
public:
    EntityManager() {}
    
private:
    Ref<GameObject> NewGameObject();
    
    void QueueDestroyGameObject(Ref<GameObject>);
    void OnUpdate();
    
    Map<Ref<GameObject>, Map<std::type_index, Ref<Component>>> m_AllGameObjects;
    Queue<Ref<GameObject>> m_GameObjectsToDestroyNextFrame;
    
    template <typename T>
    WeakRef<T> GetComponent(Ref<GameObject> gameObject)
    {
        return std::static_pointer_cast<T>(m_AllGameObjects[gameObject][typeid(T)]);
    }
    
    template <typename T>
    WeakRef<T> AddComponent(Ref<GameObject> gameObject)
    {
        auto& components = m_AllGameObjects[gameObject];
        if (!components.contains(typeid(T)))
        {
            auto newComponent = CreateRef<T>();
            newComponent->gameObject = gameObject;
            m_AllGameObjects[gameObject][typeid(T)] = newComponent;
        }
        
        return std::static_pointer_cast<T>(components[typeid(T)]);
    }
    
    friend class Engine;
};

class Engine final : public Object
{
public:
    Engine();
    void Start();
    void Stop(int exitCode = 0);
    void WaitFor();
    
    Ref<GameObject> NewGameObject();
    void DestroyGameObject(Ref<GameObject>);
    Scene* GetActiveScene();
    
    template <typename T>
    WeakRef<T> GetComponent(Ref<GameObject> gameObject)
    {
        return m_EntityManager->GetComponent<T>(gameObject);
    }
    
    template <typename T>
    WeakRef<T> AddComponent(Ref<GameObject> gameObject)
    {
        return m_EntityManager->AddComponent<T>(gameObject);
    }
    
private:
    void OnUpdate();
    
private:
    std::atomic_bool m_ShouldStop;
    std::mutex m_Mutex;
    std::thread m_MainThread;
    std::condition_variable m_StopCondition;
    std::atomic_int m_ExitCode;
    
    UniqueRef<EntityManager> m_EntityManager;
    UniqueRef<Scene> m_ActiveScene;
    
};

}
