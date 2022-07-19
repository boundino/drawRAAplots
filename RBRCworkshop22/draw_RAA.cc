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
  {"RAA_charge_pT", "#bf{h^{#pm}}, |#eta| < 1"},
  {"RAA_promptD_pT", "#bf{Prompt D^{0}}, |y| < 1"},
  {"RAA_btoD_pT", "#bf{(b#rightarrow) D^{0}}, |y| < 1"},
  {"RAA_btoD_pT_CMS", "CMS, |y| < 1, 0-100\%"},
  {"RAA_btoD_pT_ALICE", "ALICE, |y| < 0.5, 0-10\%"},
  {"RAA_btoJpsi_pT_low", "1.8 < |y| < 2.4"},
  {"RAA_btoJpsi_pT_high", "#bf{(b#rightarrow) J/#psi}, |y| < 2.4"},
  {"RAA_promptD_pT_CMS_0_10", "#bf{CMS}, 5 TeV PbPb, |y| < 1"},
  {"RAA_promptD_pT_ALICE", "#bf{ALICE}, 5 TeV PbPb, |y| < 0.8"},
  {"RAA_promptD_pT_STAR", "#bf{STAR}, 200 GeV AuAu, |y| < 1"},
  {"RAA_btoJpsi_pT_CMS", "#bf{CMS}, |y| < 2.4"},
  {"RAA_btoJpsi_pT_ATLAS", "#bf{ATLAS}, |y| < 2"},
  {"RAA_btoJpsi_pT_ALICE", "#bf{ALICE}, |y| < 0.9"},
  {"RAA_promptJpsi_pT_CMS", "CMS, |y| < 2.4"},
  {"RAA_promptJpsi_pT_ATLAS", "ATLAS, |y| < 2"},
  {"RAA_promptJpsi_pT_ALICE", "ALICE, |y| < 0.9"},
  {"RAA_inclusiveJpsi_pT_ALICE", "ALICE, |y| < 0.9"},
  {"RAA_inclusiveJpsi_pT_STAR", "STAR, |y| < 0.5"},
  {"RAA_inclusiveJpsi_pT_PHENIX", "PHENIX, |y| < 0.35"},
  {"RAA_Upsilon1S_Npart_CMS", "CMS, |y| < 2.4"},
  {"RAA_Upsilon1S_Npart_ATLAS", "ATLAS, |y| < 1.5"},
  {"RAA_Upsilon1S_Npart_ALICE", "ALICE, 2.5 < |y| < 4"},
  {"RAA_Upsilon2S_Npart_CMS", "CMS, |y| < 2.4"},
  {"RAA_Upsilon2S_Npart_ATLAS", "ATLAS, |y| < 1.5"},
  {"RAA_Upsilon2S_Npart_ALICE", "ALICE, 2.5 < |y| < 4"},
};
std::map<std::string, exps::hfdata*> dats;
TCanvas* c;
float tsize = 0.035, lspace = 0.045;

void drawhempty(TH2F* hempty, int logx, std::string prel="");
void drawpoints(std::vector<std::string> list);
void drawleg(std::vector<std::string> list, float legl, float legt, float legscale=1.);

int draw_RAA_PbPb(std::string input="configs/input_RAA_PbPb.conf")
{
  xjjc::config* conf = new xjjc::config(input);
  for(auto& ll : legentry)
    {
      auto t = ll.first;
      if(!conf->goodkey(t)) continue;
      dats[t] = new exps::hfdata(Form("%s", conf->vv(t)[0].c_str()), atoi(conf->vv(t)[1].c_str()), "", "", atoi(conf->vv(t)[2].c_str()));

      if(xjjc::str_contains(t, "Npart")) dats[t]->setxw(6, false);
    }
  dats["RAA_btoD_pT"]->setxw(0.05, true);
  dats["RAA_promptD_pT_STAR"]->setxw(0.08, true);
  dats["RAA_promptD_pT_ALICE"]->setxw(0.08, true);
  dats["RAA_promptD_pT_STAR"]->setmarkersize(1.3);
  dats["RAA_promptD_pT_ALICE"]->setmarkersize(1.3);

  //
  TH2F* hempty_RAA_pt = new TH2F("hempty_RAA_pt", ";p_{T} (GeV/c);R_{AA}", 10, 0.2, 150, 10, 0, 1.4);
  TH2F* hempty_RAA_pt2 = new TH2F("hempty_RAA_pt2", ";p_{T} (GeV/c);R_{AA}", 10, 1, 150, 10, 0, 1.7);
  TH2F* hempty_RAA_pt3 = new TH2F("hempty_RAA_pt3", ";p_{T} (GeV/c);R_{AA}", 10, 1, 60, 10, 0, 1.4);
  TH2F* hempty_RAA_pt4 = new TH2F("hempty_RAA_pt4", ";p_{T} (GeV/c);R_{AA}", 10, 0.2, 50, 10, 0, 2);
  TH2F* hempty_RAA_Npart = new TH2F("hempty_RAA_Npart", ";<N_{part}>;R_{AA}", 10, 0, 450, 10, 0, 1.5);

  xjjroot::setgstyle(1);
  xjjroot::mkdir("plots/x");

  // vs. pT: LHC vs. RHIC
  drawhempty(hempty_RAA_pt, 1, "#bf{Prompt D^{0}}");
  drawpoints({"RAA_promptD_pT_STAR", "RAA_promptD_pT_ALICE", "RAA_promptD_pT_CMS_0_10"});
  drawleg({"RAA_promptD_pT_CMS_0_10", "RAA_promptD_pT_ALICE", "RAA_promptD_pT_STAR"}, 0.45, 0.86);
  xjjroot::drawtex(0.70, 0.23, "Cent. 0-10\%", tsize);
  c->SaveAs("plots/RAA_PbPb_pT_charmLHCvsRHIC.pdf");
  delete c;

  // vs. pT: bto Jpsi LHC
  drawhempty(hempty_RAA_pt3, 1, "#bf{(b#rightarrow) J/#psi}");
  drawpoints({"RAA_btoJpsi_pT_ALICE", "RAA_btoJpsi_pT_ATLAS", "RAA_btoJpsi_pT_CMS"});
  drawleg({"RAA_btoJpsi_pT_CMS", "RAA_btoJpsi_pT_ATLAS", "RAA_btoJpsi_pT_ALICE"}, 0.50, 0.84);
  xjjroot::drawtex(0.23, 0.23, "Cent. 0-10\%", tsize);
  c->SaveAs("plots/RAA_PbPb_pT_btoJpsi.pdf");
  delete c;

  // vs. pT: bto D LHC
  drawhempty(hempty_RAA_pt2, 1, "#bf{(b#rightarrow) D^{0}}");
  drawpoints({"RAA_btoD_pT_CMS", "RAA_btoD_pT_ALICE"});
  drawleg({"RAA_btoD_pT_ALICE", "RAA_btoD_pT_CMS"}, 0.46, 0.84);
  c->SaveAs("plots/RAA_PbPb_pT_btoD.pdf");
  delete c;

  // vs. pT: Prompt Jpsi
  drawhempty(hempty_RAA_pt4, 1, "");
  drawpoints({"RAA_promptJpsi_pT_ALICE", "RAA_inclusiveJpsi_pT_ALICE", "RAA_inclusiveJpsi_pT_STAR", "RAA_promptJpsi_pT_ATLAS", "RAA_promptJpsi_pT_CMS", "RAA_inclusiveJpsi_pT_PHENIX"});
  drawleg({"[]#bf{PbPb 5.02 TeV} 0-10\%", "[]Prompt J/#psi", "RAA_promptJpsi_pT_ATLAS", "RAA_promptJpsi_pT_CMS", "RAA_promptJpsi_pT_ALICE", "[]Inclusive J/#psi", "RAA_inclusiveJpsi_pT_ALICE"}, 0.60, 0.86);
  drawleg({"[]#bf{AuAu 200 GeV} 0-20\%", "[]Inclusive J/#psi", "RAA_inclusiveJpsi_pT_PHENIX", "RAA_inclusiveJpsi_pT_STAR"}, 0.21, 0.86);
  c->SaveAs("plots/RAA_PbPb_pT_JpsiLHCvsRHIC.pdf");
  delete c;

  // vs. Npart: bto D LHC
  drawhempty(hempty_RAA_Npart, 0, "");
  drawpoints({"RAA_Upsilon1S_Npart_ALICE", "RAA_Upsilon1S_Npart_ATLAS", "RAA_Upsilon1S_Npart_CMS", "RAA_Upsilon2S_Npart_ALICE", "RAA_Upsilon2S_Npart_ATLAS", "RAA_Upsilon2S_Npart_CMS"});
  drawleg({"[]#bf{#Upsilon(1S)}, p_{T} < 30 GeV", "RAA_Upsilon1S_Npart_CMS", "RAA_Upsilon1S_Npart_ATLAS", "RAA_Upsilon1S_Npart_ALICE", "p_{T} < 15 GeV"}, 0.25, 0.86);
  drawleg({"[]#bf{#Upsilon(2S)}, p_{T} < 30 GeV", "RAA_Upsilon2S_Npart_CMS", "RAA_Upsilon2S_Npart_ATLAS", "RAA_Upsilon2S_Npart_ALICE", "p_{T} < 15 GeV"}, 0.60, 0.86);
  c->SaveAs("plots/RAA_PbPb_Npart_Upsilon1S2S.pdf");
  delete c;

  return 0;
}

int main()
{
  return draw_RAA_PbPb();
}

void drawhempty(TH2F* hempty, int logx, std::string prel)
{
  xjjroot::sethempty(hempty, 0, 0.14);
  if(logx)
    hempty->GetXaxis()->SetLabelOffset(-0.01);
  c = new TCanvas("c", "", 600, 600);
  c->SetLogx(logx);
  hempty->Draw("axis");
  // xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 0, hempty->GetXaxis()->GetXmax(), 0, kBlack, 2, 1);
  xjjroot::drawtex(0.23, 0.81, Form("#it{%s}", prel.c_str()), 0.04, 11);
}

void drawpoints(std::vector<std::string> list)
{
  for(auto& t : list)
    if(t != "")
      if(!xjjc::str_contains(t, "charge"))
        dats[t]->grsyst()->Draw("5 same");
      else
        dats[t]->grsyst()->Draw("2 same");
  for(auto& t : list)
    if(t != "")
      {
        if(dats[t]->getxw() > 0)
          dats[t]->grstat2()->Draw("pe same");
        else
          dats[t]->grstat()->Draw("pe same");
      }

  int is2015 = 0, is2018mb = 0, is2018dimu = 0;
  for(auto& t : list)
    {
      if(xjjc::str_contains(t, "charge")) is2015++;
      if(xjjc::str_contains(t, "D")) is2018mb++;
      if(xjjc::str_contains(t, "Jpsi")) is2018dimu++;
    }
  std::string lumi = std::string(is2015?"0.4":"") + std::string(is2018mb?"/0.53":"") + std::string(is2018dimu?"/0.37":"");
  if(xjjc::str_startsby(lumi, "/")) lumi.erase(0, 1);
  // xjjroot::drawCMSright("5.02 TeV PbPb ("+lumi+" nb^{-1})", 0, 0, 0.035);
  xjjroot::drawCMSright("5.02 TeV PbPb", 0, 0, 0.035);

}

void drawleg(std::vector<std::string> list, float legl, float legt, float legscale)
{
  TLegend* leg_right = new TLegend(legl, legt-lspace*legscale*list.size(), legl+0.2, legt);
  xjjroot::setleg(leg_right, tsize*legscale);
  std::map<int, std::string> legtitles;
  for(int i=0; i<list.size(); i++)
    {
      auto ll = list[i];
      if(legentry.find(ll) != legentry.end()) //
        leg_right->AddEntry(dats[ll]->grsyst(), legentry[ll].c_str(), "p");
      else if(xjjc::str_contains(ll, "[]"))
        {
          legtitles[i] = xjjc::str_eraseall(ll, "[]");
          leg_right->AddEntry((TObject*)0, "", NULL);
	}
      else
        leg_right->AddEntry((TObject*)0, ll.c_str(), NULL);
    }
  leg_right->Draw();
  for(auto& t : legtitles)
    xjjroot::drawtex(legl+0.017, legt-t.first*lspace*legscale-0.008, t.second.c_str(), tsize*legscale, 13);
}

// void drawleg(std::vector<std::string> list, float legl, float legt, float legscale)
// {
//   TLegend* leg_right = new TLegend(legl, legt-lspace*legscale*list.size(), legl+0.2, legt);
//   xjjroot::setleg(leg_right, tsize*legscale);
//   int ipromptJpsi = -1, ibtoJpsi = -1, iatlas3040 = -1;
//   for(int i=0; i<list.size(); i++)
//     {
//       auto ll = list[i];
//       if(legentry.find(ll) != legentry.end()) //
//         leg_right->AddEntry(dats[ll]->grsyst(), legentry[ll].c_str(), "p");
//       else if(ll == "")
//         leg_right->AddEntry((TObject*)0, "", NULL);
//       else
//         leg_right->AddEntry((TObject*)0, ll.c_str(), NULL);

//       if(xjjc::str_contains(ll, "promptJpsi_pT_low"))
//         ipromptJpsi = i - 1;
//       if(xjjc::str_contains(ll, "btoJpsi_pT_low"))
//         ibtoJpsi = i - 1;
//     }
//   leg_right->Draw();
//   if(ipromptJpsi > -1)
//     xjjroot::drawtex(legl+0.017, legt-ipromptJpsi*lspace*legscale-0.008, "#bf{Prompt J/#psi}", tsize*legscale, 13);
//   if(ibtoJpsi > -1)
//     xjjroot::drawtex(legl+0.017, legt-ibtoJpsi*lspace*legscale-0.008, "#bf{(b#rightarrow) J/#psi}", tsize*legscale, 13);
// }
