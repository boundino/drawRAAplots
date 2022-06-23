#include "hfdata.h"
#include "xjjcuti.h"
#include "xjjrootuti.h"
#include "config.h"

#include <string>
#include <vector>
#include <map>

#include <TCanvas.h>
#include <TH2F.h>

std::map<std::string, std::string> legentry = {
  {"v2_charge_pT", ""},
  {"v2_promptD_pT", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v2_promptJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v2_promptJpsi_pT_high", "|y| < 2.4"},
  {"v2_btoD_pT", "#bf{(b #rightarrow) D^{0}}, |y| < 1"},
  {"v2_btoJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v2_btoJpsi_pT_high", "|y| < 2.4"},
  {"v2_Upsilon_pT", "#bf{#Upsilon(1S)}, |y| < 2.4"},
  {"v2_promptD_cent", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v2_promptJpsi_cent", "#bf{Prompt J/#psi}, |y| < 2.4"},
  {"v2_btoJpsi_cent", "#bf{(b#rightarrow) J/#psi}, |y| < 2.4"},
  {"vn_v2_promptD_cent", "v_{2}"},
  {"vn_v2_promptJpsi_cent", "v_{2}"},
  {"vn_v2_btoJpsi_cent", "v_{2}"},
  {"v3_promptD_cent", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v3_promptJpsi_cent", "#bf{Prompt J/#psi}, |y| < 2.4"},
  {"v3_btoJpsi_cent", "#bf{(b#rightarrow) J/#psi}, |y| < 2.4"},
  {"vn_v3_promptD_cent", "v_{3}"},
  {"vn_v3_promptJpsi_cent", "v_{3}"},
  {"vn_v3_btoJpsi_cent", "v_{3}"},
  {"v2_promptD_pT_CMS_30_50", "Prompt D^{0} #bf{CMS}, |y| < 1"},
  {"v2_cmu_pT_ATLAS", "(c #rightarrow) #mu #bf{ATLAS}, |#eta| < 2"},
  {"v2_promptD_pT_ALICE", "Prompt D #bf{ALICE}, |y| < 0.8"},
  {"v2_promptD_pT_CMS_10_30", "Prompt D^{0} #bf{CMS}, |y| < 1"},
  {"v2_inclD_pT_STAR", "Inclusive D^{0} #bf{STAR}, |y| < 1"},
  {"v3_charge_pT", ""},
  {"v3_promptD_pT", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v3_promptJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v3_promptJpsi_pT_high", "|y| < 2.4"},
  {"v3_btoD_pT", "#bf{(b #rightarrow) D^{0}}, |y| < 1"},
  {"v3_btoJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v3_btoJpsi_pT_high", "|y| < 2.4"},
  {"v3_promptD_pT_CMS", "Prompt D^{0} #bf{CMS}, |y| < 1"},
  {"v3_cmu_pT_ATLAS", "(c #rightarrow) #mu #bf{ATLAS}, |#eta| < 2"},
};
std::map<std::string, exps::hfdata*> dats;
TCanvas* c;
float tsize = 0.035, lspace = 0.045;

void drawhempty(TH2F* hempty, int logx, std::string prel="Preliminary");
void drawpoints(std::vector<std::string> list);
void drawleg(std::vector<std::string> list, float legl, float legt, float legscale=1.);

int draw_v2_PbPb(std::string input="configs/input_v2_PbPb.conf")
{
  xjjc::config* conf = new xjjc::config(input);
  for(auto& ll : legentry)
    {
      auto t = ll.first;
      if(!conf->goodkey(t)) continue;
      dats[t] = new exps::hfdata(Form("%s", conf->vv(t)[0].c_str()), atoi(conf->vv(t)[1].c_str()), "", "", atoi(conf->vv(t)[2].c_str()));
    }
  dats["v2_charge_pT"]->grsyst()->SetLineWidth(0);
  dats["v2_charge_pT"]->grsyst()->SetFillColorAlpha(atoi(conf->vv("v2_charge_pT")[1].c_str()), 0.2);
  dats["v3_charge_pT"]->grsyst()->SetLineWidth(0);
  dats["v3_charge_pT"]->grsyst()->SetFillColorAlpha(atoi(conf->vv("v3_charge_pT")[1].c_str()), 0.2);

  //
  TH2F* hempty_v2_pt = new TH2F("hempty_v2_pt", ";p_{T} (GeV/c);v_{2}", 10, 1, 60, 10, -0.06, 0.27);
  TH2F* hempty_v2_cent = new TH2F("hempty_v2_cent", ";Centrality (\%);v_{2}", 10, 0, 90, 10, -0.06, 0.27);
  TH2F* hempty_vn_cent = new TH2F("hempty_vn_cent", ";Centrality (\%);v_{n}", 10, 0, 90, 10, -0.06, 0.27);
  TH2F* hempty_v3_pt = new TH2F("hempty_v3_pt", ";p_{T} (GeV/c);v_{3}", 10, 1, 60, 10, -0.04, 0.15);

  xjjroot::setgstyle(1);
  xjjroot::mkdir("plots/x");

  // vs. pT: LHC
  drawhempty(hempty_v2_pt, 1, "");
  drawpoints({"v2_cmu_pT_ATLAS", "v2_promptD_pT_ALICE", "v2_promptD_pT_CMS_30_50"});
  drawleg({"v2_promptD_pT_CMS_30_50", "v2_promptD_pT_ALICE", "v2_cmu_pT_ATLAS", "Cent. 30-40\%"}, 0.50, 0.84);
  xjjroot::drawtex(0.55, 0.23, "Cent. 30-50\%", tsize);
  xjjroot::drawtex(0.23, 0.79, "#it{Open charm}"); 
  c->SaveAs("plots/v2_PbPb_pT_charmLHC.pdf");
  delete c;

  // vs. pT: LHC vs. RHIC
  drawhempty(hempty_v2_pt, 1, "");
  drawpoints({"v2_inclD_pT_STAR", "v2_promptD_pT_CMS_10_30"});
  drawleg({"v2_promptD_pT_CMS_10_30", "v2_inclD_pT_STAR", "Cent. 10-40\%"}, 0.50, 0.84);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  xjjroot::drawtex(0.23, 0.79, "#it{Open charm}"); 
  c->SaveAs("plots/v2_PbPb_pT_charmLHCvsRHIC.pdf");
  delete c;

  // vs. pT: h, prompt D, bto D, bto Jpsi
  drawhempty(hempty_v2_pt, 1);
  drawpoints({"v2_charge_pT", "v2_promptD_pT", "v2_btoD_pT", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high"});
  drawleg({"v2_promptD_pT", "v2_btoD_pT", "", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high"}, 0.60, 0.82);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_h-promptD-btoD-btoJpsi.pdf");
  delete c;

  // vs. pT: h, prompt D, prompt Jpsi
  drawhempty(hempty_v2_pt, 1);
  drawpoints({"v2_charge_pT", "v2_promptD_pT", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high"});
  drawleg({"v2_promptD_pT", "", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high"}, 0.60, 0.82);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_h-promptD-promptJpsi.pdf");
  delete c;

  // vs. pT: prompt D, bto D, bto Jpsi
  drawhempty(hempty_v2_pt, 1);
  drawpoints({"v2_promptD_pT", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high", "v2_btoD_pT"});
  drawleg({"v2_promptD_pT", "v2_btoD_pT", "", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high"}, 0.60, 0.82);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_promptD-btoD-btoJpsi.pdf");
  delete c;

  // vs. pT: h, prompt D, prompt Jpsi, bto D, bto Jpsi
  drawhempty(hempty_v2_pt, 1);
  drawpoints({"v2_charge_pT", "v2_Upsilon_pT", "v2_promptD_pT", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high", "v2_btoD_pT"});
  drawleg({"v2_promptD_pT", "", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", "v2_btoD_pT", "", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high", "v2_Upsilon_pT"}, 0.60, 0.86, 0.95);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_h-promptD-promptJpsi-btoD-btoJpsi-Upsilon.pdf");
  delete c;

  // --> v3 <--

  // vs. pT: LHC
  drawhempty(hempty_v3_pt, 1, "");
  drawpoints({"v3_cmu_pT_ATLAS", "v3_promptD_pT_CMS"});
  drawleg({"v3_promptD_pT_CMS", "v3_cmu_pT_ATLAS", "Cent. 10-20\%"}, 0.50, 0.84);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  xjjroot::drawtex(0.23, 0.79, "#it{Open charm}"); 
  c->SaveAs("plots/v3_PbPb_pT_charmLHC.pdf");
  delete c;

  // vs. pT: h, prompt D, bto D, bto Jpsi
  drawhempty(hempty_v3_pt, 1);
  drawpoints({"v3_charge_pT", "v3_promptD_pT", "v3_btoD_pT", "v3_btoJpsi_pT_low", "v3_btoJpsi_pT_high"});
  drawleg({"v3_promptD_pT", "v3_btoD_pT", "", "v3_btoJpsi_pT_low", "v3_btoJpsi_pT_high"}, 0.60, 0.82);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v3_PbPb_pT_h-promptD-btoD-btoJpsi.pdf");
  delete c;

  // vs. pT: h, prompt D, prompt Jpsi
  drawhempty(hempty_v3_pt, 1);
  drawpoints({"v3_charge_pT", "v3_promptD_pT", "v3_promptJpsi_pT_low", "v3_promptJpsi_pT_high"});
  drawleg({"v3_promptD_pT", "", "v3_promptJpsi_pT_low", "v3_promptJpsi_pT_high"}, 0.60, 0.82);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v3_PbPb_pT_h-promptD-promptJpsi.pdf");
  delete c;

  // --> vn <--

  // vs. cent: prompt D, bto Jpsi
  drawhempty(hempty_v2_cent, 0);
  drawpoints({"v2_promptD_cent", "v2_btoJpsi_cent"});
  drawleg({"v2_promptD_cent", "2 < p_{T} < 8 GeV/c"}, 0.22, 0.78);
  drawleg({"v2_btoJpsi_cent", "6.5 < p_{T} < 50 GeV/c"}, 0.55, 0.78);
  c->SaveAs("plots/v2_PbPb_cent_promptD-btoJpsi.pdf");
  delete c;

  // vs. cent: prompt D, prompt Jpsi
  drawhempty(hempty_v2_cent, 0);
  drawpoints({"v2_promptD_cent", "v2_promptJpsi_cent"});
  drawleg({"v2_promptD_cent", "2 < p_{T} < 8 GeV/c"}, 0.22, 0.78);
  drawleg({"v2_promptJpsi_cent", "6.5 < p_{T} < 50 GeV/c"}, 0.55, 0.78);
  c->SaveAs("plots/v2_PbPb_cent_promptD-promptJpsi.pdf");
  delete c;

  // v2 vs. v3: prompt D
  drawhempty(hempty_vn_cent, 0, "");
  drawpoints({"vn_v2_promptD_cent", "vn_v3_promptD_cent"});
  drawleg({"vn_v2_promptD_cent", "vn_v3_promptD_cent"}, 0.60, 0.785, 1.1);
  xjjroot::drawtex(0.24, 0.78, "#bf{Prompt D^{0}}, |y| < 1", tsize*1.1, 13);
  xjjroot::drawtex(0.24, 0.78-lspace*1.1, "2 < p_{T} < 8 GeV/c", tsize*1.1, 13);
  c->SaveAs("plots/vn_PbPb_cent_promptD.pdf");
  delete c;

  // v2 vs. v3: prompt Jpsi
  drawhempty(hempty_vn_cent, 0);
  drawpoints({"vn_v2_promptJpsi_cent", "vn_v3_promptJpsi_cent"});
  drawleg({"vn_v2_promptJpsi_cent", "vn_v3_promptJpsi_cent"}, 0.60, 0.785, 1.1);
  xjjroot::drawtex(0.24, 0.78, "#bf{Prompt J/#psi}, |y| < 2.4", tsize*1.1, 13);
  xjjroot::drawtex(0.24, 0.78-lspace*1.1, "6.5 < p_{T} < 50 GeV/c", tsize*1.1, 13);
  c->SaveAs("plots/vn_PbPb_cent_promptJpsi.pdf");
  delete c;

  // v2 vs. v3: bto Jpsi
  drawhempty(hempty_vn_cent, 0);
  drawpoints({"vn_v2_btoJpsi_cent", "vn_v3_btoJpsi_cent"});
  drawleg({"vn_v2_btoJpsi_cent", "vn_v3_btoJpsi_cent"}, 0.60, 0.785, 1.1);
  xjjroot::drawtex(0.24, 0.78, "#bf{(b#rightarrow) J/#psi}, |y| < 2.4", tsize*1.1, 13);
  xjjroot::drawtex(0.24, 0.78-lspace*1.1, "6.5 < p_{T} < 50 GeV/c", tsize*1.1, 13);
  c->SaveAs("plots/vn_PbPb_cent_btoJpsi.pdf");
  delete c;

  return 0;
}

int main()
{
  return draw_v2_PbPb();
}

void drawhempty(TH2F* hempty, int logx, std::string prel)
{
  xjjroot::sethempty(hempty, 0, -0.02);
  c = new TCanvas("c", "", 600, 600);
  c->SetLogx(logx);
  hempty->Draw("axis");
  xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 0, hempty->GetXaxis()->GetXmax(), 0, kBlack, 2, 1);
  xjjroot::drawtex(0.23, 0.82, Form("#scale[1.25]{#bf{CMS}} #it{%s}", prel.c_str()), 0.04, 11);
}

void drawpoints(std::vector<std::string> list)
{
  TLegend* leg_left = new TLegend(0.23, 0.8-lspace*1, 0.5, 0.8);
  xjjroot::setleg(leg_left, tsize);
  for(auto& t : list)
    if(t != "")
      if(xjjc::str_contains(t, "charge"))
        {
          dats[t]->grsyst()->Draw("3 same");
          leg_left->AddEntry(dats[t]->grsyst(), "#bf{h^{#pm}}, |#eta| < 1", "f");
        }
      else
        dats[t]->grsyst()->Draw("5 same");
  for(auto& t : list)
    if(t != "")
      if(!xjjc::str_contains(t, "charge"))
        dats[t]->grstat()->Draw("pe same");

  leg_left->Draw();

  int is2015 = 0, is2018mb = 0, is2018dimu = 0;
  for(auto& t : list)
    {
      if(xjjc::str_contains(t, "charge")) is2015++;
      if(xjjc::str_contains(t, "D")) is2018mb++;
      if(xjjc::str_contains(t, "Jpsi")) is2018dimu++;
    }
  std::string lumi = std::string(is2015?"0.4":"") + std::string(is2018mb?"/0.58":"") + std::string(is2018dimu?"/1.6":"");
  if(xjjc::str_startsby(lumi, "/")) lumi.erase(0, 1);
  xjjroot::drawCMSright("5.02 TeV PbPb ("+lumi+" nb^{-1})", 0, 0, 0.035);

}

void drawleg(std::vector<std::string> list, float legl, float legt, float legscale)
{
  TLegend* leg_right = new TLegend(legl, legt-lspace*legscale*list.size(), legl+0.2, legt);
  xjjroot::setleg(leg_right, tsize*legscale);
  int ipromptJpsi = -1, ibtoJpsi = -1, iatlas3040 = -1;
  for(int i=0; i<list.size(); i++)
    {
      auto ll = list[i];
      if(legentry.find(ll) != legentry.end()) //
        leg_right->AddEntry(dats[ll]->grsyst(), legentry[ll].c_str(), "p");
      else if(ll == "")
        leg_right->AddEntry((TObject*)0, "", NULL);
      else
        leg_right->AddEntry((TObject*)0, ll.c_str(), NULL);

      if(xjjc::str_contains(ll, "promptJpsi_pT_low"))
        ipromptJpsi = i - 1;
      if(xjjc::str_contains(ll, "btoJpsi_pT_low"))
        ibtoJpsi = i - 1;
    }
  leg_right->Draw();
  if(ipromptJpsi > -1)
    xjjroot::drawtex(legl+0.017, legt-ipromptJpsi*lspace*legscale-0.008, "#bf{Prompt J/#psi}, 10-60\%", tsize*legscale, 13);
  if(ibtoJpsi > -1)
    xjjroot::drawtex(legl+0.017, legt-ibtoJpsi*lspace*legscale-0.008, "#bf{(b #rightarrow) J/#psi}, 10-60\%", tsize*legscale, 13);
}
