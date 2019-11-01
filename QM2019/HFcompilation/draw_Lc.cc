#include <map>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"
#include "getdat.h"

std::map<std::string, exps::getdat*> dats = {
  std::pair<std::string, exps::getdat*>("ALICE_pp_5_Npart_3-4"   , new exps::getdat("dataset/dat_Lc/ALICE_pp_5_Npart_3-4.txt"   , kGray+2                          , "#bf{#it{ALICE} pp} 5 TeV"   , "3 < p_{T} < 4 GeV"    , 21)),
  std::pair<std::string, exps::getdat*>("ALICE_pp_5_Npart_2-3"   , new exps::getdat("dataset/dat_Lc/ALICE_pp_5_Npart_2-3.txt"   , kGray+2                          , "#bf{#it{ALICE} pp} 5 TeV"   , "2 < p_{T} < 3 GeV"    , 25)),
  std::pair<std::string, exps::getdat*>("ALICE_pp_5_pt"          , new exps::getdat("dataset/dat_Lc/ALICE_pp_5_pt.txt"          , kGray+2                          , "#bf{#it{ALICE} pp} 5 TeV"   , "|y| < 0.5"            , 21)),
  std::pair<std::string, exps::getdat*>("CMS_pp_5_pt"            , new exps::getdat("dataset/dat_Lc/CMS_pp_5_pt.txt"            , kGray+1                          , "#bf{#it{CMS} pp} 5 TeV"     , "|y| < 1"              , 45)),
  std::pair<std::string, exps::getdat*>("ALICE_pPb_5_Npart_4-6"  , new exps::getdat("dataset/dat_Lc/ALICE_pPb_5_Npart_4-6.txt"  , xjjroot::mycolor_satmiddle["red"]   , "#bf{#it{ALICE} pPb} 5 TeV"  , "4 < p_{T} < 6 GeV"    , 21)),
  std::pair<std::string, exps::getdat*>("ALICE_pPb_5_Npart_2-4"  , new exps::getdat("dataset/dat_Lc/ALICE_pPb_5_Npart_2-4.txt"  , xjjroot::mycolor_satmiddle["red"]   , "#bf{#it{ALICE} pPb} 5 TeV"  , "2 < p_{T} < 4 GeV"    , 25)),
  std::pair<std::string, exps::getdat*>("ALICE_pPb_5_pt"         , new exps::getdat("dataset/dat_Lc/ALICE_pPb_5_pt.txt"         , xjjroot::mycolor_satmiddle["red"]   , "#bf{#it{ALICE} pPb} 5 TeV"  , "-0.96 < y_{CM} < 0.04", 21)),
  std::pair<std::string, exps::getdat*>("LHCb_pPbB_5_pt"         , new exps::getdat("dataset/dat_Lc/LHCb_pPbB_5_pt.txt"         , xjjroot::mycolor_satmiddle["orange"], "#bf{#it{LHCb} pPb} 5 TeV"   , "-4.5 < y_{CM} < -2.5" , 46)),
  std::pair<std::string, exps::getdat*>("LHCb_pPbF_5_pt"         , new exps::getdat("dataset/dat_Lc/LHCb_pPbF_5_pt.txt"         , xjjroot::mycolor_satmiddle["orange"], "#bf{#it{LHCb} pPb} 5 TeV"   , "1.5 < y_{CM} < 4.0"   , 47)),
  std::pair<std::string, exps::getdat*>("ALICE_PbPb_5_pt_0-10"   , new exps::getdat("dataset/dat_Lc/ALICE_PbPb_5_pt_0-10.txt"   , xjjroot::mycolor_satmiddle["violet"], "#bf{#it{ALICE} PbPb} 5 TeV" , "Cent. 0-10%"          , 21)),
  std::pair<std::string, exps::getdat*>("ALICE_PbPb_5_pt_30-50"  , new exps::getdat("dataset/dat_Lc/ALICE_PbPb_5_pt_30-50.txt"  , xjjroot::mycolor_satmiddle["violet"], "#bf{#it{ALICE} PbPb} 5 TeV" , "Cent. 30-50%"         , 25)),
  std::pair<std::string, exps::getdat*>("ALICE_PbPb_5_Npart_4-6" , new exps::getdat("dataset/dat_Lc/ALICE_PbPb_5_Npart_4-6.txt" , xjjroot::mycolor_satmiddle["violet"], "#bf{#it{ALICE} PbPb} 5 TeV" , "4 < p_{T} < 6 GeV"    , 21)),
  std::pair<std::string, exps::getdat*>("ALICE_PbPb_5_Npart_2-4" , new exps::getdat("dataset/dat_Lc/ALICE_PbPb_5_Npart_2-4.txt" , xjjroot::mycolor_satmiddle["violet"], "#bf{#it{ALICE} PbPb} 5 TeV" , "2 < p_{T} < 4 GeV"    , 25)),
  std::pair<std::string, exps::getdat*>("CMS_PbPb_5_pt_0-100"    , new exps::getdat("dataset/dat_Lc/CMS_PbPb_5_pt_0-100.txt"    , xjjroot::mycolor_satmiddle["blue"]  , "#bf{#it{CMS} PbPb} 5 TeV"   , "Cent. 0-100%"         , 45)),
  std::pair<std::string, exps::getdat*>("STAR_AuAu_200_pt_10-80" , new exps::getdat("dataset/dat_Lc/STAR_AuAu_200_pt_10-80.txt" , xjjroot::mycolor_satmiddle["azure"] , "#bf{#it{STAR} AuAu} 200 GeV", "Cent. 10-80%"         , 20)),
  std::pair<std::string, exps::getdat*>("STAR_AuAu_200_Npart_3-6", new exps::getdat("dataset/dat_Lc/STAR_AuAu_200_Npart_3-6.txt", xjjroot::mycolor_satmiddle["azure"] , "#bf{#it{STAR} AuAu} 200 GeV", "3 < p_{T} < 4 GeV"    , 20))
};

void draw_Lc_pt(const std::vector<std::string>& idraw, std::string outname, float ymax)
{
  std::map<std::string, bool> ifdraw;
  for(auto& dd : dats) 
    { 
      dd.second->setxw(0.3); 
      ifdraw[dd.first] = false;
    }
  for(auto& tt : idraw) { ifdraw[tt] = true; }

  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);#Lambda_{c} / D^{0}", 10, 0, 24, 10, 0, ymax);
  xjjroot::sethempty(hempty, 0, 0);
  TLegend* legr = new TLegend(0.40, 0.85-0.04*8, 0.60, 0.85);
  xjjroot::setleg(legr, 0.03);
  TLegend* legl = new TLegend(0.67, 0.85-0.04*10, 0.87, 0.85);
  xjjroot::setleg(legl, 0.03);
  for(auto& dd : dats)
    {
      if(!xjjc::str_contains(dd.first, "pt")) continue;
      if(xjjc::str_contains(dd.first, "pp"))
        {
          if(ifdraw[dd.first]) legl->AddEntry(dd.second->grsyst(), dd.second->line1(), "fp");
          else legl->AddEntry((TObject*)0, "", NULL);
          if(ifdraw[dd.first]) legl->AddEntry((TObject*)0, dd.second->line2(), NULL);
          else legl->AddEntry((TObject*)0, "", NULL);
        }
      if(xjjc::str_contains(dd.first, "PbPb"))
        {
          if(ifdraw[dd.first]) legr->AddEntry(dd.second->grsyst(), dd.second->line1(), "fp");
          else legr->AddEntry((TObject*)0, "", NULL);
          if(ifdraw[dd.first]) legr->AddEntry((TObject*)0, dd.second->line2(), NULL);
          else legr->AddEntry((TObject*)0, "", NULL);
        }
    }
  for(auto& dd : dats)
    {
      if(!xjjc::str_contains(dd.first, "pt")) continue;
      if(xjjc::str_contains(dd.first, "pPb"))
        {
          if(ifdraw[dd.first]) legl->AddEntry(dd.second->grsyst(), dd.second->line1(), "fp");
          else legl->AddEntry((TObject*)0, "", NULL);
          if(ifdraw[dd.first]) legl->AddEntry((TObject*)0, dd.second->line2(), NULL);
          else legl->AddEntry((TObject*)0, "", NULL);
        }
      if(xjjc::str_contains(dd.first, "AuAu"))
        {
          if(ifdraw[dd.first]) legr->AddEntry(dd.second->grsyst(), dd.second->line1(), "fp");
          else legr->AddEntry((TObject*)0, "", NULL);
          if(ifdraw[dd.first]) legr->AddEntry((TObject*)0, dd.second->line2(), NULL);
          else legr->AddEntry((TObject*)0, "", NULL);
        }
    }

  xjjroot::setgstyle(1);
  TCanvas* c = new TCanvas("c", "", 600, 600);
  hempty->Draw();
  for(auto& i : idraw)
    { dats[i]->draw(); }
  legl->Draw();
  legr->Draw();
  std::string outputname = "plots/Lc/cLc_pt_"+outname+".pdf";
  xjjroot::mkdir(outputname.c_str());
  c->SaveAs(outputname.c_str());

  delete hempty;
  delete c;

}

void draw_Lc_Npart(const std::vector<std::string>& idraw, std::string outname, float ymax)
{
  std::map<std::string, bool> ifdraw;
  for(auto& dd : dats) 
    { 
      dd.second->setxw(7); 
      ifdraw[dd.first] = false;
    }
  for(auto& tt : idraw) { ifdraw[tt] = true; }

  TH2F* hempty = new TH2F("hempty", ";N_{part};#Lambda_{c} / D^{0}", 10, -10, 410, 10, 0, ymax);
  xjjroot::sethempty(hempty, 0, 0);
  TLegend* leg1 = new TLegend(0.22, 0.86-0.04*4, 0.22+0.23, 0.86);
  xjjroot::setleg(leg1, 0.03);
  TLegend* leg2 = new TLegend(0.45, 0.86-0.04*2, 0.45+0.23, 0.86);
  xjjroot::setleg(leg2, 0.03);
  TLegend* leg3 = new TLegend(0.57, 0.18, 0.57+0.23, 0.18+0.04*4);
  xjjroot::setleg(leg3, 0.03);
  TLegend* leg4 = new TLegend(0.34, 0.18, 0.34+0.23, 0.18+0.04*4);
  xjjroot::setleg(leg4, 0.03);
  for(auto& dd : dats)
    {
      if(!xjjc::str_contains(dd.first, "Npart")) continue;
      if(xjjc::str_contains(dd.first, "pPb"))
        {
          if(ifdraw[dd.first]) leg1->AddEntry(dd.second->grsyst(), dd.second->line1(), "fp");
          else leg1->AddEntry((TObject*)0, "", NULL);
          if(ifdraw[dd.first]) leg1->AddEntry((TObject*)0, dd.second->line2(), NULL);
          else leg1->AddEntry((TObject*)0, "", NULL);
        }
      if(xjjc::str_contains(dd.first, "pp"))
        {
          if(ifdraw[dd.first]) leg4->AddEntry(dd.second->grsyst(), dd.second->line1(), "fp");
          else leg4->AddEntry((TObject*)0, "", NULL);
          if(ifdraw[dd.first]) leg4->AddEntry((TObject*)0, dd.second->line2(), NULL);
          else leg4->AddEntry((TObject*)0, "", NULL);
        }
      if(xjjc::str_contains(dd.first, "AuAu"))
        {
          if(ifdraw[dd.first]) leg2->AddEntry(dd.second->grsyst(), dd.second->line1(), "fp");
          else leg2->AddEntry((TObject*)0, "", NULL);
          if(ifdraw[dd.first]) leg2->AddEntry((TObject*)0, dd.second->line2(), NULL);
          else leg2->AddEntry((TObject*)0, "", NULL);
        }
      if(xjjc::str_contains(dd.first, "PbPb"))
        {
          if(ifdraw[dd.first]) leg3->AddEntry(dd.second->grsyst(), dd.second->line1(), "fp");
          else leg3->AddEntry((TObject*)0, "", NULL);
          if(ifdraw[dd.first]) leg3->AddEntry((TObject*)0, dd.second->line2(), NULL);
          else leg3->AddEntry((TObject*)0, "", NULL);
        }
    }

  xjjroot::setgstyle(1);
  TCanvas* c = new TCanvas("c", "", 600, 600);
  hempty->Draw();
  for(auto& i : idraw)
    { dats[i]->draw(); }
  leg1->Draw();
  leg2->Draw();
  leg3->Draw();
  leg4->Draw();
  std::string outputname = "plots/Lc/cLc_Npart_"+outname+".pdf";
  xjjroot::mkdir(outputname.c_str());
  c->SaveAs(outputname.c_str());

  delete hempty;
  delete c;

}

int main()
{
  draw_Lc_pt(std::vector<std::string>({"ALICE_pp_5_pt", "CMS_pp_5_pt", "LHCb_pPbB_5_pt", "LHCb_pPbF_5_pt", "ALICE_PbPb_5_pt_0-10", "ALICE_PbPb_5_pt_30-50", "ALICE_pPb_5_pt", "CMS_PbPb_5_pt_0-100", "STAR_AuAu_200_pt_10-80"}), "0", 2.2);
  draw_Lc_pt(std::vector<std::string>({"ALICE_PbPb_5_pt_0-10", "ALICE_PbPb_5_pt_30-50", "CMS_PbPb_5_pt_0-100", "STAR_AuAu_200_pt_10-80"}), "1", 2.2);
  draw_Lc_pt(std::vector<std::string>({"ALICE_pp_5_pt", "CMS_pp_5_pt", "ALICE_PbPb_5_pt_0-10", "ALICE_PbPb_5_pt_30-50", "CMS_PbPb_5_pt_0-100", "STAR_AuAu_200_pt_10-80"}), "2", 2.2);
  draw_Lc_pt(std::vector<std::string>({"ALICE_pp_5_pt", "CMS_pp_5_pt", "ALICE_PbPb_5_pt_0-10", "ALICE_PbPb_5_pt_30-50", "ALICE_pPb_5_pt", "CMS_PbPb_5_pt_0-100", "STAR_AuAu_200_pt_10-80"}), "3", 2.2);
  draw_Lc_pt(std::vector<std::string>({"ALICE_pp_5_pt", "CMS_pp_5_pt", "ALICE_PbPb_5_pt_0-10", "ALICE_PbPb_5_pt_30-50", "ALICE_pPb_5_pt", "CMS_PbPb_5_pt_0-100"}), "4", 1.2);
  draw_Lc_pt(std::vector<std::string>({"LHCb_pPbB_5_pt", "LHCb_pPbF_5_pt", "ALICE_pPb_5_pt"}), "5", 0.85);
  // draw_Lc_pt(std::vector<std::string>({"ALICE_pp_5_pt", "CMS_pp_5_pt", "LHCb_pPbB_5_pt", "LHCb_pPbF_5_pt", "ALICE_PbPb_5_pt_0-10", "ALICE_PbPb_5_pt_30-50", "ALICE_pPb_5_pt", "CMS_PbPb_5_pt_0-100"}), "5", 1.2);

  draw_Lc_Npart(std::vector<std::string>({"ALICE_pp_5_Npart_2-3", "ALICE_pp_5_Npart_3-4", "ALICE_pPb_5_Npart_2-4", "ALICE_pPb_5_Npart_4-6", "STAR_AuAu_200_Npart_3-6", "ALICE_PbPb_5_Npart_2-4", "ALICE_PbPb_5_Npart_4-6"}), "0", 2.0);
  draw_Lc_Npart(std::vector<std::string>({"STAR_AuAu_200_Npart_3-6", "ALICE_PbPb_5_Npart_2-4", "ALICE_PbPb_5_Npart_4-6"}), "1", 2.0);
  draw_Lc_Npart(std::vector<std::string>({"ALICE_pp_5_Npart_2-3", "ALICE_pp_5_Npart_3-4", "STAR_AuAu_200_Npart_3-6", "ALICE_PbPb_5_Npart_2-4", "ALICE_PbPb_5_Npart_4-6"}), "2", 2.0);
  draw_Lc_Npart(std::vector<std::string>({"ALICE_pp_5_Npart_2-3", "ALICE_pp_5_Npart_3-4", "ALICE_pPb_5_Npart_2-4", "ALICE_pPb_5_Npart_4-6", "STAR_AuAu_200_Npart_3-6", "ALICE_PbPb_5_Npart_2-4", "ALICE_PbPb_5_Npart_4-6"}), "3", 2.0);
  return 0;
}


// using namespace std::literals::string_literal;
// auto str = "hello"s;
