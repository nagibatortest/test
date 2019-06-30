#pragma once

#include <iostream>
#include <vector>
#include <string>

class Interface {
public:
    virtual void read(std::string data="") = 0;
    virtual void write(std::string data="") = 0;
};