cmake_minimum_required(VERSION 3.20)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_INCLUDE_DIRS}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTest.cpp)
add_executable(runProgramTest ${TEST_SOURCE_FILES})
target_link_libraries(runProgramTest gtest gtest_main core)