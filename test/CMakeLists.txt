cmake_minimum_required(VERSION 3.22)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test src/main.cpp include/regex_test.h src/regex_test.cpp src/FuncInfo.cpp include/FuncInfo.h include/SASSLineInfo.h include/helpFunc.h src/helpFunc.cpp include/Register.h include/DataType.h)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
