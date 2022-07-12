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

    double in_s {0};    // input signal
    double out_s{0};    // output signal

    double time_const = 0.5;    // постоянная времени модели, 
	int k = 10;                 // gain коэффициент усиления модели;
	double dt = 0.01;           // period
	double y = 0;
	double dy = 0;

    double count(double x);
    void get_in_control_system();
    void log();

public:
    void init();
    void update();
    void run();
};

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

int main(int argc, char *argv[])
{
    math_model mm;
    mm.init();
    mm.run();

    return 0;
}

void math_model::init()
{
    using std::cout;
    using std::endl;

    cout << "init: begin" << endl;

    std::thread t{&math_model::get_in_control_system, std::ref(*this)};
    t.detach();

    cout << "init: end" << endl;
}

void math_model::run()
{
    while (1)
    {
        this->update();
        Sleep(5000);
    }
}

void math_model::update()
{
    using std::cout;
    using std::endl;

    out_s = count(in_s);

    log();

    std::stringstream out_buff;
    out_buff << out_s;
    int status = out.write(out_buff);
    cout << "--Write control system message (" << status << "): " << out_buff.str() << endl;
}

void math_model::get_in_control_system()
{
    using std::cout;
    using std::endl;

    server in {in_port};
    cout << "thread run " << in_port << endl;
    int status;
    while (1)
    {
        std::stringstream in_buff;
        status = in.read(in_buff);
        in_buff >> in_s;

        cout << "--Read control system message (" << status << "): " << in_buff.str() << endl;
    }
}

void math_model::log()
{
    using std::cout;
    using std::endl;

    cout << "in (input signal) = " << in_s << ", out (output signal) = " << out_s << endl;
}
