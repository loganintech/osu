cmake_minimum_required(VERSION 3.5)
project(cs161_assignments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    "Assignment 1/assignment1.cpp"
    "Assignment 1/UnsignedLongLongMa.cpp"
    "Assignment 2/assignment2.cpp"
    "Assignment 3/assignment3.cpp"
    "Assignment 4/assignment4.cpp"
    Generic/recursivePower.cpp
    Generic/test.cpp
    "Lab 1/HelloWorld.cpp"
    "Lab 1/InputText.cpp"
    "Lab 2/lab2.cpp"
    "Lab 3/lab3.cpp"
    "Lab 4/FixedCode.cpp"
    "Lab 4/IntegralCalc.cpp"
    "Lab 5/lab5.cpp"
    "Lab 6/lab6Fib.cpp"
    "Lab 6/lab6String.cpp")

add_executable(cs161_assignments ${SOURCE_FILES})