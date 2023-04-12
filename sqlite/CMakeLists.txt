cmake_minimum_required(VERSION 3.0.0)
# vcpkg integration - override cmake toolchain (note: should be placed before project() call)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(sqlitedemo VERSION 0.1.0)

# Lets use modern standard
set(CMAKE_CXX_STANDARD 17)

add_executable(sqlitedemo main.cpp)


find_package(spdlog CONFIG REQUIRED)
target_link_libraries(sqlitedemo PRIVATE spdlog::spdlog_header_only)
# spdlog depends on fmt, it is also useful
find_package(fmt CONFIG REQUIRED)
target_link_libraries(sqlitedemo PRIVATE fmt::fmt-header-only)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(sqlitedemo PRIVATE unofficial::sqlite3::sqlite3)

find_path(SQLITE_MODERN_CPP_INCLUDE_DIRS "sqlite_modern_cpp.h")
target_include_directories(sqlitedemo PRIVATE ${SQLITE_MODERN_CPP_INCLUDE_DIRS})