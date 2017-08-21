#!/bin/bash

if [ ! -d "plotRAA" ]
then
    mkdir -p "plotRAA"
fi

#
g++ CombineRAA.C $(root-config --cflags --libs) -g -o CombineRAA.exe || return 1 

#

CENTPbPbMIN=0
CENTPbPbMAX=100
OUTPUTFILERAA="ROOTfiles/outputRAA.root"
OUTPUTFILERAAMB="ROOTfiles/outputRAAMB.root"

set -x

./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 0 0
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 1 0 0 
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 1 0

set +x

CENTPbPbMIN=0
CENTPbPbMAX=10
OUTPUTFILERAA="ROOTfilesCent10/outputRAA.root"
OUTPUTFILERAAMB="ROOTfilesCent10/outputRAAMB.root"

set -x

./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 0 0
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 0 0 0
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 0 1
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 1 0

set +x

rm CombineRAA.exe


