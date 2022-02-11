#include <iostream>
#include <glm/glm.hpp>
#include "AsquiEngine.h"

using namespace AsquiEngine;

int main()
{
    Engine engine;
    {
        auto obj = engine.NewGameObject();
        info(obj->ToString());
        auto transform = engine.GetComponent<Transform>(obj);
        using_weak_ref(transform)
        {
            print(_transform->ToString());
        }
        
        engine.DestroyGameObject(obj);
    }
    engine.Start();
    engine.WaitFor();
    
    return 0;
}
