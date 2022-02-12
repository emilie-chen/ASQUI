#include <iostream>
#include <glm/glm.hpp>
#include "AsquiEngine.h"

using namespace AsquiEngine;

class HugeComponent : public Behavior
{
private:
    int arr[100000];
};

class TestBehavior : public Behavior
{
private:
    int counter;
    
public:
    virtual void Start() override
    {
        print("I am starting");
        counter = 0;
    }
    
    virtual void OnUpdate() override
    {
        print(counter++);
        auto ref = engine->NewGameObject();
        engine->AddComponent<HugeComponent>(ref);
        engine->AddComponent<TestBehavior>(ref);
        Destroy(ref);
        if (counter > 100)
        {
            Application::Quit();
        }
    }
};

int main()
{
    Engine engine;
    {
        WeakRef<GameObject> obj = engine.NewGameObject();
        using_weak_ref(obj)
        {
            info(_obj->ToString());
            engine.AddComponent<TestBehavior>(_obj);
        }
        
    }
    engine.Start();
    engine.WaitFor();
    
    return 0;
}
