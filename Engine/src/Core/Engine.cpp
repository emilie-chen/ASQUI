#include "Engine.h"
#include "GameObject.h"
#include "Scene.h"

#include <thread>

namespace AsquiEngine
{
Ref<GameObject> EntityManager::NewGameObject()
{
    auto obj = GameObject::New();
    m_AllGameObjects.insert(obj);
    return obj;
}

void EntityManager::QueueDestroyGameObject(Ref<GameObject> gameObject)
{
    nonnull(gameObject);
    m_GameObjectsToDestroyNextFrame.push(gameObject);
}

void EntityManager::OnUpdate()
{
    // destroy all game objects that were queued
    // engien will first ensure that the active scene does not contain any game objects that need to be deleted
    
    auto activeScene = engine->GetActiveScene();
    while (!m_GameObjectsToDestroyNextFrame.empty())
    {
        auto objectToDestroy = m_GameObjectsToDestroyNextFrame.front();
        m_GameObjectsToDestroyNextFrame.pop();
        
        if (objectToDestroy.use_count() > 1)
        {
            // used elsewhere
            if (activeScene)
            {
                // try removing from scene
                auto& allSceneGameObjects = activeScene->m_AllSceneGameObjects;
                if (allSceneGameObjects.find(objectToDestroy) != allSceneGameObjects.end())
                {
                    // remove
                    allSceneGameObjects.erase(objectToDestroy);
                }
            }
            
            if (objectToDestroy.use_count() > 1)
            {
                std::cerr << "WARNING : GameObject { ID = " << objectToDestroy->GetId() << " } is still in use when being requested to be destroyed";
            }
        }
    }
}

Engine::Engine() :
    m_EntityManager(CreateUnique<EntityManager>())
{
    Object::Init(this);

    // default scene
    m_ActiveScene = CreateUnique<Scene>();
}

void Engine::Start()
{
    m_ShouldStop = false;
    m_MainThread = std::thread([this]
    {
        while (!m_ShouldStop)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            OnUpdate();
        }
        {
            m_StopCondition.notify_all();
        }
    });
    m_MainThread.detach();
}

void Engine::OnUpdate()
{
    static size_t counter = 0;
    std::cout << counter++ << std::endl;;
    std::cout.flush();
    
    if (counter > 1000)
    {
        Stop();
    }
}

void Engine::Stop()
{
    m_ShouldStop = true;
}

void Engine::WaitFor()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_StopCondition.wait(lock, [this]{ return m_ShouldStop.load(); });
}

Ref<GameObject> Engine::NewGameObject()
{
    Ref<GameObject> gameObject = m_EntityManager->NewGameObject();
    nonnull(gameObject);
    nonnull(m_ActiveScene);
    m_ActiveScene->AddGameObject(gameObject);
    return gameObject;
}

void Engine::DestroyGameObject(Ref<GameObject> gameObject)
{
    nonnull(gameObject);
}

Scene* Engine::GetActiveScene()
{
    return m_ActiveScene.get();
}
}
