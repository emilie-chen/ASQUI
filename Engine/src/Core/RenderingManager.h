#pragma once

#include "Core.h"
#include "Object.h"

namespace AsquiEngine
{

class RenderingManager : public Object
{
public:
    enum Code
    {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    
    class Modifier
    {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream& operator<<(std::ostream& os, const Modifier& mod)
        {
            return os << "\033[" << mod.code << "m";
        }
    };
    
    RenderingManager();
    void OnUpdate();
    
private:
    int m_Width, m_Height;
    List<List<Tuple<char, Code>>> m_Buffer;
};

}
