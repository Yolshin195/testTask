#include <iostream>
#include <sstream>
#include <thread>
#include "net/client/client.hpp"
#include "net/server/server.hpp"

class control_system
{
    int in_port {8005};
    int out_port {8004};
    int log_port {8006};
    client out_math_model {out_port};
    client logger {log_port};

    bool is_in_math_model = true;
    double in_math_model = 0;
    // double reference_value {10};
    // double prop {1};
    // double integ {0.1};
    // double period {0.01}; //dt

    int reference_value = 10;
	double prop = -1;
	double integ = -0.1;
	double dt = 0.01; //period
	double edt = 0;

    double count(double feedback);

    void get_in_math_model();
public:
    void init();
    void update();
    void run();
};

int main(int argc, char* argv[])
{
    control_system cs;
    cs.init();
    cs.run();

    return 0;
}

void control_system::init()
{
    using std::cout;
    using std::endl;

    std::cout << "init: begin" << std::endl;
    std::thread t{&control_system::get_in_math_model, std::ref(*this)};
    t.detach();
    std::cout << "init: end" << std::endl;

}

void control_system::update()
{
    using std::cout;
    using std::endl;

    double us = count(this->in_math_model);
    cout << "in = " << this->in_math_model << ", out = " << us << endl;

    std::stringstream out_buf;
    out_buf << us;

    out_math_model.write(out_buf);

    out_buf.clear();

    std::stringstream log_buf;
    log_buf << us << " " << in_math_model << " " << reference_value << " " << in_math_model << " " << us;

    logger.write(log_buf);
    log_buf.clear();
}

void control_system::run()
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
double control_system::count(double feedback)
{
	//std::cout << "feedback = " << feedback << ", reference_value = " << reference_value << ", edt = " << edt << std::endl;
	double e = feedback - reference_value;
	edt += e * dt;

	return (prop * e) + (integ * edt);
}

void control_system::get_in_math_model()
{
    server in_math_model{in_port};
    std::cout << "thread run " << in_port << std::endl;
    int status;
    while (is_in_math_model)
    {
        //std::cout << "--begin read is in_math_model" << std::endl;
        std::stringstream ss;
        status = in_math_model.read(ss);
        ss >> this->in_math_model;

        ss.clear();
        std::cout << "--Read in control system message: " << ss.str() << ", size package: " << status << std::endl;
        //Sleep(100);
    }
}