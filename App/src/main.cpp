#include <iostream>
#include <glm/glm.hpp>
#include "AsquiEngine.h"
#include "Platform/NativeInput.h"


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
        //print(counter++);
        counter++;
        //auto dim = GetConsoleDimensions();
        //print(fmt::format("{{{}, {}}}", dim.x, dim.y));
        if (kbhit())
        {
            print(getch());
        }
        
        if (counter > 100)
        {
            Application::Quit();
        }
    }
};

int main()
{
//    {
//        BufferToggle bt;
//        bt.off();
//            char c = std::getchar(); //waits for you to press enter before proceeding to the next instruction
//        print(c);
//            bt.off();
//            c = std::getchar(); //processes next instruction as soon as you type a character (no enter)
//        print(c);
//            bt.on();
//            c = std::getchar(); //waits for you to press enter before proceeding to the next instruction
//        print(c);
//        return;
//    }
//    {
//        set_conio_terminal_mode();
//
//        while (!kbhit()) {
//                /* do some work */
//            }
//            print(getch());
//        return 0;
//    }
    set_conio_terminal_mode();
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
