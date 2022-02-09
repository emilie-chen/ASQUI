#include <iostream>
#include "Document.h"
#include <glm/glm.hpp>
#include "AsquiEngine.h"

using namespace AsquiEngine;

class MyComponent : public Object
{
public:
    MyComponent(int i)
    {
        std::cout << i << std::endl;
    }
};

int main()
{
    Ref<MyComponent> c = Object::CreateRef<MyComponent>(10);

    return 0;
}
