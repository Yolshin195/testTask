#include "net/client/client.hpp"
#include "net/server/server.hpp"
#include <iostream>
#include <sstream>
#include <thread>

class control_system
{
    int in_port {8005};
    int out_port {8004};
    int log_port {8006};
    client out {out_port};
    client logger {log_port};

    double fb_s = 0; // feedback signal
    double c_s = 0; // control signal

    int reference_value = 10;
	double prop = -1;
	double integ = -0.1;
	double dt = 0.01; //period
	double edt = 0;

    double count(double feedback);
    void get_fb_math_model();
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
double control_system::count(double feedback)
{
	//std::cout << "feedback = " << feedback << ", reference_value = " << reference_value << ", edt = " << edt << std::endl;
	double e = feedback - reference_value;
	edt += e * dt;

	return (prop * e) + (integ * edt);
}

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

    cout << "init: begin" << endl;

    std::thread t{&control_system::get_fb_math_model, std::ref(*this)};
    t.detach();

    cout << "init: end" << endl;
}

void control_system::run()
{
    while (1)
    {
        this->update();
        Sleep(5000);
    }
}

void control_system::update()
{
    using std::cout;
    using std::endl;

    c_s = count(fb_s);

    log();

    std::stringstream out_buff;
    out_buff << c_s << " ";
    int status = out.write(out_buff);
    cout << "--Write math model message (" << status << "): " << out_buff.str() << endl;

    std::stringstream log_buff;
    log_buff << c_s << " " << fb_s << " " << reference_value << " " << fb_s << " " << c_s;
    int log_status = logger.write(log_buff);
    cout << "--Write logger message (" << log_status << "): " << log_buff.str() << endl;
}

void control_system::get_fb_math_model()
{
    using std::cout;
    using std::endl;

    server in {in_port};
    std::cout << "thread run " << in_port << std::endl;

    while (1)
    {
        std::stringstream in_buff;
        int status = in.read(in_buff);
        in_buff >> fb_s;

        cout << "--Read math model message (" << status << "): " << in_buff.str() << endl;
    }
}

void control_system::log()
{
    using std::cout;
    using std::endl;

    cout << "in (feedback signal) = " << fb_s << ", out (control signal) = " << c_s << endl;
}