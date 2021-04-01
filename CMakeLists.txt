cmake_minimum_required(VERSION 3.16)
project(IZ1 C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")

#static libs
add_library(STATIC_SEQ STATIC static_lib/sequential.c)
include_directories(static_lib)

add_library(STATIC_FUNCS STATIC functions_static/functions.c)
include_directories(functions_static)

#dynamic libs
add_library(DYNAMIC_PAR SHARED dynamic_lib/parallel.c)
include_directories(dynamic_lib)

#executable program
add_executable(prog src/main.c)
target_link_libraries(prog STATIC_FUNCS)
target_link_libraries(prog STATIC_SEQ)
target_link_libraries(prog DYNAMIC_PAR)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests tests/tests.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests STATIC_FUNCS)
target_link_libraries(tests STATIC_SEQ)
target_link_libraries(tests DYNAMIC_PAR)
