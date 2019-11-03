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
  std::pair<std::string, exps::getdat*>("STAR_D0_RAA_pt_0-10" , new exps::getdat("dataset/dat_charmRAA/STAR_D0_RAA_pt_0-10.dat" , xjjroot::mycolor_satmiddle["cyan"], "#bf{#it{STAR} AuAu} 200 GeV" , "0-10% D^{0}" , 21, 0.07, "log")),
  std::pair<std::string, exps::getdat*>("ALICE_D_RAA_pt_0-10" , new exps::getdat("dataset/dat_charmRAA/ALICE_D_RAA_pt_0-10.dat" , xjjroot::mycolor_satmiddle["red"], "#bf{#it{ALICE} PbPb} 5 TeV" , "0-10% Average D" , 20, 0.07, "log")),
  std::pair<std::string, exps::getdat*>("CMS_D0_RAA_pt_0-10" , new exps::getdat("dataset/dat_charmRAA/CMS_D0_RAA_pt_0-10.dat" , xjjroot::mycolor_satmiddle["yellow"], "#bf{#it{CMS} PbPb} 5 TeV" , "0-10% D0" , 20, 0.07, "log")),
  std::pair<std::string, exps::getdat*>("STAR_ce_RAA_pt_0-10" , new exps::getdat("dataset/dat_charmRAA/STAR_D0_RAA_pt_0-10.dat" , xjjroot::mycolor_satmiddle["blue"], "#bf{#it{STAR} AuAu} 200 GeV" , "0-10% c#rightarrowe" , 47, 0.07, "log")),
};

void draw_charmRAA_pt(const std::vector<std::string>& idraw, std::string outname, float ymax, bool drawch=true)
{
  std::map<std::string, bool> ifdraw;
  // std::vector<std::string> legorder = {"ALICE_D_RAA_pt_0-10", "CMS_D_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10", "STAR_ce_RAA_pt_0-10"};
  std::vector<std::string> legorder = {"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10", "STAR_ce_RAA_pt_0-10"};
  exps::Ch_RAA* chRAA = new exps::Ch_RAA("dataset/dat_chRAA/Ch_RAA_pt_0-10.dat");

  for(auto& dd : dats) 
    { 
      // dd.second->setxw(0.5); 
      ifdraw[dd.first] = false;
    }
  for(auto& tt : idraw) { ifdraw[tt] = true; }

  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);R_{AA}", 10, 0.3, 200, 10, 0, ymax);
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
  c->SetLogx();
  hempty->Draw();
  if(drawch) chRAA->Draw();
  for(auto& i : idraw)
    { dats[i]->draw("f"); }
  for(auto& i : idraw)
    { dats[i]->draw("p"); }
  leg->Draw();
  xjjroot::drawline(0.3, 1, 10, 1, kBlack, 2, 2);
  gPad->RedrawAxis();
  std::string outputname = "plots/charmRAA/ccharmRAA_pt_"+outname+".pdf";
  xjjroot::mkdir(outputname.c_str());
  c->SaveAs(outputname.c_str());

  delete hempty;
  delete c;

}

int main()
{
  // draw_charmRAA_pt(std::vector<std::string>({"CMS_D0_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10", "STAR_ce_RAA_pt_0-10", "ALICE_D_RAA_pt_0-10"}), "0", 1.25);
  draw_charmRAA_pt(std::vector<std::string>({"CMS_D0_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10", "ALICE_D_RAA_pt_0-10"}), "0", 1.25, false);
  // draw_charmRAA_pt(std::vector<std::string>({"CMS_D0_RAA_pt_0-10", "ALICE_D_RAA_pt_0-10"}), "1", 1.25);
  return 0;
}

