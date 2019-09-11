#!/bin/bash

make

file main.o sumsine.o main

nm main.o

readelf -a main.o

objdump --disassemble main.o
objdump --disassemble sumsine.o


