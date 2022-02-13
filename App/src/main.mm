#include <iostream>
#include <glm/glm.hpp>
#include "AsquiEngine.h"
#include "Platform/NativeInput.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>


using namespace AsquiEngine;
using namespace AsquiEngine::Platform;


//class BufferToggle
//{
//    private:
//        struct termios t;
//
//    public:
//
//        /*
//         * Disables buffered input
//         */
//
//        void off(void)
//        {
//            tcgetattr(fileno(stdin), &t); //get the current terminal I/O structure
//            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
//            tcsetattr(fileno(stdin), TCSANOW, &t); //Apply the new settings
//        }
//
//
//        /*
//         * Enables buffered input
//         */
//
//        void on(void)
//        {
//            tcgetattr(fileno(stdin), &t); //get the current terminal I/O structure
//            t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
//            tcsetattr(fileno(stdin), TCSANOW, &t); //Apply the new settings
//        }
//};


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
        auto transform = GetComponent<Transform>();
        using_weak_ref(transform)
        {
            auto pos = _transform->GetPosition();
            while (kbhit())
            {
                char input = getch();
                auto movementAmount = 10 * Time::GetDeltaTime();
                switch (input)
                {
                    case 'a':
                    {
                        pos.x -= movementAmount;
                        _transform->SetPosition(pos);
                        break;
                    }
                    case 'd':
                    {
                        pos.x += movementAmount;
                        _transform->SetPosition(pos);
                        break;
                    }
                    case 'w':
                    {
                        pos.y -= movementAmount;
                        _transform->SetPosition(pos);
                        break;
                    }
                    case 's':
                    {
                        pos.y += movementAmount;
                        _transform->SetPosition(pos);
                        break;
                    }
                    case 'q':
                    {
                        Application::Quit();
                        break;
                    }
                }
            }
        }
    }
};

class TestRenderer : public Renderer
{
public:
    virtual void Render(RenderingManager* manager) override
    {
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                manager->DrawPixel(gameObject, x, y, RenderingManager::Code::BG_MAGENTA);
            }
        }
    }
};

int main()
{
    {
        MonoDomain *domain;

        domain = mono_jit_init("Test domain");
    }
    set_conio_terminal_mode();
    Engine engine;
    {
        WeakRef<GameObject> obj = engine.NewGameObject();
        using_weak_ref(obj)
        {
            info(_obj->ToString());
            engine.AddComponent<TestBehavior>(_obj);
            engine.AddComponent<TestRenderer>(_obj);
        }
        
    }
    engine.Start();
    engine.WaitFor();
    
    return 0;
}
