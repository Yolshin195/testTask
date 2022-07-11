#include <iostream>
#include <sstream>
#include "net/client/client.hpp"

class control_system
{
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

    client c {9001};

    double i = 0.0;
    int status = 0;

    while (1) 
    {
        std::stringstream buf;
        i += 0.19242394;
        buf << i;
        status = c.write(buf);

        if (status == buf.str().length()) 
        {
            std::cout << "success write size " << status << ", write message " << buf.str() << std::endl;
        }
        
        buf.clear();

        if (i > 1000) i = 0;
        Sleep(10);
    }

}

void control_system::update()
{
    
}

void control_system::run()
{
    
}