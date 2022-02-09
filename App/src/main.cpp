#include <iostream>
#include "Document.h"
#include <glm/glm.hpp>
#include "AsquiEngine.h"

using namespace AsquiEngine;

int main()
{
    Unique<Engine> engine = Object::CreateUnique<Engine>();
    
    // start up script for the engine, e.g., creating a scene, adding initial game objects before engine starts
    auto gameObject = engine->NewGameObject();
    
    engine->Start();
    engine->WaitFor();
    
    return 0;
}
