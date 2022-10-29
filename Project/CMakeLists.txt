cmake_minimum_required(VERSION 3.23)
project(BigReal)

set(CMAKE_CXX_STANDARD 20)

add_executable(BigReal main.cpp BigDecimalInt.cpp BigDecimalInt.h BigReal.cpp BigReal.h MainWindow.h MainWindow.cpp)
