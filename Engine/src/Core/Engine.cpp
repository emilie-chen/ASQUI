#include "Engine.h"
#include "GameObject.h"
#include "Scene.h"
#include "Component.h"
#include "Application.h"
#include "../Components/Transform.h"

#include <thread>

namespace AsquiEngine
{
Ref<GameObject> EntityManager::NewGameObject()
{
    auto obj = GameObject::New();
    m_AllGameObjects[obj][typeid(Transform)] = CreateRef<Transform>();
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
    // update all scene objects
    for (auto& [_, components] : m_AllGameObjects)
    {
        for (auto& [_, component] : components)
        {
            component->OnUpdate();
        }
    }
    
    while (!m_GameObjectsToDestroyNextFrame.empty())
    {
        auto objectToDestroy = m_GameObjectsToDestroyNextFrame.front();
        m_GameObjectsToDestroyNextFrame.pop();
        
        m_AllGameObjects.erase(objectToDestroy);
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
                spdlog::warn("GameObject {{ ID = {} }} is still in use when being requested to be destroyed", objectToDestroy->GetInstanceID());
                delete objectToDestroy.get();
            }
        }
    }
}

Engine::Engine() :
    m_EntityManager(CreateUniqueRef<EntityManager>())
{
    Object::Init(this);
    Application::Init(this);
    // default scene
    m_ActiveScene = CreateUniqueRef<Scene>();
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
    m_EntityManager->OnUpdate();
}

void Engine::Stop(int exitCode)
{
    m_ShouldStop = true;
    m_ExitCode = exitCode;
}

void Engine::WaitFor()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_StopCondition.wait(lock, [this]{ return m_ShouldStop.load(); });
    exit(m_ExitCode.load());
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
    m_EntityManager->QueueDestroyGameObject(gameObject);
}

Scene* Engine::GetActiveScene()
{
    return m_ActiveScene.get();
}
}
