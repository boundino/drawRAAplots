#!/bin/bash

FOLDERS=("plotRAA" "plotCrossSection")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]
    then
        mkdir -p $i
    fi
done

g++ CombineCrossSections.C $(root-config --cflags --libs) -g -o CombineCrossSections.exe
g++ CombineRAA.C $(root-config --cflags --libs) -g -o CombineRAA.exe 

OUTPUTFILEPlotPP="ROOTfiles/CrossSectionFONLLPP.root"
OUTPUTFILEPlotPPMB="ROOTfiles/CrossSectionFONLLPPMB.root"

set -x

./CombineCrossSections.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPP" "0"

set +x

CENTPbPbMIN=0
CENTPbPbMAX=100
OUTPUTFILERAA="ROOTfiles/outputRAA.root"
OUTPUTFILERAAMB="ROOTfiles/outputRAAMB.root"

set -x

./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 0 
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 1
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 1

set +x

CENTPbPbMAX=10
OUTPUTFILERAA="ROOTfilesCent10/outputRAA.root"
OUTPUTFILERAAMB="ROOTfilesCent10/outputRAAMB.root"

set -x

./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 0 
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 1
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 1

rm CombineRAA.exe
rm CombineCrossSections.exe

set +x

