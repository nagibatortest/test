#pragma once

#include "Interface.h"
#include "ClassA.h"
#include "ClassB.h"

enum class Role {
    Proxy,
    Observer,
    Mediator,
};

template<Role>
class ClassC {};

template<>
class ClassC<Role::Proxy> : public Interface {
public:
    ClassC(Interface& i) : interface(i) {}

    void read(std::string data="") {
        std::cout << "Proxy_read" << std::endl;
        interface.read();
    }

    void write(std::string data=""){
        std::cout << "Proxy_write" << std::endl;
    }
private:
    Interface& interface;
};

template<>
class ClassC<Role::Mediator> : public Interface {
public:
    void add(ClassB& b) {
        colleagues.push_back(b);
    }

    void read(std::string data="") {
        std::cout << "Mediator_read" << std::endl;
        for (auto colleague : colleagues) {
            colleague.read();
        }
    }

    void write(std::string data="") {
        std::cout << "Mediator_write" << std::endl;
    }

private:
    std::vector<ClassB> colleagues;
};

template<>
class ClassC<Role::Observer> : public Interface {
public:
    void add(ClassA& subscriber) {
        subscribers.push_back(subscriber);
    }

    void read(std::string data="") {
        std::cout << "Observer_read " << data << std::endl;
        for (auto subscriber : subscribers) {
            subscriber.write();
        }
    }

    void write(std::string data="") {
        std::cout << "Observer_write" << std::endl;
    }

private:
    std::vector<ClassA> subscribers;
};
