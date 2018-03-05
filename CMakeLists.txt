cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp int_stack.cpp int_stack.h stack_machine.cpp stack_machine.h)
add_executable(untitled ${SOURCE_FILES})