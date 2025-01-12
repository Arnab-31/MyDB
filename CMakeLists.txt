cmake_minimum_required(VERSION 3.10)
project(MyDB)

set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
list(REMOVE_ITEM SOURCES ${TEST_SOURCES})

add_library(MyDB ${SOURCES})

# Add Google Test
set(GTest_DIR C:/Users/arnabpoddar/code/vcpkg/installed/x64-windows/share/gtest)
find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# enable_testing()

# Add main executabl
add_executable(main_program main.cpp)
target_link_libraries(main_program MyDB)

#Add test executable
add_executable(test_queries tests/test_queries.cpp)
target_link_libraries(test_queries PRIVATE MyDB GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(test_queries)