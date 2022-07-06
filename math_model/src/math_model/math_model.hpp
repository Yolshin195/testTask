#include "client.hpp"
#include "server.hpp"

class math_model
{
	int in_port = 0;
	int out_port = 0;
	float time_const = 0.5;	//постоянная времени модели, 
	int k = 10;			//gain коэффициент усиления модели;
	float period = 0.01;	//dt
	float dt = 0.01;
	float y = 0;
	float dy = 0;

    server in_control_system {in_port};
    client out_control_system {out_port};

	void init();
	void update();

public:
	float count(float x);
};