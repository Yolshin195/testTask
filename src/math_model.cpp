#include "net/server/server.hpp"
#include <iostream>
#include <thread>

class math_model
{
    int in_port{9001};
    double in_control_system{0};

    double dy;
    double k;
    double x;
    double y;
    double time_const;
    double dt;

    double count(double x);
    void get_in_control_system();

public:
    void init();
    void update();
    void run();
};

int main(int argc, char *argv[])
{
    math_model mm;
    mm.init();
    mm.run();

    return 0;
}

void math_model::init()
{

    std::cout << "init: begin" << std::endl;
    std::thread t{&math_model::get_in_control_system, std::ref(*this)};
    t.detach();
    std::cout << "init: end" << std::endl;
}

void math_model::update()
{
    std::cout << "--Start update" << std::endl;
    std::cout << "in_control_system == " << this->in_control_system << std::endl;
    std::cout << "--End update" << std::endl;
    
}

void math_model::run()
{
    while (1)
    {
        this->update();
        Sleep(10);
    }
}

/*
    𝑦(𝑡) - выходной сигнал,
    𝑥(𝑡) - входной сигнал,
    𝑇 - постоянная времени модели,
    𝐾 - коэффициент усиления модели;
*/
double math_model::count(double x)
{
    dy = ((k * x) - y) / time_const;
    y += dy * dt;
    return y;
}

void math_model::get_in_control_system()
{
    server in_control_system{in_port};
    std::cout << "thread run " << in_port << std::endl;
    int status;
    while (1)
    {
        std::cout << "--begin read is in_math_model" << std::endl;
        std::stringstream ss;
        status = in_control_system.read(ss);

        ss >> this->in_control_system;

        ss.clear();
        std::cout << "--Read in control system message: " << ss.str() << ", size package: " << status << std::endl;
        Sleep(100);
    }
}