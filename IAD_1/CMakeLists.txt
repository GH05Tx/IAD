# cmake_minimum_required(VERSION <specify CMake version here>)
project(IAD_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(IAD_1 main.cpp src/Proba.cpp include/Proba.h src/Dane.cpp include/Dane.h src/DaneIS.cpp include/DaneIS.h src/DaneIVC.cpp include/DaneIVC.h src/DaneIV.cpp include/DaneIV.h src/DaneALL.cpp include/DaneALL.h)