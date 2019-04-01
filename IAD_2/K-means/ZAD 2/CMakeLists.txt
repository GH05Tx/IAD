cmake_minimum_required(VERSION 3.13)
project(ZAD_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ZAD_2 main.cpp src/KSrednich.cpp include/KSrednich.h src/Punkt.cpp include/Punkt.h src/Klaster.cpp include/Klaster.h src/Irys.cpp include/Irys.h src/Wino.cpp include/Wino.h src/Abalone.cpp include/Abalone.h)