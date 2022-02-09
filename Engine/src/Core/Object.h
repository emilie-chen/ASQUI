#pragma once

#include "Core.h"

namespace AsquiEngine
{

class Engine;

class Object
{
public:
    Object() {}
    
    virtual ~Object() = default;

    template <typename T, typename ... Args>
    static Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    
    template <typename T, typename ... Args>
    static Unique<T> CreateUnique(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
protected:
    Engine* m_Engine;
    inline static Engine* engine;
    
private:
    static void Init(Engine* engineInstance)
    {
        engine = engineInstance;
    }
    
    friend class Engine;
};

}
