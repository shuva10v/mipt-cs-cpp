cmake_minimum_required(VERSION 3.21)
project("various")

add_executable(value_ptr_ref value_ptr_ref.cpp)
add_executable(operators operators.cpp)
add_executable(templates templates.cpp)
add_executable(stl_containers stl_containers.cpp)
# set_property(TARGET bank PROPERTY CXX_STANDARD 20)
