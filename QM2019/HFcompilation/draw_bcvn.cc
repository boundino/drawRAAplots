#include <map>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"
#include "getdat.h"
#include "Ch_v2.h"

std::map<std::string, exps::getdat*> dats = {
  std::pair<std::string, exps::getdat*>("ALICE_D0_v2_pt_30-50" , new exps::getdat("dataset/dat_charmvn/ALICE_D0_v2_pt_30-50.dat" , xjjroot::mycolor_satmiddle["yellow"], "#bf{#it{ALICE} PbPb} 5 TeV" , "30-50% Prompt D^{0}" , 20, 0.4, "linear")),
  std::pair<std::string, exps::getdat*>("CMS_D0_v2_pt_30-50" , new exps::getdat("dataset/dat_charmvn/CMS_D0_v2_pt_30-50.dat" , xjjroot::mycolor_satmiddle["red"], "#bf{#it{CMS} PbPb} 5 TeV" , "30-50% Prompt D^{0}" , 20, 0.4, "linear")),
  std::pair<std::string, exps::getdat*>("ALICE_Jpsi_v2_pt_30-50" , new exps::getdat("dataset/dat_charmvn/ALICE_Jpsi_v2_pt_30-50.dat" , xjjroot::mycolor_satmiddle["green"], "#bf{#it{ALICE} PbPb} 5 TeV" , "30-50% J/#psi" , 47, 0.4, "linear")),
  std::pair<std::string, exps::getdat*>("ATLAS_cm_v2_pt_30-40" , new exps::getdat("dataset/dat_charmvn/ATLAS_cm_v2_pt_30-40.dat" , xjjroot::mycolor_satmiddle["violet"], "#bf{#it{ATLAS} PbPb} 5 TeV" , "30-40% c#rightarrow#mu" , 21, 0.4, "linear")),
  std::pair<std::string, exps::getdat*>("ATLAS_bm_v2_pt_30-40" , new exps::getdat("dataset/dat_beautyvn/ATLAS_bm_v2_pt_30-40.dat" , xjjroot::mycolor_satmiddle["blue"], "#bf{#it{ATLAS} PbPb} 5 TeV" , "30-40% b#rightarrow#mu" , 21, 0.4, "linear")),
  std::pair<std::string, exps::getdat*>("STAR_be_v2_pt_0-80" , new exps::getdat("dataset/dat_beautyvn/STAR_be_v2_pt_0-80.dat" , xjjroot::mycolor_satmiddle["cyan"], "#bf{#it{STAR} AuAu} 200 GeV" , "0-80% b#rightarrowe" , 21, 0.4, "linear")),
};

void draw_bcv2_pt(const std::vector<std::string>& idraw, std::string outname)
{
  std::map<std::string, bool> ifdraw;
  std::vector<std::string> legorder = {"ATLAS_cm_v2_pt_30-40", "ALICE_D0_v2_pt_30-50", "CMS_D0_v2_pt_30-50", "ALICE_Jpsi_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "STAR_be_v2_pt_0-80"};
  exps::Ch_v2* chv2 = new exps::Ch_v2("dataset/dat_chvn/Ch_v2_pt_30-50.dat");
  
  for(auto& dd : dats) 
    { 
      // dd.second->setmarkersize(1.3); 
      ifdraw[dd.first] = false;
    }
  for(auto& tt : idraw) { ifdraw[tt] = true; }

  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);v_{2}", 10, 0, 40, 10, -0.03, 0.27);
  xjjroot::sethempty(hempty, 0, 0);
  TLegend* leg = new TLegend(0.60, 0.85-0.04*12, 0.80, 0.85);
  xjjroot::setleg(leg, 0.03);
  for(auto& dd : legorder)
    {
      if(ifdraw[dd]) leg->AddEntry(dats[dd]->grsyst(), dats[dd]->line1(), "fp");
      else leg->AddEntry((TObject*)0, "", NULL);
      if(ifdraw[dd]) leg->AddEntry((TObject*)0, dats[dd]->line2(), NULL);
      else leg->AddEntry((TObject*)0, "", NULL);
    }

  xjjroot::setgstyle(1);
  TCanvas* c = new TCanvas("c", "", 600, 600);
  // c->SetLogx();
  hempty->Draw();
  chv2->Draw();
  for(auto& i : idraw)
    { dats[i]->draw("f"); }
  for(auto& i : idraw)
    { dats[i]->draw("p"); }
  leg->Draw();
  xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 0, hempty->GetXaxis()->GetXmax(), 0, kBlack, 2, 2);
  gPad->RedrawAxis();
  std::string outputname = "plots/bcv2/cbcv2_pt_"+outname+".pdf";
  xjjroot::mkdir(outputname.c_str());
  c->SaveAs(outputname.c_str());

  delete hempty;
  delete c;

}

int main()
{
  draw_bcv2_pt(std::vector<std::string>({"ALICE_D0_v2_pt_30-50", "CMS_D0_v2_pt_30-50"}), "0");
  draw_bcv2_pt(std::vector<std::string>({"ALICE_D0_v2_pt_30-50", "ATLAS_cm_v2_pt_30-40", "CMS_D0_v2_pt_30-50"}), "1");
  draw_bcv2_pt(std::vector<std::string>({"ATLAS_cm_v2_pt_30-40", "CMS_D0_v2_pt_30-50"}), "2");
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "STAR_be_v2_pt_0-80"}), "3");
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50", "ALICE_Jpsi_v2_pt_30-50"}), "4");
  draw_bcv2_pt(std::vector<std::string>({"ALICE_D0_v2_pt_30-50", "ATLAS_cm_v2_pt_30-40", "CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50"}), "5");
  // draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ALICE_Jpsi_v2_pt_30-50"}), "0");
  return 0;
}

