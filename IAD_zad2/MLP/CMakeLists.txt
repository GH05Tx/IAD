cmake_minimum_required(VERSION 3.12)
project(untitled2)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled2 main.cpp src/Layer.cpp include/Layer.h src/Perceptron.cpp include/Perceptron.h src/Space.cpp include/Space.h)