#include <map>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"
#include "getdat.h"
#include "Ch_RAA.h"

std::map<std::string, exps::getdat*> dats = {
  std::pair<std::string, exps::getdat*>("CMS_npJpsi_RAA_pt_0-100" , new exps::getdat("dataset/dat_beautyRAA/CMS_npJpsi_RAA_pt_0-100.dat" , xjjroot::mycolor_satmiddle["greenblue"], "#bf{#it{CMS} PbPb} 5 TeV" , "0-100% (b#rightarrow)J/#psi" , 20, 0.6, "linear")),
  std::pair<std::string, exps::getdat*>("CMS_npD_RAA_pt_0-100" , new exps::getdat("dataset/dat_beautyRAA/CMS_npD_RAA_pt_0-100.dat" , xjjroot::mycolor_satmiddle["blue"], "#bf{#it{CMS} PbPb} 5 TeV" , "0-100% (b#rightarrow)D^{0}" , 20, 0.6, "linear")),
  std::pair<std::string, exps::getdat*>("CMS_Bp_RAA_pt_0-100" , new exps::getdat("dataset/dat_beautyRAA/CMS_Bp_RAA_pt_0-100.dat" , xjjroot::mycolor_satmiddle["yellow"], "#bf{#it{CMS} PbPb} 5 TeV" , "0-100% B^{+}" , 20, 0.6, "linear")),
  std::pair<std::string, exps::getdat*>("STAR_be_RAA_pt_0-80" , new exps::getdat("dataset/dat_beautyRAA/STAR_be_RAA_pt_0-80.dat" , xjjroot::mycolor_satmiddle["orange"], "#bf{#it{STAR} AuAu} 200 GeV" , "0-80% b(#rightarrowc)#rightarrowe" , 21, 0.6, "linear")),
};

void draw_beautyRAA_pt(const std::vector<std::string>& idraw, std::string outname, float ymax)
{
  std::map<std::string, bool> ifdraw;
  std::vector<std::string> legorder = {"CMS_npD_RAA_pt_0-100", "CMS_npJpsi_RAA_pt_0-100", "STAR_be_RAA_pt_0-80", "CMS_Bp_RAA_pt_0-100"};

  for(auto& dd : dats) 
    { 
      dd.second->setxw(0.6); 
      ifdraw[dd.first] = false;
    }
  for(auto& tt : idraw) { ifdraw[tt] = true; }

  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);R_{AA}", 10, 0, 60, 10, 0, ymax);
  xjjroot::sethempty(hempty, 0, 0);
  TLegend* leg = new TLegend(0.60, 0.85-0.04*8, 0.80, 0.85);
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
  for(auto& i : idraw)
    { dats[i]->draw("f"); }
  for(auto& i : idraw)
    { dats[i]->draw("p"); }
  leg->Draw();
  xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 1, 30., 1, kBlack, 2, 2);
  gPad->RedrawAxis();
  std::string outputname = "plots/beautyRAA/cbeautyRAA_0-100_pt_"+outname+".pdf";
  xjjroot::mkdir(outputname.c_str());
  c->SaveAs(outputname.c_str());

  delete hempty;
  delete c;

}

int main()
{
  draw_beautyRAA_pt(std::vector<std::string>({"CMS_npD_RAA_pt_0-100", "CMS_Bp_RAA_pt_0-100", "CMS_npJpsi_RAA_pt_0-100", "STAR_be_RAA_pt_0-80"}), "0", 1.4);
  return 0;
}

