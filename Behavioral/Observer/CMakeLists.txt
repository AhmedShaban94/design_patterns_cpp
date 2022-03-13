cmake_minimum_required(VERSION 3.11.0)
project(cpp_design_patterns)

# main configuration 
add_executable(observer observer.cpp)
set_target_properties (observer PROPERTIES FOLDER "01.Behavioral")