cmake_minimum_required(VERSION 3.7)
project(COMread)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SerialClass.cpp SerialClass.h SerialLinux.cpp SerialLinux.h)
add_executable(SerialOperations ${SOURCE_FILES})