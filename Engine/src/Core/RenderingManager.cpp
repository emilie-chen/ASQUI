#include "RenderingManager.h"
#include "../Platform/NativeInput.h"
#include "Engine.h"
#include "Component.h"
#include "../Components/Renderer.h"
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
//    {
//        static int counter;
//        for (size_t x = 0; x < m_Width; x++)
//        {
//            for (size_t y = 0; y < m_Height; y++)
//            {
//                m_Buffer[x][y] = std::make_tuple(' ', Code::BG_RED);
//            }
//        }
//        std::get<1>(m_Buffer[counter / 3][5]) = Code::BG_BLUE;
//        counter++;
//    }
//
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

void RenderingManager::DrawPixel(int x, int y, Code color)
{
    
}

}
