cmake_minimum_required(VERSION 3.11.0)
project(cpp_design_patterns)

# main configuration 
add_executable(strategy strategy.cpp)
set_target_properties (strategy PROPERTIES FOLDER "01.Behaviorals")