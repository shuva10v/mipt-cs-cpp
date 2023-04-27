cmake_minimum_required(VERSION 3.0.0)
# vcpkg integration - override cmake toolchain (note: should be placed before project() call)
set(VCPKG_CXX_FLAGS_RELEASE -Wno-narrowing) # fix for restbed
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(rest VERSION 0.1.0)

# Lets use modern standard
set(CMAKE_CXX_STANDARD 17)

add_executable(rest_server server.cpp)


find_package(spdlog CONFIG REQUIRED)
target_link_libraries(rest_server PRIVATE spdlog::spdlog_header_only)
# spdlog depends on fmt, it is also useful
find_package(fmt CONFIG REQUIRED)
target_link_libraries(rest_server PRIVATE fmt::fmt-header-only)

find_package(unofficial-restbed CONFIG REQUIRED)
target_link_libraries(rest_server PRIVATE unofficial::restbed::restbed)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(rest_server PRIVATE JsonCpp::JsonCpp)

add_executable(rest_client client.cpp)

target_link_libraries(rest_client PRIVATE spdlog::spdlog_header_only)
target_link_libraries(rest_client PRIVATE fmt::fmt-header-only)
find_package(restclient-cpp CONFIG REQUIRED)
target_link_libraries(rest_client PRIVATE restclient-cpp)
target_link_libraries(rest_client PRIVATE JsonCpp::JsonCpp)