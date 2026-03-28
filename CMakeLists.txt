cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DewLang VERSION 1.0 DESCRIPTION "Dew Language" LANGUAGES C CXX)

# Main exec
add_executable(dew
    src/interpreter.cpp
    src/print.cpp
    src/error_handling.cpp
    src/math_utils.c
    src/math_wrapper.cpp
    src/unix_wrapper.cpp
    src/unix_utils.c
)

target_include_directories(dew PUBLIC include)

# testing
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# test exec
add_executable(math_utils_test
    tests/math_utils_test.cpp
    src/math_utils.c
)

target_include_directories(math_utils_test PUBLIC include)
target_link_libraries(math_utils_test ${GTEST_LIBRARIES} pthread)
add_test(NAME MathUtilsTests COMMAND math_utils_test)
