#!/bin/bash

# #!/usr/local/bin/bash

[[ ${1:-0} -eq 1 ]] && {
    g++ draw_bcRAA.cc -I"includes/" $(root-config --libs --cflags) -g -o draw_bcRAA.exe || exit 1
    ./draw_bcRAA.exe
    rm draw_bcRAA.exe
}

[[ ${2:-0} -eq 1 ]] && {
    g++ draw_bcvn.cc -I"includes/" $(root-config --libs --cflags) -g -o draw_bcvn.exe || exit 1
    ./draw_bcvn.exe
    rm draw_bcvn.exe
}

[[ ${3:-0} -eq 1 ]] && {
    g++ draw_Lc.cc -I"includes/" $(root-config --libs --cflags) -g -o draw_Lc.exe || exit 1
    ./draw_Lc.exe
    rm draw_Lc.exe
}

set +x
