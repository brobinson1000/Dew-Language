#!/bin/bash


rm -rf build
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build


clang-tidy -fix -checks=google-readability-braces-around-statements -p=build src/*.cpp

