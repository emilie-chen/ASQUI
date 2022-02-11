#include "Scene.h"

namespace AsquiEngine
{
void Scene::OnLoad()
{
    // awake all, then start all
}

void Scene::OnUnload()
{
    
}

void Scene::AddGameObject(Ref<GameObject> object)
{
    m_AllSceneGameObjects.insert(object);
}

void Scene::RemoveGameObject(Ref<GameObject> object)
{
    m_AllSceneGameObjects.erase(object);
}
}
