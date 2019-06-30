#pragma once

#include "Interface.h"

class ClassB : public Interface {
public:
    ClassB(Interface& i) : interface(i), datas("init_data") {}

    void read(std::string data="") {
        std::cout << "B_read: " << datas << std::endl;
    }

    void write(std::string data="") {
        datas = data;
        interface.read(data);
    }

private:
    Interface& interface;
    std::string datas;
};
