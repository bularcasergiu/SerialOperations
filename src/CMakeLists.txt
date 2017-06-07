cmake_minimum_required(VERSION 3.5)
project(Serial)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(GCC_COVERAGE_LINK_FLAGS    "-Wl,--no-as-needed,-ldl")

set (CMAKE_EXE_LINKER_FLAGS -ldl)

set(SOURCE_FILES main.cpp SerialClass.h SerialLinux.h)
if(WIN32)
    set(SOURCE_FILES
            ${PROJECT_SOURCE_DIR}/SerialClass.cpp
            ${SOURCE_FILES})
    message("----------------------------------------WIN32")
    message(SOURCE_FILES)
else(WIN32)
    set(SOURCE_FILES
            ${PROJECT_SOURCE_DIR}/SerialLinux.cpp
            ${SOURCE_FILES})
    message("----------------------------------------NOT WIN32")
endif(WIN32)
add_executable(SerialOperations ${SOURCE_FILES})