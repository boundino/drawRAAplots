#!/bin/bash

g++ draw_v2.cc $(root-config --libs --cflags) -I$HOME -g -o draw_v2.exe || exit
g++ draw_v2_pPb.cc $(root-config --libs --cflags) -I$HOME -g -o draw_v2_pPb.exe || exit

./draw_v2.exe
./draw_v2_pPb.exe

rm draw_v2.exe
rm draw_v2_pPb.exe
