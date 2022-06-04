#!/bin/bash

g++ draw_v2.cc $(root-config --libs --cflags) -I$HOME -g -o draw_v2.exe || exit

./draw_v2.exe

rm draw_v2.exe
