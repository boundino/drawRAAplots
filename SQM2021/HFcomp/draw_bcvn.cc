#include <map>
#include <string>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "xjjrootuti.h"
#include "xjjcuti.h"
#include "hfdata.h"
#include "dataset/Ch_v2.h"
#include "vn.h"

void draw_bcv2_pt(const std::vector<std::string>& idraw, std::string outname, bool charged=true, bool logx=false, float xmin=0, float xmax=40)
{
  exps::Ch_v2* chv2 = new exps::Ch_v2("dataset/dat_chvn/Ch_v2_pt_30-50.dat");
  
  TH2F* hempty = new TH2F("hempty", ";p_{T} (GeV/c);v_{2}", 10, xmin, xmax, 10, -0.03, 0.27);
  xjjroot::sethempty(hempty, 0, -0.2);
  TLegend* leg = new TLegend(0.50, 0.78-0.047*2*idraw.size()*2/3., 0.72, 0.78+0.04*2*idraw.size()*1/3.);
  xjjroot::setleg(leg, 0.038);
  for(auto& dd : idraw)
    {
      dats[dd]->setxw(0.5*(xmax-xmin)/40, logx);
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
  draw_bcv2_pt(std::vector<std::string>({"ALICE_D0_v2_pt_30-50", "CMS_D0_v2_pt_30-50"}), "charm_1", false);
  draw_bcv2_pt(std::vector<std::string>({"ATLAS_cm_v2_pt_30-40", "CMS_D0_v2_pt_30-50"}), "charm_2", false);
  draw_bcv2_pt(std::vector<std::string>({"ALICE_D0_v2_pt_30-50", "ATLAS_cm_v2_pt_30-40", "CMS_D0_v2_pt_30-50"}), "charm_3", false);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "STAR_be_v2_pt_0-80", "ATLAS_bm_v2_pt_30-40", "ALICE_be_v2_pt_30-50"}), "bc_1", true);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd"}), "bc_2", true);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "CMS_Upsilon_v2_pt_30-50"}), "bc_3", true);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "ALICE_Jpsi_v2_pt_30-50_mid"}), "bc_4", true);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40", "ALICE_Jpsi_v2_pt_30-50_fwd", "ALICE_Jpsi_v2_pt_30-50_mid", "CMS_Upsilon_v2_pt_30-50"}), "bc_5", true);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ATLAS_bm_v2_pt_30-40"}), "bc_6", true);
  draw_bcv2_pt(std::vector<std::string>({"CMS_D0_v2_pt_30-50", "ALICE_Jpsi_v2_pt_30-50_fwd"}), "bc_7", true);
  return 0;
}

