#include <map>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"
#include "hfdata.h"
#include "dataset/Ch_RAA.h"
#include "RAA.h"

void draw_bcRAA_pt(const std::vector<std::string>& idraw, std::string outname, bool drawch, bool logx, float xmin=0.3, float xmax=150)
{
  exps::Ch_RAA* chRAA = new exps::Ch_RAA("dataset/dat_chRAA/Ch_RAA_pt_0-10.dat");

  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);R_{AA}", 10, xmin, xmax, 10, 0, 1.6);
  xjjroot::sethempty(hempty, 0, -0.2);
  TLegend* leg = new TLegend(0.36, 0.82-0.047*idraw.size()*2/3., 0.60, 0.82+0.047*idraw.size()*1/3.);
  xjjroot::setleg(leg, 0.038);
  for(auto& dd : idraw)
    {
      if(logx) dats[dd]->setxw(0.07, logx);
      else dats[dd]->setxw(0.4*(xmax-xmin)/40, logx);
      leg->AddEntry(dats[dd]->grsyst(), Form("%s, %s", dats[dd]->line1(), dats[dd]->line2()), "fp");
    }

  xjjroot::setgstyle(2);
  gStyle->SetPadRightMargin(xjjroot::margin_pad_right);
  gStyle->SetPadLeftMargin(xjjroot::margin_pad_left*0.7);
  gStyle->SetPadTopMargin(xjjroot::margin_pad_top*0.5);
  gStyle->SetPadBottomMargin(xjjroot::margin_pad_bottom);

  TCanvas* c = new TCanvas("c", "", 700, 600);
  if(logx) c->SetLogx();
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
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "ALICE_npD_RAA_pt_0-10", "CMS_npJpsi_RAA_pt_0-10"}), "bc_0", true, true);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "CMS_npJpsi_RAA_pt_0-10"}), "bc_1", true, true);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "ALICE_npD_RAA_pt_0-10"}), "bc_2", true, true);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10"}), "bc_3", true, true);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "ATLAS_cm_RAA_pt_0-10", "ATLAS_bm_RAA_pt_0-10"}), "bc_4", false, true, 1, 150);

  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10"}), "charm_0", false, true);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_D_RAA_pt_0-10", "CMS_D0_RAA_pt_0-10", "ATLAS_cm_RAA_pt_0-10", "STAR_D0_RAA_pt_0-10"}), "charm_1", false, true);

  draw_bcRAA_pt(std::vector<std::string>({"CMS_npD_RAA_pt_0-100", "CMS_npJpsi_RAA_pt_0-100", "STAR_be_RAA_pt_0-80", "CMS_Bp_RAA_pt_0-100"}), "beauty_0-100", false, false, 0, 60);
  draw_bcRAA_pt(std::vector<std::string>({"ALICE_npD_RAA_pt_0-10", "CMS_npJpsi_RAA_pt_0-10", "ALICE_be_RAA_pt_0-10", "ATLAS_bm_RAA_pt_0-10"}), "beauty_0-10", false, false, 0, 30);
  return 0;
}

