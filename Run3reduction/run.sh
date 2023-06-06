#!/bin/bash

CONFIG=configs/run3reduction.conf
DO_PLOTTheory=${1:-0}
DO_PLOTXsig=${2:-0}

#
echo "compiling..."
[[ $DO_PLOTTheory -eq 1 || $# -eq 0 ]] && { g++ drawTheory.C $(root-config --cflags --libs) -I"../includes/" -g -o drawTheory.exe || exit 1 ;
    echo "[Done] drawTheory.C" ; }
[[ $DO_PLOTXsig -eq 1 || $# -eq 0 ]] && { g++ drawXsig.C $(root-config --cflags --libs) -I"../includes/" -g -o drawXsig.exe || exit 1 ;
    echo "[Done] drawXsig.C" ; }

#
[[ $DO_PLOTTheory -eq 1 ]] && ./drawTheory.exe $CONFIG
[[ $DO_PLOTXsig -eq 1 ]] && ./drawXsig.exe $CONFIG

rm drawTheory.exe 2>/dev/null
rm drawXsig.exe 2>/dev/null
