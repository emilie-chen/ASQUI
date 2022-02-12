#pragma once

#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include "Core.h"
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
#include <stdio.h>

namespace AsquiEngine {
    namespace Platform {

        void reset_terminal_mode();

        void set_conio_terminal_mode();

        int kbhit();

        int getch();

        glm::vec<2, uint16_t, defaultp> GetConsoleDimensions();
    }
}
