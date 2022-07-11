#include "signal.hpp"
#include <sstream>

void signal::parse()
{
    std::stringstream ss {_data};
    ss >> id >> name >> value;
}

int signal::size() 
{
    return to_string().length();
}

std::string signal::to_string()
{
    std::stringstream ss;

    ss << id << " " << name << " " << value;

    return ss.str();
}