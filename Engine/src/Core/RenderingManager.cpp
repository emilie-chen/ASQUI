#include "RenderingManager.h"
#include <iostream>

namespace AsquiEngine
{

RenderingManager::RenderingManager() :
    m_Width(20), m_Height(20)
{
    m_Buffer.resize(m_Width);
    for (size_t x = 0; x < m_Width; x++)
    {
        m_Buffer[x].resize(m_Height);
    }
    
    for (size_t x = 0; x < m_Width; x++)
    {
        for (size_t y = 0; y < m_Height; y++)
        {
            m_Buffer[x][y] = std::make_tuple(' ', Code::BG_RED);
        }
    }
}

void RenderingManager::OnUpdate()
{
    std::stringstream ss;
    for (size_t x = 0; x < m_Width; x++)
    {
        for (size_t y = 0; y < m_Height; y++)
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
