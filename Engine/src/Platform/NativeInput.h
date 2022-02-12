#pragma once

#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

namespace AsquiEngine
{
namespace Platform
{

void reset_terminal_mode();
void set_conio_terminal_mode();
int kbhit();
int getch();

}
}
