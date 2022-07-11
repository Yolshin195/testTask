#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

class signal
{
    int id;
    std::string name;
    std::string value;

    std::string _data;

    void parse();

public:
    signal(){};
    signal(int id, std::string name, std::string value) :id(id), name(name), value(value) {};
    signal(std::string data) : _data(data) {parse();};

    int size();
    std::string to_string();
};

#endif