#pragma once

#include "Interface.h"

class ClassA {
public:
    void read(Interface& i) {
        std::cout << "ClassA_read"<< std::endl;
        i.read();
    }

    void write() {
        std::cout << "A_write"<< std::endl;
    }
};
