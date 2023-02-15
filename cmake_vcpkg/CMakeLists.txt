cmake_minimum_required(VERSION 3.0.0)
# vcpkg integration - override cmake toolchain (note: should be placed before project() call)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(vcpkgdemo VERSION 0.1.0)

include(CTest)
enable_testing()

# Lets use modern standard
set(CMAKE_CXX_STANDARD 17)

add_executable(vcpkg_demo src/main.cpp src/complex.cpp)


find_package(spdlog CONFIG REQUIRED)
target_link_libraries(vcpkg_demo PRIVATE spdlog::spdlog_header_only)
# spdlog depends on fmt, it is also useful
find_package(fmt CONFIG REQUIRED)
target_link_libraries(vcpkg_demo PRIVATE fmt::fmt-header-only)

# CPack stuff

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
