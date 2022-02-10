cmake_minimum_required(VERSION 3.11.0)
project(cpp_design_patterns)

# main configuration 
add_executable(factory_method factory_method.cpp)
set_target_properties (factory_method PROPERTIES FOLDER "01.Creational")