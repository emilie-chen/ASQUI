#include "Application.h"
#include "Engine.h"

namespace AsquiEngine
{
void Application::Init(Engine* enginePtr)
{
    engine = enginePtr;
}

void Application::Quit(int exitCode)
{
    engine->Stop(exitCode);
}
}
