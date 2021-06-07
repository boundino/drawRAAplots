#include <map>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"
#include "hfdata.h"
#include "dataset/Ch_v2.h"

std::map<std::string, exps::hfdata*> dats = {
  {"ALICE_D0_v2_pt_30-50"       , new exps::hfdata("dataset/dat_charmvn/ALICE_D0_v2_pt_30-50.dat"       , xjjroot::mycolor_satmiddle["orange"] , "#bf{#it{ALICE} PbPb} 5 TeV 30-50%" , "Prompt D^{0} |y| < 0.8"         , 20 , 0.4 , "linear")} ,
  {"CMS_D0_v2_pt_30-50"         , new exps::hfdata("dataset/dat_charmvn/CMS_D0_v2_pt_30-50.dat"         , xjjroot::mycolor_satmiddle["red"]    , "#bf{#it{CMS} PbPb} 5 TeV 30-50%"   , "Prompt D^{0} |y| < 1"           , 20 , 0.4 , "linear")} ,
  {"ATLAS_cm_v2_pt_30-40"       , new exps::hfdata("dataset/dat_charmvn/ATLAS_cm_v2_pt_30-40.csv"       , xjjroot::mycolor_satmiddle["violet"] , "#bf{#it{ATLAS} PbPb} 5 TeV 30-40%" , "c#rightarrow#mu |#eta| < 2"     , 20 , 0.4 , "linear")} ,
  // {"ALICE_Jpsi_v2_pt_30-50_fwd" , new exps::hfdata("dataset/dat_charmvn/ALICE_Jpsi_v2_pt_30-50_fwd.csv" , xjjroot::mycolor_satmiddle["cyan"]   , "#bf{#it{ALICE} PbPb} 5 TeV 30-50%" , "Inclusive J/#psi 2.5 < |y| < 4" , 34 , 0.4 , "linear")} ,
  {"ALICE_Jpsi_v2_pt_30-50_fwd" , new exps::hfdata("dataset/dat_charmvn/ALICE_Jpsi_v2_pt_30-50_fwd.csv" , TColor::GetColor("#00991E")   , "#bf{#it{ALICE} PbPb} 5 TeV 30-50%" , "Inclusive J/#psi 2.5 < |y| < 4" , 34 , 0.4 , "linear")} ,
  {"ALICE_Jpsi_v2_pt_30-50_mid" , new exps::hfdata("dataset/dat_charmvn/ALICE_Jpsi_v2_pt_30-50_mid.csv" , xjjroot::mycolor_light["cyan"]       , "#bf{#it{ALICE} PbPb} 5 TeV 30-50%" , "Inclusive J/#psi |y| < 0.9"     , 34 , 0.4 , "linear")} ,
  {"ATLAS_bm_v2_pt_30-40"       , new exps::hfdata("dataset/dat_beautyvn/ATLAS_bm_v2_pt_30-40.csv"      , xjjroot::mycolor_satmiddle["blue"]   , "#bf{#it{ATLAS} PbPb} 5 TeV 30-40%" , "b#rightarrow#mu |#eta| < 2"     , 21 , 0.4 , "linear")} ,
  {"ALICE_be_v2_pt_30-50"       , new exps::hfdata("dataset/dat_beautyvn/ALICE_be_v2_pt_30-50.csv"      , xjjroot::mycolor_satmiddle["azure"]  , "#bf{#it{ALICE} PbPb} 5 TeV 30-50%" , "b#rightarrowe |y| < 0.8"        , 21 , 0.4 , "linear")} ,
  {"STAR_be_v2_pt_0-80"         , new exps::hfdata("dataset/dat_beautyvn/STAR_be_v2_pt_0-80.dat"        , xjjroot::mycolor_satmiddle["green"]  , "#bf{#it{STAR} AuAu} 200 GeV 0-80%" , "b#rightarrowe"                  , 21 , 0.4 , "linear")} ,
  {"CMS_Upsilon_v2_pt_30-50"    , new exps::hfdata("dataset/dat_beautyvn/CMS_upsilon1S_v2_pt_30-50.csv" , xjjroot::mycolor_satmiddle["yellow"] , "#bf{#it{CMS} PbPb} 5 TeV 30-50%"   , "#Upsilon(1S) |y| < 2.4"         , 34 , 0.4 , "linear")} ,
};

void draw_bcv2_pt(const std::vector<std::string>& idraw, std::string outname, float xmin=0, float xmax=40)
{
  exps::Ch_v2* chv2 = new exps::Ch_v2("dataset/dat_chvn/Ch_v2_pt_30-50.dat");
  
  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);v_{2}", 10, xmin, xmax, 10, -0.03, 0.27);
  xjjroot::sethempty(hempty, 0, -0.2);
  TLegend* leg = new TLegend(0.50, 0.78-0.047*2*idraw.size()*2/3., 0.72, 0.78+0.04*2*idraw.size()*1/3.);
  xjjroot::setleg(leg, 0.038);
  for(auto& dd : idraw)
    {
      dats[dd]->setxw(0.5*(xmax-xmin)/40);
      leg->AddEntry(dats[dd]->grsyst(), dats[dd]->line1(), "fp");
      leg->AddEntry((TObject*)0, dats[dd]->line2(), NULL);
    }

  xjjroot::setgstyle(1);
  gStyle->SetPadRightMargin(xjjroot::margin_pad_right);
  gStyle->SetPadLeftMargin(xjjroot::margin_pad_left*0.7);
  gStyle->SetPadTopMargin(xjjroot::margin_pad_top*0.5);
  gStyle->SetPadBottomMargin(xjjroot::margin_pad_bottom);

  TCanvas* c = new TCanvas("c", "", 700, 600);
  // c->SetLogx();
  hempty->Draw();
  chv2->Draw();
  for(auto& i : idraw)
    { dats[i]->draw("f"); }
  for(auto& i : idraw)
    { dats[i]->draw("p"); }
  leg->Draw();
  xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 0, hempty->GetXaxis()->GetXmax(), 0, kBlack, 2, 1);
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
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "STAR_be_v2_pt_0-80", "ATLAS_bm_v2_pt_30-40", "ALICE_be_v2_pt_30-50"}), "3");
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd"}), "4");
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "CMS_Upsilon_v2_pt_30-50"}), "5");
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "CMS_Upsilon_v2_pt_30-50"}), "5_lowpt", 0, 18);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "ALICE_Jpsi_v2_pt_30-50_mid"}), "6");
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "ALICE_Jpsi_v2_pt_30-50_mid"}), "6_lowpt", 0, 18);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "ALICE_Jpsi_v2_pt_30-50_mid", "CMS_Upsilon_v2_pt_30-50"}), "7");
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "ALICE_Jpsi_v2_pt_30-50_mid", "CMS_Upsilon_v2_pt_30-50"}), "7_lowpt", 0, 18);
  draw_bcv2_pt(std::vector<std::string>({"ALICE_D0_v2_pt_30-50", "ATLAS_cm_v2_pt_30-40", "CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd"}), "8");
  return 0;
}

