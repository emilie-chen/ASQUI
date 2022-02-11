#include <iostream>
#include <glm/glm.hpp>
#include "AsquiEngine.h"

using namespace AsquiEngine;

int main()
{
    panic();
    Engine engine;
    {
        auto obj = engine.NewGameObject();
        engine.DestroyGameObject(obj);
    }
    engine.Start();
    engine.WaitFor();
    
    return 0;
}
