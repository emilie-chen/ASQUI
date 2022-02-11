#include <iostream>
#include <glm/glm.hpp>
#include "AsquiEngine.h"

using namespace AsquiEngine;

int main()
{
    Engine engine;
    {
        auto obj = engine.NewGameObject();
        fmt::print(obj->ToString());
        engine.DestroyGameObject(obj);
    }
    engine.Start();
    engine.WaitFor();
    
    return 0;
}
