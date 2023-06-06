#!/bin/bash

# #!/usr/local/bin/bash

set -x
g++ draw_Lc.cc -I$HOME $(root-config --libs --cflags) -g -o draw_Lc.exe || exit 1
./draw_Lc.exe
rm draw_Lc.exe

g++ draw_charmRAA.cc -I$HOME $(root-config --libs --cflags) -g -o draw_charmRAA.exe || exit 1
./draw_charmRAA.exe
rm draw_charmRAA.exe

g++ draw_beautyRAA.cc -I$HOME $(root-config --libs --cflags) -g -o draw_beautyRAA.exe || exit 1
./draw_beautyRAA.exe
rm draw_beautyRAA.exe

g++ draw_beautyRAA_0-100.cc -I$HOME $(root-config --libs --cflags) -g -o draw_beautyRAA_0-100.exe || exit 1
./draw_beautyRAA_0-100.exe
rm draw_beautyRAA_0-100.exe

g++ draw_bcRAA.cc -I$HOME $(root-config --libs --cflags) -g -o draw_bcRAA.exe || exit 1
./draw_bcRAA.exe
rm draw_bcRAA.exe

# g++ draw_bcvn.cc -I$HOME $(root-config --libs --cflags) -g -o draw_bcvn.exe || exit 1
# ./draw_bcvn.exe
# rm draw_bcvn.exe


set +x
