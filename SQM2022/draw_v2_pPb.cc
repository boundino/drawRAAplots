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
  {"v2_charge_pT", "#bf{K_{s}^{0}}, |y| < 1"},
  {"v2_promptD_pT", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v2_promptJpsi_pT", "#bf{Prompt J/#psi}"},
  {"v2_btoD_pT", "#bf{(b #rightarrow) D^{0}}, |y| < 1"},
  {"v2_Upsilon_pT", "#bf{#Upsilon(1S)}, |y| < 2.4"},
};
std::map<std::string, exps::hfdata*> dats;
TCanvas* c;
float tsize = 0.035, lspace = 0.045;

void drawhempty(TH2F* hempty, int logx);
void drawpoints(std::vector<std::string> list);
void drawleg(std::vector<std::string> list, float legl, float legt);

int draw_v2_PbPb(std::string input="configs/input_v2_pPb.conf")
{
  xjjc::config* conf = new xjjc::config(input);
  for(auto& ll : legentry)
    {
      auto t = ll.first;
      if(!conf->goodkey(t)) continue;
      dats[t] = new exps::hfdata(Form("%s:B", conf->vv(t)[0].c_str()), atoi(conf->vv(t)[1].c_str()), "", "", atoi(conf->vv(t)[2].c_str()));
    }
  dats["v2_charge_pT"]->grsyst()->SetLineWidth(0);
  dats["v2_charge_pT"]->grsyst()->SetFillColorAlpha(atoi(conf->vv("v2_charge_pT")[1].c_str()), 0.2);

  //
  TH2F* hempty_v2_pt = new TH2F("hempty_v2_pt", ";p_{T} (GeV/c);v_{2}", 10, 0, 10, 10, -0.07, 0.25);

  xjjroot::setgstyle(1);
  xjjroot::mkdir("plots/x");

  // vs. pT: h, prompt D, prompt Jpsi, bto D, bto Jpsi, Upsilon1S
  drawhempty(hempty_v2_pt, 0);
  drawpoints({"v2_charge_pT", "v2_Upsilon_pT", "v2_btoD_pT", "v2_promptJpsi_pT", "v2_promptD_pT"});
  drawleg({"v2_promptD_pT", "v2_promptJpsi_pT", "1.2 < |y| < 2.4", "v2_btoD_pT", "v2_Upsilon_pT", "70 #leq N_{trk} < 300"}, 0.60, 0.85);
  xjjroot::drawtex(0.55, 0.21, "185 #leq N_{trk} < 250", 0.035);
  c->SaveAs("plots/v2_pPb_pT_h-promptD-promptJpsi-btoD-Upsilon.pdf");
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
  c = new TCanvas("c", "", 600, 600);
  c->SetLogx(logx);
  hempty->Draw("axis");
  xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 0, hempty->GetXaxis()->GetXmax(), 0, kBlack, 2, 1);
  xjjroot::drawtex(0.23, 0.82, "#scale[1.25]{#bf{CMS}} #it{Preliminary}", 0.04, 11);
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
          leg_left->AddEntry(dats[t]->grsyst(), legentry[t].c_str(), "f");
        }
      else
        dats[t]->grsyst()->Draw("5 same");

  for(auto& t : list)
    if(t != "")
      if(!xjjc::str_contains(t, "charge"))
        dats[t]->grstat()->Draw("pe same");

  leg_left->Draw();
  xjjroot::drawCMSright("8.16 TeV pPb", 0, 0, 0.035);

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
    }
  leg_right->Draw();
}
