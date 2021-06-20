#!/bin/bash

input=(
    # "dat_charmvn/ALICE_D_v2_pt_0-10.csv:B[]PLB 813 (2021) 136054[]v2[]pT[]Prompt D[]PbPb[]5 TeV[]ALICE[]0-10%[]|y| < 0.8[][]https://arxiv.org/abs/2005.11131"
    # "dat_charmvn/ALICE_D_v2_pt_30-50.csv:B[]PLB 813 (2021) 136054[]v2[]pT[]Prompt D[]PbPb[]5 TeV[]ALICE[]30-50%[]|y| < 0.8[][]https://arxiv.org/abs/2005.11131"
    # "dat_charmvn/ALICE_D_v3_pt_0-10.csv:B[]PLB 813 (2021) 136054[]v3[]pT[]Prompt D[]PbPb[]5 TeV[]ALICE[]0-10%[]|y| < 0.8[][]https://arxiv.org/abs/2005.11131"
    # "dat_charmvn/ALICE_D_v3_pt_30-50.csv:B[]PLB 813 (2021) 136054[]v3[]pT[]Prompt D[]PbPb[]5 TeV[]ALICE[]30-50%[]|y| < 0.8[][]https://arxiv.org/abs/2005.11131"
    # "dat_charmvn/ALICE_Jpsi_v2_pt_0-10_y2p5-4.csv[]JHEP 10 (2020) 141[]v2[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]0-10%[]2.5 < |y| < 4[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v2_pt_10-30_y2p5-4.csv[]JHEP 10 (2020) 141[]v2[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]10-30%[]2.5 < |y| < 4[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v2_pt_30-50_y2p5-4.csv[]JHEP 10 (2020) 141[]v2[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]30-50%[]2.5 < |y| < 4[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v2_pt_0-50_y2p5-4.csv[]JHEP 10 (2020) 141[]v2[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]0-50%[]2.5 < |y| < 4[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v2_pt_0-10_y0p9.csv[]JHEP 10 (2020) 141[]v2[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]0-10%[]|y| < 0.9[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v2_pt_30-50_y0p9.csv[]JHEP 10 (2020) 141[]v2[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]30-50%[]|y| < 0.9[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v3_pt_0-10_y2p5-4.csv[]JHEP 10 (2020) 141[]v3[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]0-10%[]2.5 < |y| < 4[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v3_pt_10-30_y2p5-4.csv[]JHEP 10 (2020) 141[]v3[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]10-30%[]2.5 < |y| < 4[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v3_pt_30-50_y2p5-4.csv[]JHEP 10 (2020) 141[]v3[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]30-50%[]2.5 < |y| < 4[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_Jpsi_v3_pt_0-50_y2p5-4.csv[]JHEP 10 (2020) 141[]v3[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]0-50%[]2.5 < |y| < 4[][]https://arxiv.org/abs/2005.14518"
    # "dat_charmvn/ALICE_cbe_v2_pt_pPb.csv:B[]PRL 122 (2019) 072301[]v2[]pT[](c,b&rarr;) e[]pPb[]5 TeV[]ALICE[][]|&eta;| < 0.8[][]https://arxiv.org/abs/1805.04367"
    # "dat_charmvn/ATLAS_cm_v2_pt_0-10.csv[]PLB 807 (2020) 135595[]v2[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]0-10%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v2_pt_10-20.csv[]PLB 807 (2020) 135595[]v2[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]10-20%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v2_pt_20-30.csv[]PLB 807 (2020) 135595[]v2[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]20-30%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v2_pt_30-40.csv[]PLB 807 (2020) 135595[]v2[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]30-40%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v2_pt_40-60.csv[]PLB 807 (2020) 135595[]v2[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]40-60%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v3_pt_0-10.csv[]PLB 807 (2020) 135595[]v3[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]0-10%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v3_pt_10-20.csv[]PLB 807 (2020) 135595[]v3[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]10-20%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v3_pt_20-30.csv[]PLB 807 (2020) 135595[]v3[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]20-30%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v3_pt_30-40.csv[]PLB 807 (2020) 135595[]v3[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]30-40%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_cm_v3_pt_40-60.csv[]PLB 807 (2020) 135595[]v3[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]40-60%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_charmvn/ATLAS_Jpsi_v2_pt_0-60.dat[]EPJC 78 (2018) 784[]v2[]pT[]Prompt J/&psi;[]PbPb[]5 TeV[]ATLAS[]0-60%[]|y| < 2[][]https://arxiv.org/abs/1807.05198"
    # "dat_charmvn/ATLAS_cm_v2_pt_pp.csv[]PRL 124 (2020) 082301[]v2[]pT[](c&rarr;) &mu;[]pp[]13 TeV[]ATLAS[][]|&eta;| < 2.4[][]https://arxiv.org/abs/1909.01650"
    "dat_charmvn/CMS_D0_v2_pt_0-10_y1.csv[]PLB 816 (2021) 136253[]v2[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]0-10%[]|y| < 1[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v2_pt_10-30_y1.csv[]PLB 816 (2021) 136253[]v2[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]10-30%[]|y| < 1[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v2_pt_30-50_y1.csv[]PLB 816 (2021) 136253[]v2[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]30-50%[]|y| < 1[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v2_pt_0-10_y1-2.csv[]PLB 816 (2021) 136253[]v2[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]0-10%[]1 < |y| < 2[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v2_pt_10-30_y1-2.csv[]PLB 816 (2021) 136253[]v2[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]10-30%[]1 < |y| < 2[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v2_pt_30-50_y1-2.csv[]PLB 816 (2021) 136253[]v2[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]30-50%[]1 < |y| < 2[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v3_pt_0-10_y1.csv[]PLB 816 (2021) 136253[]v3[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]0-10%[]|y| < 1[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v3_pt_10-30_y1.csv[]PLB 816 (2021) 136253[]v3[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]10-30%[]|y| < 1[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v3_pt_30-50_y1.csv[]PLB 816 (2021) 136253[]v3[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]30-50%[]|y| < 1[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v3_pt_0-10_y1-2.csv[]PLB 816 (2021) 136253[]v3[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]0-10%[]1 < |y| < 2[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v3_pt_10-30_y1-2.csv[]PLB 816 (2021) 136253[]v3[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]10-30%[]1 < |y| < 2[][]https://arxiv.org/abs/2009.12628"
    "dat_charmvn/CMS_D0_v3_pt_30-50_y1-2.csv[]PLB 816 (2021) 136253[]v3[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]30-50%[]1 < |y| < 2[][]https://arxiv.org/abs/2009.12628"
    # "dat_charmvn/CMS_D0_v2_pt_pPb.csv[]PRL 121 (2018) 082301[]v2[]pT[]Prompt D&#8304;[]pPb[]8 TeV[]CMS[][]|y| < 1[][]https://arxiv.org/abs/1804.09767"
    # "dat_charmvn/CMS_D0_v2_pt_pp.dat[]PLB 813 (2021) 136036[]v2[]pT[]Prompt D&#8304;[]pp[]13 TeV[]CMS[][]|y| < 1[][]https://arxiv.org/abs/2009.07065"
    # "dat_charmvn/CMS_Jpsi_v2_pt_pPb.dat[]PLB 791 (2019) 172[]v2[]pT[]Prompt J/&psi;[]pPb[]8 TeV[]CMS[][]|y| < 2.4[][]https://arxiv.org/abs/1810.01473"
    # "dat_charmvn/STAR_D0_v2_pt_0-80.csv[]PRL 118 (2017) 212301[]v2[]pT[]D&#8304;[]AuAu[]200 GeV[]STAR[]0-80%[]|y| < 1[][]https://arxiv.org/abs/1701.06060"
    # "dat_charmvn/STAR_D0_v2_pt_10-40.csv[]PRL 118 (2017) 212301[]v2[]pT[]D&#8304;[]AuAu[]200 GeV[]STAR[]10-40%[]|y| < 1[][]https://arxiv.org/abs/1701.06060"

    # "dat_beautyvn/ALICE_be_v2_pt_30-50.csv[]PRL 126 (2021) 162001[]v2[]pT[](b&rarr;) e[]PbPb[]5 TeV[]ALICE[]30-50%[]|y| < 0.8[][]https://arxiv.org/abs/2005.11130"
    # "dat_beautyvn/ALICE_Upsilon1S_v2_pt_5-60.csv:B[]PRL 123 (2019) 192301[]v2[]pT[]&Upsilon;(1S)[]PbPb[]5 TeV[]ALICE[]5-60%[]2.5 < |y| < 4[][]https://arxiv.org/abs/1907.03169"
    # "dat_charmvn/ALICE_Jpsi_v2_pt_5-60_y2p5-4.csv:B[]PRL 123 (2019) 192301[]v2[]pT[]Inclusive J/&psi;[]PbPb[]5 TeV[]ALICE[]5-60%[]2.5 < |y| < 4[][]https://arxiv.org/abs/1907.03169"
    # "dat_beautyvn/ATLAS_bm_v2_pt_0-10.csv[]PLB 807 (2020) 135595[]v2[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]0-10%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v2_pt_10-20.csv[]PLB 807 (2020) 135595[]v2[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]10-20%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v2_pt_20-30.csv[]PLB 807 (2020) 135595[]v2[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]20-30%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v2_pt_30-40.csv[]PLB 807 (2020) 135595[]v2[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]30-40%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v2_pt_40-60.csv[]PLB 807 (2020) 135595[]v2[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]40-60%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v3_pt_0-10.csv[]PLB 807 (2020) 135595[]v3[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]0-10%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v3_pt_10-20.csv[]PLB 807 (2020) 135595[]v3[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]10-20%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v3_pt_20-30.csv[]PLB 807 (2020) 135595[]v3[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]20-30%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v3_pt_30-40.csv[]PLB 807 (2020) 135595[]v3[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]30-40%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v3_pt_40-60.csv[]PLB 807 (2020) 135595[]v3[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]40-60%[]|&eta;| < 2[][]https://arxiv.org/abs/2003.03565"
    # "dat_beautyvn/ATLAS_bm_v2_pt_pp.csv[]PRL 124 (2020) 082301[]v2[]pT[](b&rarr;) &mu;[]pp[]13 TeV[]ATLAS[][]|&eta;| < 2.4[][]https://arxiv.org/abs/1909.01650"
    # "dat_beautyvn/ATLAS_npJpsi_v2_pt_0-60.dat[]EPJC 78 (2018) 784[]v2[]pT[](b&rarr;) J/&psi;[]PbPb[]5 TeV[]ATLAS[]0-60%[]|y| < 2[][]https://arxiv.org/abs/1807.05198"
    # "dat_beautyvn/CMS_Upsilon1S_v2_pt_10-30.csv:B[]PLB 819 (2021) 136385[]v2[]pT[]&Upsilon;(1S)[]PbPb[]5 TeV[]CMS[]10-30%[]|y| < 2.4[][]https://arxiv.org/abs/2006.07707"
    # "dat_beautyvn/CMS_Upsilon1S_v2_pt_30-50.csv:B[]PLB 819 (2021) 136385[]v2[]pT[]&Upsilon;(1S)[]PbPb[]5 TeV[]CMS[]30-50%[]|y| < 2.4[][]https://arxiv.org/abs/2006.07707"
    # "dat_beautyvn/CMS_Upsilon1S_v2_pt_50-90.csv:B[]PLB 819 (2021) 136385[]v2[]pT[]&Upsilon;(1S)[]PbPb[]5 TeV[]CMS[]50-90%[]|y| < 2.4[][]https://arxiv.org/abs/2006.07707"
    # "dat_beautyvn/CMS_Upsilon1S_v2_pt_5-60.csv:B[]PLB 819 (2021) 136385[]v2[]pT[]&Upsilon;(1S)[]PbPb[]5 TeV[]CMS[]5-60%[]|y| < 2.4[][]https://arxiv.org/abs/2006.07707"
    # "dat_beautyvn/CMS_npD_v2_pt_pPb.dat[]PLB 813 (2021) 136036[]v2[]pT[](b&rarr;) D&#8304;[]pPb[]8 TeV[]CMS[][]|y| < 1[][]https://arxiv.org/abs/2009.07065"

    # "dat_chvn/CMS_Ks_v2_pt_pPb.csv[]PRL 121 (2018) 082301[]v2[]pT[]Ks0[]pPb[]8 TeV[]CMS[][]|y| < 1[][]https://arxiv.org/abs/1804.09767"

    # "dat_charmRAA/ALICE_D_RAA_pt_0-10.dat[]ALICE Preliminary[]RAA[]pT[]Prompt D[]PbPb[]5 TeV[]ALICE[]0-10%[]|y| < 0.5[][]https://alice-figure.web.cern.ch/node/15443"
    # "dat_charmRAA/CMS_D0_RAA_pt_0-10.csv:B[]PLB 782 (2018) 474[]RAA[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]0-10%[]|y| < 1[][]https://arxiv.org/abs/1708.04962"
    # "dat_charmRAA/CMS_D0_RAA_pt_0-100.csv:B[]PLB 782 (2018) 474[]RAA[]pT[]Prompt D&#8304;[]PbPb[]5 TeV[]CMS[]0-100%[]|y| < 1[][]https://arxiv.org/abs/1708.04962"
    # "dat_charmRAA/CMS_pJpsi_RAA_pt_0-100_y0p6.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[]Prompt J/&psi;[]PbPb[]5 TeV[]CMS[]0-100%[]|y| < 0.6[][]https://arxiv.org/abs/1712.08959"
    # "dat_charmRAA/CMS_pJpsi_RAA_pt_0-100_y1p8-2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[]Prompt J/&psi;[]PbPb[]5 TeV[]CMS[]0-100%[]1.8 < |y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_charmRAA/CMS_pJpsi_RAA_pt_0-100_y2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[]Prompt J/&psi;[]PbPb[]5 TeV[]CMS[]0-100%[]|y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_charmRAA/CMS_pJpsi_RAA_pt_0-10_y2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[]Prompt J/&psi;[]PbPb[]5 TeV[]CMS[]0-10%[]|y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_charmRAA/CMS_pJpsi_RAA_pt_10-30_y2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[]Prompt J/&psi;[]PbPb[]5 TeV[]CMS[]10-30%[]|y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_charmRAA/CMS_pJpsi_RAA_pt_30-100_y2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[]Prompt J/&psi;[]PbPb[]5 TeV[]CMS[]30-100%[]|y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_charmRAA/STAR_D0_RAA_pt_0-10.dat[]PRC 99 (2019) 034908[]RAA[]pT[]Prompt D&#8304;[]AuAu[]200 GeV[]STAR[]0-10%[]|y| < 1[][]https://arxiv.org/abs/1812.10224"
    # "dat_charmRAA/STAR_D0_RAA_pt_10-40.dat[]PRC 99 (2019) 034908[]RAA[]pT[]Prompt D&#8304;[]AuAu[]200 GeV[]STAR[]10-40%[]|y| < 1[][]https://arxiv.org/abs/1812.10224"
    # "dat_charmRAA/STAR_D0_RAA_pt_40-80.dat[]PRC 99 (2019) 034908[]RAA[]pT[]Prompt D&#8304;[]AuAu[]200 GeV[]STAR[]40-80%[]|y| < 1[][]https://arxiv.org/abs/1812.10224"
    # "dat_charmRAA/ATLAS_cm_RAA_pt_0-10.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]0-10%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_charmRAA/ATLAS_cm_RAA_pt_10-20.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]10-20%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_charmRAA/ATLAS_cm_RAA_pt_20-30.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]20-30%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_charmRAA/ATLAS_cm_RAA_pt_30-40.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]30-40%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_charmRAA/ATLAS_cm_RAA_pt_40-60.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](c&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]40-60%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_charmRAA/STAR_ce_RAA_pt_0-80.dat[]STAR Preliminary[]RAA[]pT[](c&rarr;) e[]AuAu[]200 GeV[]STAR[]0-80%[]|&eta;| < 1[][]https://indico.cern.ch/event/985652/contributions/4305124/attachments/2245001/3810816/HFE_for_SQM2021_v6.pdf"

    # "dat_beautyRAA/CMS_npD_RAA_pt_0-100.csv:B[]PRL 123 (2019) 022001[]RAA[]pT[](b&rarr;) D&#8304;[]PbPb[]5 TeV[]CMS[]0-100%[]|y| < 1[][]https://arxiv.org/abs/1810.11102"
    # "dat_beautyRAA/CMS_npJpsi_RAA_pt_0-100_y0p6.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[](b&rarr;) J/&psi;[]PbPb[]5 TeV[]CMS[]0-100%[]|y| < 0.6[][]https://arxiv.org/abs/1712.08959"
    # "dat_beautyRAA/CMS_npJpsi_RAA_pt_0-100_y1p8-2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[](b&rarr;) J/&psi;[]PbPb[]5 TeV[]CMS[]0-100%[]1.8 < |y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_beautyRAA/CMS_npJpsi_RAA_pt_0-100_y2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[](b&rarr;) J/&psi;[]PbPb[]5 TeV[]CMS[]0-100%[]|y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_beautyRAA/CMS_npJpsi_RAA_pt_0-10_y2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[](b&rarr;) J/&psi;[]PbPb[]5 TeV[]CMS[]0-10%[]|y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_beautyRAA/CMS_npJpsi_RAA_pt_10-30_y2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[](b&rarr;) J/&psi;[]PbPb[]5 TeV[]CMS[]10-30%[]|y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_beautyRAA/CMS_npJpsi_RAA_pt_30-100_y2p4.csv:B[]EPJC 78 (2018) 509[]RAA[]pT[](b&rarr;) J/&psi;[]PbPb[]5 TeV[]CMS[]30-100%[]|y| < 2.4[][]https://arxiv.org/abs/1712.08959"
    # "dat_beautyRAA/STAR_be_RAA_pt_0-80.dat[]STAR Preliminary[]RAA[]pT[](b&rarr;) e[]AuAu[]200 GeV[]STAR[]0-80%[]|&eta;| < 1[][]https://indico.cern.ch/event/792436/contributions/3535848/attachments/1938681/3213669/Kelsey_QM2019.pdf"
    # "dat_beautyRAA/CMS_Bp_RAA_pt_0-100.dat[]PRL 119 (2017) 152301[]RAA[]pT[]B&#8314;[]PbPb[]5 TeV[]CMS[]0-100%[]|y| < 2.4[][]https://arxiv.org/abs/1705.04727"
    # "dat_beautyRAA/ALICE_npD_RAA_pt_0-10.dat[]ALICE Preliminary[]RAA[]pT[](b&rarr;) D&#8304;[]PbPb[]5 TeV[]ALICE[]0-10%[]|y| < 0.5[][]https://alice-figure.web.cern.ch/node/16423"
    # "dat_beautyRAA/ALICE_be_RAA_pt_0-10.dat[]ALICE Preliminary[]RAA[]pT[](b&rarr;) e[]PbPb[]5 TeV[]ALICE[]0-10%[]|y| < 0.8[][]https://alice-figure.web.cern.ch/node/13142"
    # "dat_beautyRAA/ATLAS_bm_RAA_pt_0-10.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]0-10%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_beautyRAA/ATLAS_bm_RAA_pt_0-10.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]0-10%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_beautyRAA/ATLAS_bm_RAA_pt_10-20.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]10-20%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_beautyRAA/ATLAS_bm_RAA_pt_20-30.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]20-30%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_beautyRAA/ATLAS_bm_RAA_pt_30-40.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]30-40%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"
    # "dat_beautyRAA/ATLAS_bm_RAA_pt_40-60.dat[]ATLAS-CONF-2021-020[]RAA[]pT[](b&rarr;) &mu;[]PbPb[]5 TeV[]ATLAS[]40-60%[]|&eta;| < 2[][]https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-020/"

    # "dat_chRAA/CMS_Ch_RAA_pt_0-100.csv:B S4[]JHEP 04 (2017) 039[]RAA[]pT[]Light h&plusmn;[]PbPb[]5 TeV[]CMS[]0-100%[]|y| < 1[][]https://arxiv.org/abs/1611.01664"
    # "dat_chRAA/CMS_Ch_RAA_pt_0-10.csv:B S4[]JHEP 04 (2017) 039[]RAA[]pT[]Light h&plusmn;[]PbPb[]5 TeV[]CMS[]0-10%[]|y| < 1[][]https://arxiv.org/abs/1611.01664"
    # "dat_chRAA/CMS_Ch_RAA_pt_10-30.csv:B S4[]JHEP 04 (2017) 039[]RAA[]pT[]Light h&plusmn;[]PbPb[]5 TeV[]CMS[]10-30%[]|y| < 1[][]https://arxiv.org/abs/1611.01664"
    # "dat_chRAA/CMS_Ch_RAA_pt_30-50.csv:B S4[]JHEP 04 (2017) 039[]RAA[]pT[]Light h&plusmn;[]PbPb[]5 TeV[]CMS[]30-50%[]|y| < 1[][]https://arxiv.org/abs/1611.01664"
    # "dat_chRAA/CMS_Ch_RAA_pt_50-70.csv:B S4[]JHEP 04 (2017) 039[]RAA[]pT[]Light h&plusmn;[]PbPb[]5 TeV[]CMS[]50-70%[]|y| < 1[][]https://arxiv.org/abs/1611.01664"
)

g++ getjs.cc $(root-config --libs --cflags) -I"../includes/" -g -o getjs.exe || exit 1

for i in "${input[@]}"
do
    ./getjs.exe "$i"
done

rm getjs.exe


# CMS 
