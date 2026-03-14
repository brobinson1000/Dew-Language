cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DewLang VERSION 1.0 DESCRIPTION "Dew Language" LANGUAGES CXX)

add_executable(dew src/interpreter.cpp)

target_include_directories(dew PUBLIC include)




