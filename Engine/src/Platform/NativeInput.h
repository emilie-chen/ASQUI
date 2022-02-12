#pragma once

#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include "Core.h"
#include "Core/Object.h"
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
#include <stdio.h>

namespace AsquiEngine {
    namespace Platform {

        void reset_terminal_mode();


        ////
        class NativeInputManager : public Object {
        public :
            void OnUpdate();

            template<typename T>
            void AddConsoleDimensionChangedListener(const T &func){
                m_FunctionList.template emplace_back(func);
            };
        private:
            List<std::function<void(const glm::vec<2, int, defaultp>&)>> m_FunctionList;
        };

        ////
        void set_conio_terminal_mode();

        int kbhit();

        int getch();

        glm::vec<2, uint16_t, defaultp> GetConsoleDimensions();
    }
}
