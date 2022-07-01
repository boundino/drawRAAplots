#!/bin/bash

CONFIG=configs/hfwinc22.conf
DO_PLOTTheory=${1:-0}

#
echo "compiling..."
[[ $DO_PLOTTheory -eq 1 || $# -eq 0 ]] && { g++ drawTheory.C $(root-config --cflags --libs) -I"../includes/" -g -o drawTheory.exe || exit 1 ;
    echo "[Done] drawTheory.C" ; }

#
[[ $DO_PLOTTheory -eq 1 ]] && ./drawTheory.exe $CONFIG

rm drawTheory.exe 2>/dev/null
