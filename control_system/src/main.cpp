#include <iostream>
#include "control_system/control_system.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	control_system cs;
	cs.init();
	cs.update();

	return 0;
}
