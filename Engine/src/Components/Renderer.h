#pragma once

#include "../Core/Component.h"

namespace AsquiEngine
{
class RenderingManager;

class Renderer : public Component
{
public:
    virtual void Render(RenderingManager* rm) = 0;
};

}
