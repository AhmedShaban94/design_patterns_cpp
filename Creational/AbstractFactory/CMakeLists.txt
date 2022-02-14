cmake_minimum_required(VERSION 3.11.0)
project(cpp_design_patterns)

# main configuration 
add_executable(abstarct_factory abstract_factory.cpp)
set_target_properties (abstarct_factory PROPERTIES FOLDER "01.Creational")