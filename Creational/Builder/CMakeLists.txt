cmake_minimum_required(VERSION 3.11.0)
project(cpp_design_patterns)

# main configuration 
add_executable(builder builder.cpp)
set_target_properties (builder PROPERTIES FOLDER "01.Creational")