#!/bin/sh

rm -rf build/
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
cp build/compile_commands.json .
sudo chown root ./build/main
sudo chmod +s ./build/main