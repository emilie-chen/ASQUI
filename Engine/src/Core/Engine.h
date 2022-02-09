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

class EntityManager : public Object
{
public:
    EntityManager() {}
    
private:
    Ref<GameObject> NewGameObject();
    void QueueDestroyGameObject(Ref<GameObject>);
    void OnUpdate();
    
    Set<Ref<GameObject>> m_AllGameObjects;
    Queue<Ref<GameObject>> m_GameObjectsToDestroyNextFrame;
    
    friend class Engine;
};

class Engine final : public Object
{
public:
    Engine();
    void Start();
    void OnUpdate();
    void Stop();
    void WaitFor();
    
    Ref<GameObject> NewGameObject();
    void DestroyGameObject(Ref<GameObject>);
    Scene* GetActiveScene();
private:
    std::atomic_bool m_ShouldStop;
    std::mutex m_Mutex;
    std::thread m_MainThread;
    std::condition_variable m_StopCondition;
    
    Unique<EntityManager> m_EntityManager;
    Unique<Scene> m_ActiveScene;
    
};

}
