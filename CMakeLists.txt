cmake_minimum_required(VERSION 3.11)
project(cpp_design_patterns)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

if(MSVC)
  add_compile_options(/W3 /permissive-)
  string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus")
else()
  add_compile_options(-O3 -Wall -Wextra -pedantic)
endif()

add_subdirectory(Behavioral)
add_subdirectory(Creational)
add_subdirectory(Structural)