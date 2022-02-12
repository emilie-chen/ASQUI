#pragma once

#include "Core.h"
#include "Object.h"

namespace AsquiEngine
{

class Component;

class RenderingManager : public Object
{
public:
    enum Code
    {
        BG_BLACK = 40,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_MAGENTA = 45,
        BG_CYAN = 46,
        BG_WHITE = 47,
        BG_DEFAULT = 49
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
    void OnUpdate(Map<Ref<GameObject>, Map<std::type_index, Ref<Component>>>& gameObjects);
    void DrawPixel(WeakRef<GameObject> gameObject, int x, int y, Code color);
    
private:
    void InitBufferWith(size_t width, size_t height);
    
private:
    int m_Width, m_Height;
    List<List<Tuple<char, Code>>> m_Buffer;
};

}
