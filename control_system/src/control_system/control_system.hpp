// #include "server.hpp"
#include "client.hpp"

class control_system
{

    // control_system(int in_port, int out_port, int log_port, double reference_value, double prop, double integ, double period)
    //     : in_port(in_port)
    // {};

    int in_port {8005};
    int out_port {8004};
    int log_port {8006};
    double reference_value {10};
    double prop {1};
    double integ {0.1};
    double period {0.01};

    client logger {log_port};

    void init();
    
public:
    void update();
};