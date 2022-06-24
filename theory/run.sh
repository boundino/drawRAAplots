#!/bin/bash

CONFIG=configs/hfwinc22.conf
DO_PLOTTheory=${1:-0}
# DO_PLOTRAA=${1:-0}
# DO_PLOTV2=${2:-0}

#
echo "compiling..."
# [[ $DO_PLOTRAA -eq 1 || $# -eq 0 ]] && { g++ plotRAA.C $(root-config --cflags --libs) -I"../includes/" -g -o plotRAA.exe || exit 1 ;
#     echo "[Done] plotRAA.C" ; }
# [[ $DO_PLOTV2 -eq 1 || $# -eq 0 ]] && { g++ plotV2.C $(root-config --cflags --libs) -I"../includes/" -g -o plotV2.exe || exit 1 ;
#     echo "[Done] plotV2.C" ; }
[[ $DO_PLOTTheory -eq 1 || $# -eq 0 ]] && { g++ drawTheory.C $(root-config --cflags --libs) -I"../includes/" -g -o drawTheory.exe || exit 1 ;
    echo "[Done] drawTheory.C" ; }

#
# [[ $DO_PLOTRAA -eq 1 ]] && ./plotRAA.exe $CONFIG
# [[ $DO_PLOTV2 -eq 1 ]] && ./plotV2.exe $CONFIG
[[ $DO_PLOTTheory -eq 1 ]] && ./drawTheory.exe $CONFIG

rm plotRAA.exe 2>/dev/null 
rm plotV2.exe 2>/dev/null
rm drawTheory.exe 2>/dev/null
