#!/usr/bin/env bash

for f in $(find . -type f ! -path "./CMake*" -name "*.cpp" -or -name "*.c" -or -name "*.hpp" -or -name "*.h");
do
    clang-format -i ${f}
done
