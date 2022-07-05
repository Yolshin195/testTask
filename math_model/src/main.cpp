#include <iostream>

class config
{
public:
	int in_port = 0;
	int out_port = 0;
	double time_const = 0;
	int gain = 0;
	double period = 0;

	config(int argc, char *argv[])
	{
		if (argc == 11)
		{
			this->in_port = atoi(argv[2]);
			this->out_port = atoi(argv[4]);
			this->time_const = atof(argv[6]);
			this->gain = atoi(argv[8]);
			this->period = atof(argv[10]);
		}
	}

	void print()
	{
		using std::cout;
		using std::endl;

		cout << "Config: " << endl;
		cout << "  in_port \t= " << in_port << endl;
		cout << "  out_port \t= " << out_port << endl;
		cout << "  time_const \t= " << time_const << endl;
		cout << "  gain \t\t= " << gain << endl;
		cout << "  period \t= " << period << endl << endl;
	}
};



class mathModel
{
	int in_port = 0;
	int out_port = 0;
	float time_const = 0.5;	//постоянная времени модели, 
	int k = 10;			//gain коэффициент усиления модели;
	float period = 0.01;	//dt
	float dt = 0.01;
	float y = 0;
	float dy = 0;

	void init();
	void update();

public:
	float count(float x);
};

/*
	𝑦(𝑡) - выходной сигнал,
	𝑥(𝑡) - входной сигнал,
	𝑇 - постоянная времени модели,
	𝐾 - коэффициент усиления модели; 
*/
float mathModel::count(float x)
{
	dy =  ( ( k * x ) - y ) / time_const;
	y += dy * dt;
	return y;
}


class controlSystem
{
	int in_port = 0;
	int out_port = 0;
	int log_port = 0;
	int reference_value = 10;
	float prop = -1;
	float integ = -0.1;
	float dt = 0.01; //period
	float edt = 0;

	void init();
	void update();

public:
	float count(float x);
};

/*
	𝑦(𝑡) - выходной сигнал,
	𝑥(𝑡) - входной сигнал,
	𝑇 - постоянная времени модели,
	𝐾 - коэффициент усиления модели; 
*/
float controlSystem::count(float feedback)
{
	//std::cout << "feedback = " << feedback << ", reference_value = " << reference_value << ", edt = " << edt << std::endl;
	float e = feedback - reference_value;
	edt += e * dt;

	return (prop * e) + (integ * edt);
}

void mathModel::init()
{

}

void mathModel::update()
{

}

/*
input:
	math_model -i [in_port] -o [out_port] --Tm [time_const] --Km [gain] -t [period]
example:
	math_model -i 8004 -o 8005 --Tm 0.5 --Km 10 -t 0.01
*/
int main(int argc, char *argv[])
{
	mathModel m;
	controlSystem cs;

	float u = 0;
	float b = 0;
	for (int i = 0; i < 20000000; i++)
	{
		//std::cout << "b = " << b << ", u = " << u << std::endl; 

		b = m.count(u);
		//std::cout << b << std::endl;
		u = cs.count(b);

		if (b > 10) {
			
			std::cout << "i = " << i << "b = " << b << ", u = " << u << std::endl << std::endl;
			return 0;
		}
		
	}

	std::cout << "b = " << b << ", u = " << u << std::endl << std::endl;
	
	config conf(argc, argv);
	conf.print();
	return 0;
}

void controlSystem::init()
{

}

void controlSystem::update()
{

}