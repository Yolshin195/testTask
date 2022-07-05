#include "control_system.hpp"
#include <windows.h>
#include <iostream>

void control_system::update()
{
    char msg[256] = "hello world";

    while(1)
    {
		logger.write(msg, sizeof(msg));
        Sleep(1000);
    }
}