cmake_minimum_required(VERSION 3.8)
project(metprog1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ClassA.h ClassB.h ClassC.h Interface.h)
add_executable(metprog1 ${SOURCE_FILES})