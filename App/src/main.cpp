#include <iostream>
#include <glm/glm.hpp>
#include "AsquiEngine.h"

using namespace AsquiEngine;

int main()
{
    Engine engine;
    {
        WeakRef<GameObject> obj = engine.NewGameObject();
        using_weak_ref(obj)
        {
            info(_obj->ToString());
            auto transform = engine.GetComponent<Transform>(_obj);
            using_weak_ref(transform)
            {
                print(_transform->ToString());
            }
            
            engine.DestroyGameObject(_obj);
        }
        
    }
    engine.Start();
    engine.WaitFor();
    
    return 0;
}
