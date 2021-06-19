
std::map<std::string, exps::hfdata*> dats = {
  // charm
  std::pair<std::string, exps::hfdata*>("ALICE_D_RAA_pt_0-10", new exps::hfdata("dataset/dat_charmRAA/ALICE_D_RAA_pt_0-10.dat", xjjroot::mycolor_satmiddle["azure"], 
                                                                                "#bf{#it{ALICE} PbPb} 5 TeV", "0-10% Prompt D", 21)),
  std::pair<std::string, exps::hfdata*>("CMS_D0_RAA_pt_0-10", new exps::hfdata("dataset/dat_charmRAA/CMS_D0_RAA_pt_0-10.dat", xjjroot::mycolor_satmiddle["greenblue"], 
                                                                               "#bf{#it{CMS} PbPb} 5 TeV", "0-10% Prompt D^{0}", 21)),
  std::pair<std::string, exps::hfdata*>("STAR_D0_RAA_pt_0-10", new exps::hfdata("dataset/dat_charmRAA/STAR_D0_RAA_pt_0-10.dat", xjjroot::mycolor_satmiddle["orange"], 
                                                                                "#bf{#it{STAR} AuAu} 200 GeV", "0-10% Prompt D^{0}", 21)),
  std::pair<std::string, exps::hfdata*>("ATLAS_cm_RAA_pt_0-10", new exps::hfdata("dataset/dat_charmRAA/ATLAS_cm_RAA_pt_0-10.dat", xjjroot::mycolor_satmiddle["violet"], 
                                                                                 "#bf{#it{ATLAS} PbPb} 5 TeV", "0-10% c#rightarrow#mu", 20)),
  // beauty 0-100%
  std::pair<std::string, exps::hfdata*>("CMS_npD_RAA_pt_0-100", new exps::hfdata("dataset/dat_beautyRAA/CMS_npD_RAA_pt_0-100.dat", xjjroot::mycolor_satmiddle["blue"], 
                                                                                 "#bf{#it{CMS} PbPb} 5 TeV", "0-100% (b#rightarrow)D^{0}", 47)),
  std::pair<std::string, exps::hfdata*>("CMS_npJpsi_RAA_pt_0-100", new exps::hfdata("dataset/dat_beautyRAA/CMS_npJpsi_RAA_pt_0-100.dat", xjjroot::mycolor_satmiddle["red"], 
                                                                                    "#bf{#it{CMS} PbPb} 5 TeV", "0-100% (b#rightarrow)J/#psi", 47)),
  std::pair<std::string, exps::hfdata*>("STAR_be_RAA_pt_0-80", new exps::hfdata("dataset/dat_beautyRAA/STAR_be_RAA_pt_0-80.dat", xjjroot::mycolor_satmiddle["orange"], 
                                                                                "#bf{#it{STAR} AuAu} 200 GeV", "0-80% b(#rightarrowc)#rightarrowe", 20)),
  std::pair<std::string, exps::hfdata*>("CMS_Bp_RAA_pt_0-100", new exps::hfdata("dataset/dat_beautyRAA/CMS_Bp_RAA_pt_0-100.dat", xjjroot::mycolor_satmiddle["violet"], 
                                                                                "#bf{#it{CMS} PbPb} 5 TeV", "0-100% B^{+}", 21)),
  // beauty 0-10%
  std::pair<std::string, exps::hfdata*>("ALICE_npD_RAA_pt_0-10", new exps::hfdata("dataset/dat_beautyRAA/ALICE_npD_RAA_pt_0-10.dat", xjjroot::mycolor_satmiddle["blue"], 
                                                                                  "#bf{#it{ALICE} PbPb} 5 TeV", "0-10% (b#rightarrow)D^{0}", 47)),
  std::pair<std::string, exps::hfdata*>("CMS_npJpsi_RAA_pt_0-10", new exps::hfdata("dataset/dat_beautyRAA/CMS_npJpsi_RAA_pt_0-10.dat", xjjroot::mycolor_satmiddle["red"], 
                                                                                   "#bf{#it{CMS} PbPb} 5 TeV", "0-10% (b#rightarrow)J/#psi", 47)),
  std::pair<std::string, exps::hfdata*>("ALICE_be_RAA_pt_0-10", new exps::hfdata("dataset/dat_beautyRAA/ALICE_be_RAA_pt_0-10.dat", xjjroot::mycolor_satmiddle["orange"], 
                                                                                 "#bf{#it{ALICE} PbPb} 5 TeV", "0-10% b(#rightarrowc)#rightarrowe", 20)),
  std::pair<std::string, exps::hfdata*>("ATLAS_bm_RAA_pt_0-10", new exps::hfdata("dataset/dat_beautyRAA/ATLAS_bm_RAA_pt_0-10.dat", xjjroot::mycolor_satmiddle["magenta"], 
                                                                                 "#bf{#it{ATLAS} PbPb} 5 TeV", "0-10% b(#rightarrowc)#rightarrow#mu", 20)),
};
