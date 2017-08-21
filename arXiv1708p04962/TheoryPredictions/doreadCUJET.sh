
INPUT=("CUJET_5.02TeV_D0_RAA_0-10.dat" "CUJET_5.02TeV_D0_RAA_0-100.dat")
OUTPUT=("CUJET_D0_RAA_0_10.root" "CUJET_D0_RAA_0_100.root")
nPUT=${#INPUT[@]}

i=0
while ((i<$nPUT))
do
    root -b -q readCUJETnew.cc+(\"${INPUT[i]}\",\"${OUTPUT[i]}\")
    i=$(($i+1))
done