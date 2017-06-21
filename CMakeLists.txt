cmake_minimum_required(VERSION 3.6)
project(sehw4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp model.h controller.h view.cpp view.h model.cpp controller.cpp)
add_executable(sehw4 ${SOURCE_FILES})