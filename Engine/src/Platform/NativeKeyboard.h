//
// Created by Ezra on 2022-02-12.
//
#pragma once
#include <termios.h>
#include "Core/Object.h"

namespace AsquiEngine
{
    namespace Platform
    {
        class NativeKeyboard : public Object
                {
                public:
                    bool GetKeyDown(char c);
                public :
                    char GetCharArray();
        };


    }
}