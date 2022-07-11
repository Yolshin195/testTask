#include <iostream>
#include <sstream>
#include "net/server/server.hpp"
class logger
{
    int port {8006};
    server s {port};

    double math_in = 0;
    double math_out = 0;
    double control_in = 0;
    double control_fb = 0;
    double control_out = 0;

public:
    void init();
    void update();
    void run();
};

int main(int argc, char* argv[])
{
    logger log;
    log.init();
    log.run();
    
    return 0;
}

void logger::init()
{

}

void logger::update()
{
    using std::cout;
    using std::endl;

    std::stringstream ss;

    int status = s.read(ss);

    cout << "read " << status << ", value (" << ss.str().length() << ") " << ss.str() << endl;

    ss >> math_in >> math_out >> control_in >> control_fb >> control_out;

    cout 
        << "math_in " << math_in 
        << ", math_out " << math_out 
        << ", control_in " << control_in 
        << ", control_fb " << control_fb 
        << ", control_out " << control_out << endl;
}

void logger::run()
{
    while (1) {
        this->update();
        //Sleep(100);
    }
}