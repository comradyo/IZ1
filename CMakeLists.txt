cmake_minimum_required(VERSION 3.16)
project(IZ1 C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SOURCE_FILES src/List.c src/Warships.c)

add_library(study_std_lib STATIC ${LIB_SOURCE_FILES})

add_executable(prog src/main.c)
target_link_libraries(prog study_std_lib)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
#message(${GTEST_LIBRARIES})
#message(${GTEST_INCLUDE_DIRS})

add_executable(tests tests/tests.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests study_std_lib)
