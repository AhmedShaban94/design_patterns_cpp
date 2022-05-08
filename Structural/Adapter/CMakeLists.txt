cmake_minimum_required(VERSION 3.11.0)
project(cpp_design_patterns)

# main configuration 
add_executable(adapter adapter.cpp tinyxml2.cpp)
set_target_properties (adapter PROPERTIES FOLDER "03.Structural")

# Nlohamann configuration
include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG v3.10.5)

FetchContent_MakeAvailable(json)
target_link_libraries(adapter PRIVATE nlohmann_json::nlohmann_json)

# TinyXML configuration
