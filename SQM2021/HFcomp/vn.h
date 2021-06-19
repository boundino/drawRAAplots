
std::map<std::string, exps::hfdata*> dats = {
  {"ALICE_D0_v2_pt_30-50", new exps::hfdata("dataset/dat_charmvn/ALICE_D0_v2_pt_30-50.dat", xjjroot::mycolor_satmiddle["orange"], 
                                            "#bf{#it{ALICE} PbPb} 5 TeV 30-50%", "Prompt D^{0} |y| < 0.8", 20)},
  {"CMS_D0_v2_pt_30-50", new exps::hfdata("dataset/dat_charmvn/CMS_D0_v2_pt_30-50.dat", xjjroot::mycolor_satmiddle["red"], 
                                          "#bf{#it{CMS} PbPb} 5 TeV 30-50%", "Prompt D^{0} |y| < 1", 20)},
  {"ATLAS_cm_v2_pt_30-40", new exps::hfdata("dataset/dat_charmvn/ATLAS_cm_v2_pt_30-40.csv", xjjroot::mycolor_satmiddle["violet"], 
                                            "#bf{#it{ATLAS} PbPb} 5 TeV 30-40%", "c#rightarrow#mu |#eta| < 2", 20)},
  {"ALICE_Jpsi_v2_pt_30-50_fwd", new exps::hfdata("dataset/dat_charmvn/ALICE_Jpsi_v2_pt_30-50_fwd.csv", TColor::GetColor("#00991E"), // xjjroot::mycolor_satmiddle["cyan"]
                                                  "#bf{#it{ALICE} PbPb} 5 TeV 30-50%", "Inclusive J/#psi 2.5 < |y| < 4", 34)},
  {"ALICE_Jpsi_v2_pt_30-50_mid", new exps::hfdata("dataset/dat_charmvn/ALICE_Jpsi_v2_pt_30-50_mid.csv", xjjroot::mycolor_light["cyan"], 
                                                  "#bf{#it{ALICE} PbPb} 5 TeV 30-50%", "Inclusive J/#psi |y| < 0.9", 34)},
  {"ATLAS_bm_v2_pt_30-40", new exps::hfdata("dataset/dat_beautyvn/ATLAS_bm_v2_pt_30-40.csv", xjjroot::mycolor_satmiddle["blue"], 
                                            "#bf{#it{ATLAS} PbPb} 5 TeV 30-40%", "b#rightarrow#mu |#eta| < 2", 21)},
  {"ALICE_be_v2_pt_30-50", new exps::hfdata("dataset/dat_beautyvn/ALICE_be_v2_pt_30-50.csv", xjjroot::mycolor_satmiddle["azure"], 
                                            "#bf{#it{ALICE} PbPb} 5 TeV 30-50%", "b#rightarrowe |y| < 0.8", 21)},
  {"STAR_be_v2_pt_0-80", new exps::hfdata("dataset/dat_beautyvn/STAR_be_v2_pt_0-80.dat", xjjroot::mycolor_satmiddle["green"], 
                                          "#bf{#it{STAR} AuAu} 200 GeV 0-80%", "b#rightarrowe", 21)},
  {"CMS_Upsilon_v2_pt_30-50", new exps::hfdata("dataset/dat_beautyvn/CMS_upsilon1S_v2_pt_30-50.csv", xjjroot::mycolor_satmiddle["yellow"], 
                                               "#bf{#it{CMS} PbPb} 5 TeV 30-50%", "#Upsilon(1S) |y| < 2.4", 34)},
};
