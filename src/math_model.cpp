#include "net/server/server.hpp"
#include "net/client/client.hpp"
#include <iostream>
#include <sstream>
#include <thread>

class math_model
{
    int in_port{8004};
    int out_port {8005};
    client out {out_port};

    double in_control_system{0};

    // double dy;
    // double k;
    // double x;
    // double y;
    // double time_const;
    // double dt;

    double time_const = 0.5;	//постоянная времени модели, 
	int k = 10;			//gain коэффициент усиления модели;
	double period = 0.01;	//dt
	double dt = 0.01;
	double y = 0;
	double dy = 0;

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
    using std::cout;
    using std::endl;
    //std::cout << "--Start update" << std::endl;
    //std::cout << "in_control_system == " << this->in_control_system << std::endl;
    double out_control_system = this->count(this->in_control_system);
    cout << "in = " << this->in_control_system << ", out = " << out_control_system << endl;
    std::stringstream out_buf;

    out_buf << out_control_system;

    out.write(out_buf);
    out_buf.clear();

    //std::cout << "--End update" << std::endl;
    
}

void math_model::run()
{
    while (1)
    {
        this->update();
        Sleep(1);
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
	dy =  ( ( k * x ) - y ) / time_const;
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
        //std::cout << "--begin read is in_math_model" << std::endl;
        std::stringstream ss;
        status = in_control_system.read(ss);

        ss >> this->in_control_system;

        ss.clear();
        //std::cout << "--Read in control system message: " << ss.str() << ", size package: " << status << std::endl;
        //Sleep(100);
    }
}