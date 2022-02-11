#pragma once

#include "Core.h"

namespace AsquiEngine
{

class Engine;
class GameObject;

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
    static UniqueRef<T> CreateUniqueRef(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    virtual String ToString() const;
    int64_t GetInstanceID() const;
    static void Destroy(Ref<GameObject> object);
    
    
protected:
    inline static Engine* engine;
    
private:
    static void Init(Engine* engineInstance)
    {
        engine = engineInstance;
    }
    
    friend class Engine;
};

}
