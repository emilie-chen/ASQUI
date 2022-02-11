#pragma once

#include "Core.h"

namespace AsquiEngine
{

class Engine;

class Application
{
public:
    Application() = delete;
    
    static void Quit(int exitCode = 0);
    
private:
    friend class Engine;
    
    static void Init(Engine* enginePtr);
    
    inline static Engine* engine;
};

}
