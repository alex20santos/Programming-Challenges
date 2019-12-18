#!/usr/bin/env bash
g++ -Wall -std=c++98  main.cpp -o main
./main < test.txt >log.txt
