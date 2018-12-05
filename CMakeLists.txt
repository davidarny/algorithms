cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(algorithms)

set(CMAKE_CXX_STANDARD 17)

if (DEFINED ENV{MINGW_INCLUDE_DIR})
    set(Boost_INCLUDE_DIR $ENV{MINGW_INCLUDE_DIR})
endif ()

find_package(Boost 1.6 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (NOT DEFINED ENV{CI})
    add_subdirectory(src)
endif ()
add_subdirectory(test)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
