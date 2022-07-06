#include "client.hpp"
#include "server.hpp"

class math_model
{
	int in_port = 8004;
	int out_port = 8005;
	float time_const = 0.5;	//постоянная времени модели, 
	int k = 10;			//gain коэффициент усиления модели;
	float period = 0.01;	//dt
	float dt = 0.01;
	float y = 0;
	float dy = 0;
    char msg[256];

    client out_control_system {out_port};

	void get_in_control_system();

public:
    void init();
    void update();
	float count(float x);
};