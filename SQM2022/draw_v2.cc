#include "hfdata.h"
#include "xjjcuti.h"
#include "xjjrootuti.h"
#include "config.h"

#include <string>
#include <vector>
#include <map>

#include <TCanvas.h>
#include <TH2F.h>

std::vector<std::string> types = {"v2_charge_pT", "v2_promptD_pT", 
                                  "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", 
                                  "v2_btoD_pT", "v2_btoJpsi_pT_low", 
                                  "v2_btoJpsi_pT_high", "v2_Upsilon_pT", 
                                  "v2_promptD_cent", "v2_promptJpsi_cent", 
                                  "vn_v2_promptD_cent", "vn_v2_promptJpsi_cent", 
                                  "v3_promptD_cent", "v3_promptJpsi_cent",
                                  "vn_v3_promptD_cent", "vn_v3_promptJpsi_cent"};
std::map<std::string, std::string> legentry = {
  {"v2_promptD_pT", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v2_promptJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v2_promptJpsi_pT_high", "|y| < 2.4"},
  {"v2_btoD_pT", "#bf{(b #rightarrow) D^{0}}, |y| < 1"},
  {"v2_btoJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v2_btoJpsi_pT_high", "|y| < 2.4"},
  {"v2_Upsilon_pT", "#bf{#Upsilon(1S)}, |y| < 2.4"},
  {"v2_promptD_cent", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v2_promptJpsi_cent", "#bf{Prompt J/#psi}, |y| < 2.4"},
  {"vn_v2_promptD_cent", "v_{2}"},
  {"vn_v2_promptJpsi_cent", "v_{2}"},
  {"v3_promptD_cent", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v3_promptJpsi_cent", "#bf{Prompt J/#psi}, |y| < 2.4"},
  {"vn_v3_promptD_cent", "v_{3}"},
  {"vn_v3_promptJpsi_cent", "v_{3}"},
};
std::map<std::string, exps::hfdata*> dats;
TCanvas* c;
float tsize = 0.031, lspace = 0.042;

void drawhempty(TH2F* hempty, int logx);
void drawpoints(std::vector<std::string> list);
void drawleg(std::vector<std::string> list, float legl, float legt);

int draw_v2_PbPb(std::string input="configs/input_v2_PbPb.conf")
{
  xjjc::config* conf = new xjjc::config(input);
  for(auto& t : types)
    {
      if(!conf->goodkey(t)) continue;
      dats[t] = new exps::hfdata(Form("%s:B", conf->vv(t)[0].c_str()), atoi(conf->vv(t)[1].c_str()), "", "", atoi(conf->vv(t)[2].c_str()));
    }
  dats["v2_charge_pT"]->grsyst()->SetLineWidth(0);
  dats["v2_charge_pT"]->grsyst()->SetFillColorAlpha(atoi(conf->vv("v2_charge_pT")[1].c_str()), 0.2);

  //
  TH2F* hempty_v2_pt = new TH2F("hempty_v2_pt", ";p_{T} (GeV/c);v_{2}", 10, 1, 60, 10, -0.06, 0.27);
  TH2F* hempty_v2_cent = new TH2F("hempty_v2_cent", ";Centrality (\%);v_{2}", 10, 0, 90, 10, -0.03, 0.27);
  TH2F* hempty_vn_cent = new TH2F("hempty_vn_cent", ";Centrality (\%);v_{n}", 10, 0, 90, 10, -0.03, 0.27);

  xjjroot::setgstyle(1);
  xjjroot::mkdir("plots/x");

  // vs. pT: h, prompt D, prompt Jpsi
  drawhempty(hempty_v2_pt, 1);
  drawpoints({"v2_charge_pT", "v2_promptD_pT", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high"});
  drawleg({"v2_promptD_pT", "", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high"}, 0.62, 0.8);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", 0.035);
  c->SaveAs("plots/v2_PbPb_pT_h-promptD-promptJpsi.pdf");
  delete c;

  // vs. pT: h, prompt D, prompt Jpsi, bto D, bto Jpsi
  drawhempty(hempty_v2_pt, 1);
  drawpoints({"v2_charge_pT", "v2_Upsilon_pT", "v2_promptD_pT", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high", "v2_btoD_pT"});
  drawleg({"v2_promptD_pT", "", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", "v2_btoD_pT", "", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high", "v2_Upsilon_pT"}, 0.62, 0.86);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", 0.035);
  c->SaveAs("plots/v2_PbPb_pT_h-promptD-promptJpsi-btoD-btoJpsi-Upsilon.pdf");
  delete c;

  // vs. pT: prompt D, bto D, bto Jpsi
  drawhempty(hempty_v2_pt, 1);
  drawpoints({"v2_promptD_pT", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high", "v2_btoD_pT"});
  drawleg({"v2_promptD_pT", "v2_btoD_pT", "", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high"}, 0.62, 0.82);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", 0.035);
  c->SaveAs("plots/v2_PbPb_pT_promptD-btoD-btoJpsi.pdf");
  delete c;

  // vs. cent: prompt D, prompt Jpsi
  drawhempty(hempty_v2_cent, 0);
  drawpoints({"v2_promptD_cent", "v2_promptJpsi_cent"});
  drawleg({"v2_promptD_cent", "2 < p_{T} < 8 GeV/c"}, 0.22, 0.78);
  drawleg({"v2_promptJpsi_cent", "6.5 < p_{T} < 50 GeV/c"}, 0.55, 0.78);
  c->SaveAs("plots/v2_PbPb_cent_promptD-promptJpsi.pdf");
  delete c;

  // v2 vs. v3: prompt D
  drawhempty(hempty_vn_cent, 0);
  drawpoints({"vn_v2_promptD_cent", "vn_v3_promptD_cent"});
  drawleg({"vn_v2_promptD_cent", "vn_v3_promptD_cent"}, 0.60, 0.785);
  xjjroot::drawtex(0.24, 0.78, "#bf{Prompt D^{0}}, |y| < 1", 0.035, 13);
  xjjroot::drawtex(0.24, 0.78-lspace*1, "2 < p_{T} < 8 GeV/c", 0.035, 13);
  c->SaveAs("plots/vn_PbPb_cent_promptD.pdf");
  delete c;

  // v2 vs. v3: prompt Jpsi
  drawhempty(hempty_vn_cent, 0);
  drawpoints({"vn_v2_promptJpsi_cent", "vn_v3_promptJpsi_cent"});
  drawleg({"vn_v2_promptJpsi_cent", "vn_v3_promptJpsi_cent"}, 0.60, 0.785);
  xjjroot::drawtex(0.24, 0.78, "#bf{Prompt J/#psi}, |y| < 2.4", 0.035, 13);
  xjjroot::drawtex(0.24, 0.78-lspace*1, "6.5 < p_{T} < 50 GeV/c", 0.035, 13);
  c->SaveAs("plots/vn_PbPb_cent_promptJpsi.pdf");
  delete c;

  return 0;
}

int main()
{
  return draw_v2_PbPb();
}

void drawhempty(TH2F* hempty, int logx)
{
  xjjroot::sethempty(hempty, 0, -0.02);
  c = new TCanvas("c", "", 700, 600);
  c->SetLogx(logx);
  hempty->Draw("axis");
  xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 0, hempty->GetXaxis()->GetXmax(), 0, kBlack, 2, 1);
  xjjroot::drawtex(0.23, 0.84, "#scale[1.25]{#bf{CMS}} #it{Preliminary}");
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

void drawleg(std::vector<std::string> list, float legl, float legt)
{
  TLegend* leg_right = new TLegend(legl, legt-lspace*list.size(), legl+0.2, legt);
  xjjroot::setleg(leg_right, tsize);
  int ipromptJpsi = -1, ibtoJpsi = -1;
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
    xjjroot::drawtex(legl+0.017, legt-ipromptJpsi*lspace-0.008, "#bf{Prompt J/#psi}, 10-60\%", tsize, 13);
  if(ibtoJpsi > -1)
    xjjroot::drawtex(legl+0.017, legt-ibtoJpsi*lspace-0.008, "#bf{(b #rightarrow) J/#psi}, 10-60\%", tsize, 13);
}
