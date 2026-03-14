#!/bin/bash

clang-tidy -fix -checks=google-readability-braces-around-statements -p=build src/interpreter.cpp


cd build || exit 1

make -j$(nproc) && ./dew
