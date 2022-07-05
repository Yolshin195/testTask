#include <WinSock2.h>

class control_system
{
    int math_model_port = 8004;
    int control_system_port = 8005;
    int log_port = 8006;
    SOCKET math_model_socket;
    SOCKET control_system_socket;
    SOCKET log_socket;

    void connectSocket(int port, SOCKET *socket);
    void getLogSocket();

    void init();
    
public:
    void update();
};