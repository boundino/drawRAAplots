#!/bin/bash

FILEPP=rootfiles/xsec_Djet_pp_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng
FILEPbPb=rootfiles/xsec_Djet_PbPb_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng
FILERatio=rootfiles/ratio_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng
FILEPythia=rootfiles/xsec_Djet_pppythiaRaw_woCorr_Signal_MC_GenD_GenJet_jetpt_60p0_999p0_jeteta_0p0_1p6_noHLT_woScale_woSmearPt_woSmearAng_noDweight
OUTPUT=Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng

mkdir -p plotfinal
g++ djtana_finalplot.C $(root-config --cflags --libs) -g -o djtana_finalplot.exe || return 1
./djtana_finalplot.exe $FILEPP $FILEPbPb $FILERatio $OUTPUT 60 999 0.0 1.6 1 $FILEPythia

FIGARCHIVE=(../../plotArchive/figsup ../../plotArchive/figs)
for i in ${FIGARCHIVE[@]}; do mkdir -p $i ; done ;

PLOTSUP=(
    # "plotfitspaper/cmasspaper_Djet_PbPb_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng_eta_pt_1_dr_1.pdf"
    # "plotfitspaper/cmasspaper_Djet_pp_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng_eta_pt_1_dr_1.pdf"
    # "plotxsecspaper/cxsec_dr_Djet_PbPb_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng_pt_0_Me.pdf"
    # "plotxsecspaper/cxsecsub_dr_Djet_PbPb_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng_pt_0_Me.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_dNdronly.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_dNdronly.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_ratioonly.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_ratioonly.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_dNdrratio.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_dNdrratio.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_dNdrpythia.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_dNdrpythia.pdf"
)
PLOTPAPER=(
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_pythia.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_pythia.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_pythia_pre.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_pythia_pre.pdf"
)

for i in ${PLOTSUP[@]}
do 
    filename=${i//"6__w"/"6___w"}
    filename=${filename##*/}
    cp $i ../../plotArchive/figsup/${filename//"_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_"/"-"}
done
for i in ${PLOTPAPER[@]}
do 
    filename=${i//"6__w"/"6___w"}
    filename=${filename##*/}
    cp $i ../../plotArchive/figs/${filename//"_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_"/"-"}
done

rm djtana_finalplot.exe
rm -r plotfinal
echo "----------------"$'\n'"Figures in: "`readlink -f ../../plotArchive`$'\n'"----------------"
