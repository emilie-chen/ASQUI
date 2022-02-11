#include <iostream>
#include <glm/glm.hpp>
#include "AsquiEngine.h"

using namespace AsquiEngine;

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
        if (counter > 200)
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
            auto transform = engine.GetComponent<Transform>(_obj);
            auto testBehavior = engine.AddComponent<TestBehavior>(_obj);
            
            using_weak_ref(testBehavior)
            {
                _testBehavior->OnUpdate();
            }

            using_weak_ref(transform)
            {
                print(_transform->ToString());
            }
            
            //engine.DestroyGameObject(_obj);
        }
        
    }
    engine.Start();
    engine.WaitFor();
    
    return 0;
}
