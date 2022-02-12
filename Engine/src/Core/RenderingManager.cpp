#include "RenderingManager.h"
#include "../Platform/NativeInput.h"
#include <iostream>

namespace AsquiEngine
{

RenderingManager::RenderingManager()
{
    auto size = Platform::GetConsoleDimensions();
    m_Width = size.x;
    m_Height = size.y;
    m_Buffer.resize(m_Width);
    for (size_t x = 0; x < m_Width; x++)
    {
        m_Buffer[x].resize(m_Height);
    }
}

void RenderingManager::OnUpdate()
{
    {
        static int counter;
        for (size_t x = 0; x < m_Width; x++)
        {
            for (size_t y = 0; y < m_Height; y++)
            {
                m_Buffer[x][y] = std::make_tuple(' ', Code::BG_RED);
            }
        }
        std::get<1>(m_Buffer[counter / 3][5]) = Code::BG_BLUE;
        counter++;
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

}
