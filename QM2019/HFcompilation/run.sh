#!/usr/local/bin/bash

g++ draw_Lc.cc -I$HOME $(root-config --libs --cflags) -g -o draw_Lc.exe || exit 1
./draw_Lc.exe
rm draw_Lc.exe
