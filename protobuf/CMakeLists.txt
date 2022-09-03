cmake_minimum_required(VERSION 3.22)
project(protobuf)

set(CMAKE_CXX_STANDARD 11)

add_executable(protobuf main.cpp Student/maps.cpp)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})