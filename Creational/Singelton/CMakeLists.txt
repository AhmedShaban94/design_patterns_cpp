cmake_minimum_required(VERSION 3.11.0)
project(cpp_design_patterns)

# main configuration 
add_executable(thread_safe_singelton thread_safe_singelton.cpp)
set_target_properties (thread_safe_singelton PROPERTIES FOLDER "01.Creational")

add_executable(meyers_singelton meyers_singelton.cpp)
set_target_properties (meyers_singelton PROPERTIES FOLDER "01.Creational")