#include "control_system.hpp"
#include <windows.h>
#include <iostream>

void control_system::update()
{
    char msg[256] = "hello world";

    while(1)
    {
        in_math_model.read(msg, sizeof(msg));
        out_math_model.write(msg, sizeof(msg));
		logger.write(msg, sizeof(msg));
        Sleep(1000);
    }
}