#pragma once

#include <iostream>


class SharedPointerCounter {
    int counter;

public:
    SharedPointerCounter() : counter(1) {}

    void Increase() {
        counter++;
    }

    int Decrease() {
        counter--;
        return counter;
    }
};

template <class T> class SharedPointer {
private:
    T *data;
    SharedPointerCounter *counter;

public:
    SharedPointer() : data(nullptr) {
        counter = new SharedPointerCounter();
    }

    SharedPointer(T* value) : data(value) {
        counter = new SharedPointerCounter();
    }

    SharedPointer(const SharedPointer<T>& pointer) : data(pointer.data), counter(pointer.counter) {
        counter->Increase();
    }

    ~SharedPointer() {
        if(counter->Decrease() == 0)
        {
            delete data;
            delete counter;
        }
    }

    SharedPointer<T>& operator = (const SharedPointer<T>& pointer) {
        if (this != &pointer) {
            if(counter->Decrease() == 0) {
                delete data;
                delete counter;
            }

            data = pointer.data;
            counter = pointer.counter;
            counter->Increase();
        }
        return *this;
    }

    T& operator* () {
        return *data;
    }

    T* operator-> () {
        return data;
    }
};