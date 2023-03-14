cmake_minimum_required(VERSION 3.21)
project("various")

add_executable(value_ptr_ref value_ptr_ref.cpp)
add_executable(operators operators.cpp)
add_executable(templates templates.cpp)
add_executable(stl_containers stl_containers.cpp)
add_executable(destructors destructors.cpp)

# design pattern
add_executable(singleton singleton.cpp)
add_executable(factory_method factory_method.cpp)
# set_property(TARGET bank PROPERTY CXX_STANDARD 20)
