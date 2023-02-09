cmake_minimum_required(VERSION 3.21)
project("bank")

add_executable(bank main.cpp bank.cpp)
set_property(TARGET bank PROPERTY CXX_STANDARD 20)
