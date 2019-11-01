#include <map>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"
#include "getdat.h"

std::map<std::string, exps::getdat*> dats = {
  std::pair<std::string, exps::getdat*>("STAR_D0_RAA_pt_0-10" , new exps::getdat("dataset/dat_charmRAA/STAR_D0_RAA_pt_0-10.dat" , xjjroot::mycolor_satmiddle["orange"], "#bf{#it{STAR} AuAu} 200 GeV" , "0-10% D^{0}" , 21, 0.5, "log")),
  std::pair<std::string, exps::getdat*>("ALICE_D_RAA_pt_0-10" , new exps::getdat("dataset/dat_charmRAA/ALICE_D_RAA_pt_0-10.dat" , xjjroot::mycolor_satmiddle["red"], "#bf{#it{ALICE} AuAu} 5 TeV" , "0-10% Average D" , 20, 0.5, "log")),
};

void draw_charmRAA_pt(const std::vector<std::string>& idraw, std::string outname, float ymax)
{
  std::map<std::string, bool> ifdraw;
  // std::vector<std::string> datorder = {"ALICE_D_RAA_pt_0-10", "CMS_D_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10", "STAR_ce_RAA_pt_0-10"};
  std::vector<std::string> datorder = {"ALICE_D_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10"};
  for(auto& dd : dats) 
    { 
      dd.second->setxw(0.3); 
      ifdraw[dd.first] = false;
    }
  for(auto& tt : idraw) { ifdraw[tt] = true; }

  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);R_{AA}", 10, 0.1, 200, 10, 0, ymax);
  xjjroot::sethempty(hempty, 0, 0);
  TLegend* leg = new TLegend(0.40, 0.85-0.04*8, 0.60, 0.85);
  xjjroot::setleg(leg, 0.03);
  for(auto& dd : datorder)
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
  for(auto& i : idraw)
    { dats[i]->draw(); }
  leg->Draw();
  std::string outputname = "plots/charmRAA/ccharmRAA_pt_"+outname+".pdf";
  xjjroot::mkdir(outputname.c_str());
  c->SaveAs(outputname.c_str());

  delete hempty;
  delete c;

}

int main()
{
  draw_charmRAA_pt(std::vector<std::string>({"STAR_D0_RAA_pt_0-10", "ALICE_D_RAA_pt_0-10"}), "0", 1.25);
  return 0;
}

