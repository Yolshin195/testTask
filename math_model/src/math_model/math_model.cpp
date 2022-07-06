#include "math_model.hpp"
#include <iostream>
#include <thread>

/*
	𝑦(𝑡) - выходной сигнал,
	𝑥(𝑡) - входной сигнал,
	𝑇 - постоянная времени модели,
	𝐾 - коэффициент усиления модели; 
*/
float math_model::count(float x)
{
	dy =  ( ( k * x ) - y ) / time_const;
	y += dy * dt;
	return y;
}

void  math_model::update()
{    
    out_control_system.write(msg, sizeof(msg));
}

void math_model::init()
{
	std::cout << "init: begin" << std::endl;
	std::thread t {&math_model::get_in_control_system, std::ref(*this)};
	t.join();
	std::cout << "init: end" << std::endl;
}

void math_model::get_in_control_system()
{
	server in_control_system {in_port};
	char msg[256] = "Hello, world! in math model";
	std::cout << "thread run " << in_port << std::endl;
	while (1)
	{
		std::cout << "begin read is in_math_model" << std::endl;
		in_control_system.read(msg, sizeof(msg));
		std::cout << "Read in control system message: " << msg << std::endl;
		Sleep(1000);
	}
}