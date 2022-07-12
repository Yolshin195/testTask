#include <iostream>
#include <sstream>
#include <fstream>
#include "net/server/server.hpp"
#include <string>
class logger
{
    int port {8006};
    server s {port};
    std::string filename;
    std::ofstream file;

    double math_in = 0;
    double math_out = 0;
    double control_in = 0;
    double control_fb = 0;
    double control_out = 0;

    void write_to_file();

public:
    void init();
    void update();
    void run();
    ~logger();
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
    filename = "log.csv";
    file.open(filename);
    if (!file)
    {
        std::cout << "file open error, filename " << filename << std::endl;
        exit(1);
    }

    file 
        << "math_in"
        << "; math_out"
        << "; control_in"
        << "; control_fb"
        << "; control_out" << std::endl;
    file.flush();
}

void logger::update()
{
    using std::cout;
    using std::endl;

    std::stringstream in;

    int status = s.read(in);

    cout << "read " << status << ", value (" << in.str().length() << ") " << in.str() << endl;

    in >> math_in >> math_out >> control_in >> control_fb >> control_out;

    write_to_file();

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

void logger::write_to_file()
{
    if (!file)
    {
        std::cout << "file closed, filename " << filename << std::endl;
    }

    file 
        << math_in 
        << ";" << math_out 
        << ";" << control_in 
        << ";" << control_fb 
        << ";" << control_out << std::endl;
    file.flush();
}

logger::~logger()
{
    file.close();
    std::cout << "destructor" << std::endl;
}