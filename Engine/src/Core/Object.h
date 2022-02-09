#pragma once

#include "Core.h"

namespace AsquiEngine
{

class Object
{
public:
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
};

}
