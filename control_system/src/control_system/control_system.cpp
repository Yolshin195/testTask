#include "control_system.hpp"
#include <windows.h>
#include <iostream>
#include <thread>

void control_system::init()
{
	std::cout << "init: begin" << std::endl;
	std::thread t {&control_system::get_in_math_model, std::ref(*this)};
	t.detach();
	std::cout << "init: end" << std::endl;
}

void control_system::get_in_math_model()
{
	server in_math_model {in_port};
	char msg[256] = "Hello, world! in math model";
	std::cout << "thread run " << in_port << std::endl;
	while (1)
	{
		std::cout << "begin read is in_math_model" << std::endl;
		in_math_model.read(msg, sizeof(msg));
		Sleep(1000);
	}
}

void control_system::update()
{
	char msg[256] = "Hello, world!";
    while(1)
    {

        out_math_model.write(msg, sizeof(msg));
		logger.write(msg, sizeof(msg));
        Sleep(1000);
    }
}

/*
	𝑦(𝑡) - выходной сигнал,
	𝑥(𝑡) - входной сигнал,
	𝑇 - постоянная времени модели,
	𝐾 - коэффициент усиления модели; 
*/
float control_system::count(float feedback)
{
	//std::cout << "feedback = " << feedback << ", reference_value = " << reference_value << ", edt = " << edt << std::endl;
	float e = feedback - reference_value;
	edt += e * dt;

	return (prop * e) + (integ * edt);
}