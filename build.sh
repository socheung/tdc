#! /bin/sh -e
mkdir -p ./build
g++ -Wall -g -c ./src/main.cpp -o ./build/main.o
g++ -Wall -g -c ./src/util.cpp -o ./build/util.o
g++  ./build/main.o ./build/util.o -o ./build/test
