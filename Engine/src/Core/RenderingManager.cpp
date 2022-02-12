#include "RenderingManager.h"
#include "../Platform/NativeInput.h"
#include "Engine.h"
#include "Component.h"
#include "GameObject.h"
#include "../Components/Renderer.h"
#include "../Components/Transform.h"
#include <iostream>

namespace AsquiEngine
{

RenderingManager::RenderingManager()
{
    auto size = Platform::GetConsoleDimensions();
    m_Width = size.x;
    m_Height = size.y;
    
    InitBufferWith(size.x, size.y);
    
    engine->m_NativeInputManager->AddConsoleDimensionChangedListener(
        [this](const auto& newDim)
        {
            // reinitialize buffer
            InitBufferWith(newDim.x, newDim.y);
        });
}

void RenderingManager::InitBufferWith(size_t width, size_t height)
{
    m_Width = width;
    m_Height = height;
    m_Buffer.resize(m_Width);
    for (size_t x = 0; x < m_Width; x++)
    {
        m_Buffer[x].resize(m_Height);
    }
    
    for (size_t x = 0; x < m_Width; x++)
    {
        for (size_t y = 0; y < m_Height; y++)
        {
            m_Buffer[x][y] = std::make_tuple(' ', Code::BG_DEFAULT);
        }
    }
}

void RenderingManager::OnUpdate(Map<Ref<GameObject>, Map<std::type_index, Ref<Component>>>& gameObjects)
{
    {
        for (size_t x = 0; x < m_Width; x++)
        {
            for (size_t y = 0; y < m_Height; y++)
            {
                m_Buffer[x][y] = std::make_tuple(' ', Code::BG_DEFAULT);
            }
        }
    }

    for (auto& [_, components] : gameObjects)
    {
        for (auto& [_, component] : components)
        {
            auto componentAsRenderer = std::dynamic_pointer_cast<Renderer>(component);
            if (componentAsRenderer)
            {
                componentAsRenderer->Render(this);
            }
        }
    }
    
    std::stringstream ss;
    for (size_t y = 0; y < m_Height; y++)
    {
        for (size_t x = 0; x < m_Width; x++)
        {
            auto& [c, color] = m_Buffer[x][y];
            ss << Modifier(color);
            ss << c;
        }
    }
    system("clear");
    std::cout << ss.str();
    std::cout.flush();
}

void RenderingManager::DrawPixel(WeakRef<GameObject> gameObject, int x, int y, Code color)
{
    using_weak_ref(gameObject)
    {
        const auto transform = engine->GetComponent<Transform>(_gameObject);
        using_weak_ref(transform)
        {
            const auto position = _transform->GetPosition();
            int targetX = position.x + x;
            int targetY = position.y + y;
            if (targetX >= m_Width || targetX < 0 || targetY >= m_Height || targetY < 0)
                return;
            m_Buffer[targetX][targetY] = std::make_tuple(' ', color);
        }
    }
}

}
