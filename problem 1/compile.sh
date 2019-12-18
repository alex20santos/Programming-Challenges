#!/usr/bin/env bash
g++ -Wall -std=c++98  main40.cpp -o main
./main < test.txt > log.txt
