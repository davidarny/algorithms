cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(algorithms)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.65.1 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

enable_testing()
add_test(NAME Test COMMAND Test)
