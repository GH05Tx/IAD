cmake_minimum_required(VERSION 3.13)
project(IAD_MLP)

set(CMAKE_CXX_STANDARD 17)

add_executable(IAD_MLP main.cpp Bias.cpp Bias.h Functions.cpp Functions.h InputLayer.h InputNeuron.h Klasyfikacja.h Layer.cpp Layer.h Net.cpp Net.h Neuron.cpp Neuron.h Service.h ReadData.h Teach.h)