#include <map>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"
#include "hfdata.h"
#include "dataset/Ch_RAA.h"

std::map<std::string, exps::hfdata*> dats = {
  std::pair<std::string , exps::hfdata*>("ALICE_D_RAA_pt_0-10"    , new exps::hfdata("dataset/dat_charmRAA/ALICE_D_RAA_pt_0-10.dat"     , xjjroot::mycolor_satmiddle["azure"]    , "#bf{#it{ALICE} PbPb} 5 TeV"  , "0-10% Prompt D"             , 20 , 0.07 , "log")) ,
  std::pair<std::string , exps::hfdata*>("CMS_D0_RAA_pt_0-10"     , new exps::hfdata("dataset/dat_charmRAA/CMS_D0_RAA_pt_0-10.dat"      , xjjroot::mycolor_satmiddle["greenblue"] , "#bf{#it{CMS} PbPb} 5 TeV"    , "0-10% Prompt D^{0}"         , 20 , 0.07 , "log")) ,
  std::pair<std::string , exps::hfdata*>("STAR_D0_RAA_pt_0-10"    , new exps::hfdata("dataset/dat_charmRAA/STAR_D0_RAA_pt_0-10.dat"     , xjjroot::mycolor_satmiddle["orange"]   , "#bf{#it{STAR} AuAu} 200 GeV" , "0-10% Prompt D^{0}"         , 20 , 0.07 , "log")) ,
  std::pair<std::string , exps::hfdata*>("ALICE_npD_RAA_pt_0-10"  , new exps::hfdata("dataset/dat_beautyRAA/ALICE_npD_RAA_pt_0-10.dat"  , xjjroot::mycolor_satmiddle["violet"]   , "#bf{#it{ALICE} PbPb} 5 TeV"  , "0-10% (b#rightarrow)D^{0}"  , 21 , 0.07 , "log")) ,
  std::pair<std::string , exps::hfdata*>("CMS_npJpsi_RAA_pt_0-10" , new exps::hfdata("dataset/dat_beautyRAA/CMS_npJpsi_RAA_pt_0-10.dat" , xjjroot::mycolor_satmiddle["red"]   , "#bf{#it{CMS} PbPb} 5 TeV"    , "0-10% (b#rightarrow)J/#psi" , 21 , 0.07 , "log")) ,
};

void draw_bcRAA_pt(const std::vector<std::string>& idraw, std::string outname, bool drawch, float xmin=0.3, float xmax=150)
{
  exps::Ch_RAA* chRAA = new exps::Ch_RAA("dataset/dat_chRAA/Ch_RAA_pt_0-10.dat");

  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);R_{AA}", 10, xmin, xmax, 10, 0, 1.6);
  xjjroot::sethempty(hempty, 0, -0.2);
  TLegend* leg = new TLegend(0.36, 0.82-0.047*idraw.size()*2/3., 0.60, 0.82+0.047*idraw.size()*1/3.);
  xjjroot::setleg(leg, 0.038);
  for(auto& dd : idraw)
    {
      if(dats[dd]->log()) dats[dd]->setxw(0.07);
      else dats[dd]->setxw(0.5*(xmax-xmin)/40);
      leg->AddEntry(dats[dd]->grsyst(), Form("%s, %s", dats[dd]->line1(), dats[dd]->line2()), "fp");
    }

  xjjroot::setgstyle(2);
  gStyle->SetPadRightMargin(xjjroot::margin_pad_right);
  gStyle->SetPadLeftMargin(xjjroot::margin_pad_left*0.7);
  gStyle->SetPadTopMargin(xjjroot::margin_pad_top*0.5);
  gStyle->SetPadBottomMargin(xjjroot::margin_pad_bottom);

  TCanvas* c = new TCanvas("c", "", 700, 600);
  c->SetLogx();
  hempty->Draw();
  if(drawch) chRAA->Draw();
  for(auto& i : idraw)
    { dats[i]->draw("f"); }
  for(auto& i : idraw)
    { dats[i]->draw("p"); }
  leg->Draw();
  xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 1, hempty->GetXaxis()->GetXmax(), 1, kBlack, 2, 2);
  gPad->RedrawAxis();
  std::string outputname = "plots/bcRAA/cbcRAA_pt_"+outname+".pdf";
  xjjroot::mkdir(outputname.c_str());
  c->SaveAs(outputname.c_str());

  delete hempty;
  delete c;

}

int main()
{
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10"}), "charm_0", false);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "ALICE_npD_RAA_pt_0-10", "CMS_npJpsi_RAA_pt_0-10"}), "bc_0", true);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "CMS_npJpsi_RAA_pt_0-10"}), "bc_1", true);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "ALICE_npD_RAA_pt_0-10"}), "bc_2", true);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10"}), "bc_3", true);
  return 0;
}

