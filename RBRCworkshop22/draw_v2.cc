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
  {"v2_promptD_pT", "#bf{Prompt D^{0}} CMS, |y| < 1"},
  {"v2_promptJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v2_promptJpsi_pT_high", "|y| < 2.4"}, 
  {"v2_promptPsi2S_pT_low", "1.6 < |y| < 2.4"},
  {"v2_promptPsi2S_pT_high", "|y| < 2.4"}, 
  {"v2_inclJpsi_pT_ALICE", "2.5 < y < 4"},
  {"v2_inclJpsi_pT_STAR", "STAR, 10-40\%, |y| < 1"},
  {"v2_inclJpsi_pT_PHENIX", "PHENIX, 1.2 < |y| < 2.2"},
  {"v2_btoD_pT", "#bf{(b#rightarrow) D^{0}} CMS, |y| < 1"},
  {"v2_btoJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v2_btoJpsi_pT_high", "|y| < 2.4"},
  {"v2_bmu_pT_ATLAS", "#bf{(b#rightarrow) #mu} ATLAS, |#eta| < 2"},
  {"v2_promptD_pT_CMS_30_50", "Prompt D^{0} #bf{CMS}, |y| < 1"},
  {"v2_cmu_pT_ATLAS", "(c#rightarrow) #mu #bf{ATLAS}, |#eta| < 2"},
  {"v2_promptD_pT_ALICE", "Prompt D #bf{ALICE}, |y| < 0.8"},
  {"v2_promptD_pT_CMS_10_30", "Prompt D^{0} #bf{CMS}, |y| < 1"},
  {"v2_inclD_pT_STAR", "Inclusive D^{0} #bf{STAR}, |y| < 1"},
  {"v3_promptD_pT", "#bf{Prompt D^{0}}, |y| < 1"},
  {"v3_promptJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v3_promptJpsi_pT_high", "|y| < 2.4"},
  {"v3_inclJpsi_pT_ALICE", "2.5 < y < 4"},
  {"v3_btoD_pT_CMS_beauty", "#bf{(b#rightarrow) D^{0}} CMS, |y| < 1"},
  {"v3_btoJpsi_pT_low", "1.6 < |y| < 2.4"},
  {"v3_btoJpsi_pT_high", "|y| < 2.4"},
  {"v3_promptD_pT_CMS", "Prompt D^{0} #bf{CMS}, |y| < 1"},
  {"v3_promptD_pT_CMS_charm", "#bf{Prompt D^{0}} CMS, |y| < 1"},
  {"v3_cmu_pT_ATLAS", "(c#rightarrow) #mu #bf{ATLAS}, |#eta| < 2"},
  {"v3_cmu_pT_ATLAS_charm", "#bf{(c#rightarrow) #mu} ATLAS, |#eta| < 2"},
  {"v3_bmu_pT_ATLAS_beauty", "#bf{(b#rightarrow) #mu} ATLAS, |#eta| < 2"},
  {"v2_pPb_promptD_pT", "#bf{Prompt D^{0}}"},
  {"v2_pPb_promptJpsi_pT", "#bf{Prompt J/#psi}"},
  {"v2_pPb_btoD_pT", "#bf{(b#rightarrow) D^{0}}"},
  {"v2_pp_cmu_pT", "#bf{(c#rightarrow) #mu}"},
  {"v2_pp_Jpsi_pT", "#bf{J/#psi}"},
  {"v2_pp_bmu_pT", "#bf{(b#rightarrow) #mu}"},
  {"v2_PbPb_promptD_pT", "#bf{Prompt D^{0}}"},
  {"v2_PbPb_Jpsi_pT", "#bf{Inclusive J/#psi}"},
  {"v2_PbPb_btoD_pT", "#bf{(b#rightarrow) D^{0}}"},
};
std::map<std::string, exps::hfdata*> dats;
TCanvas* c;
float tsize = 0.035, lspace = 0.045;

void drawhempty(TH2F* hempty, int logx, std::string prel="", std::string out="5.02 TeV PbPb");
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
      if(xjjc::str_contains(t, "_pPb_") || xjjc::str_contains(t, "_pp_")) dats[t]->setxw(0.15, false);
    }
  dats["v2_inclJpsi_pT_STAR"]->setxw(0.08, true);
  dats["v2_inclJpsi_pT_PHENIX"]->setxw(0.08, true);
  dats["v2_promptPsi2S_pT_low"]->setxw(0.08, true);
  dats["v2_promptPsi2S_pT_high"]->setxw(0.08, true);
  
  //
  TH2F* hempty_v2_pt = new TH2F("hempty_v2_pt", ";p_{T} (GeV/c);v_{2}", 10, 1, 60, 10, -0.06, 0.27);
  TH2F* hempty_v2_pt2 = new TH2F("hempty_v2_pt2", ";p_{T} (GeV/c);v_{2}", 10, 0.3, 60, 10, -0.06, 0.27);
  TH2F* hempty_v2_pt3 = new TH2F("hempty_v2_pt3", ";p_{T} (GeV/c);v_{2}", 10, 1, 60, 10, -0.06, 0.40);
  TH2F* hempty_v3_pt = new TH2F("hempty_v3_pt", ";p_{T} (GeV/c);v_{3}", 10, 1, 60, 10, -0.04, 0.15);
  TH2F* hempty_v2_pt_pPb = new TH2F("hempty_v2_pt_pPb", ";p_{T} (GeV/c);v_{2}", 10, 0, 10, 10, -0.08, 0.2);
  TH2F* hempty_v2_pt_PbPb = new TH2F("hempty_v2_pt_pPb", ";p_{T} (GeV/c);v_{2}", 10, 0, 10, 10, -0.08, 0.2);
  TH2F* hempty_v2_pt_pp = new TH2F("hempty_v2_pt_pp", ";p_{T} (GeV/c);v_{2}", 10, 0, 12, 10, -0.08, 0.2);

  xjjroot::setgstyle(1);
  xjjroot::mkdir("plots/x");

  // vs. pT: LHC open charm
  drawhempty(hempty_v2_pt, 1, "#it{#bf{Open charm}}");
  drawpoints({"v2_cmu_pT_ATLAS", "v2_promptD_pT_ALICE", "v2_promptD_pT_CMS_30_50"});
  drawleg({"v2_promptD_pT_CMS_30_50", "v2_promptD_pT_ALICE", "v2_cmu_pT_ATLAS", "Cent. 30-40\%"}, 0.50, 0.85);
  xjjroot::drawtex(0.55, 0.23, "Cent. 30-50\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_charmLHC.pdf");
  delete c;

  // vs. pT: LHC vs. RHIC
  drawhempty(hempty_v2_pt, 1, "#it{#bf{Open charm}}");
  drawpoints({"v2_inclD_pT_STAR", "v2_promptD_pT_CMS_10_30"});
  drawleg({"v2_promptD_pT_CMS_10_30", "v2_inclD_pT_STAR", "AuAu 200 GeV, 10-40\%"}, 0.50, 0.85);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_charmLHCvsRHIC.pdf");
  delete c;

  // vs. pT: prompt D, prompt Jpsi CMS, inclusive Jpsi ALICE
  drawhempty(hempty_v2_pt, 1);
  drawpoints({"v2_promptD_pT", "v2_inclJpsi_pT_ALICE", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high"});
  drawleg({"v2_promptD_pT", "[]#bf{Prompt J/#psi} CMS, 10-60\%", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", "[]#bf{Inclusive J/#psi} ALICE", "v2_inclJpsi_pT_ALICE"}, 0.53, 0.85);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_promptD-Jpsi.pdf");
  delete c;

  // vs. pT: Jpsi: LHC vs.RHIC
  drawhempty(hempty_v2_pt2, 1);
  drawpoints({"v2_inclJpsi_pT_ALICE", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", "v2_inclJpsi_pT_STAR", "v2_inclJpsi_pT_PHENIX"});
  drawleg({"[]#bf{PbPb 5.02 TeV}", "[]Prompt J/#psi CMS", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", "[]Inclusive J/#psi ALICE, 10-30\%", "v2_inclJpsi_pT_ALICE"}, 0.23, 0.85);
  drawleg({"[]#bf{AuAu 200 GeV}", "[]Inclusive J/#psi", "v2_inclJpsi_pT_STAR", "v2_inclJpsi_pT_PHENIX"}, 0.53, 0.852);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-60\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_JpsiLHCvsRHIC.pdf");
  delete c;

  // vs. pT: Jpsi vs. Psi2S
  drawhempty(hempty_v2_pt3, 1);
  drawpoints({"v2_promptPsi2S_pT_low", "v2_promptPsi2S_pT_high", "v2_inclJpsi_pT_ALICE", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high"});
  drawleg({"[]#bf{Prompt #psi(2S)} CMS", "v2_promptPsi2S_pT_low", "v2_promptPsi2S_pT_high"}, 0.23, 0.85);
  drawleg({"[]#bf{Prompt J/#psi} CMS", "v2_promptJpsi_pT_low", "v2_promptJpsi_pT_high", "[]#bf{Inclusive J/#psi} ALICE", "v2_inclJpsi_pT_ALICE", "Cent. 10-30\%"}, 0.60, 0.85);
  xjjroot::drawtex(0.55, 0.20, "Cent. 10-60\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_promptJpsi-promptPsi2S.pdf");
  delete c;

  // vs. pT: prompt D, bto D, bto Jpsi, bto mu
  drawhempty(hempty_v2_pt, 1, "#it{#bf{Open beauty}}");
  drawpoints({"v2_promptD_pT", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high", "v2_btoD_pT", "v2_bmu_pT_ATLAS"});
  drawleg({"v2_promptD_pT", "v2_btoD_pT", "[]#bf{(b#rightarrow) J/#psi} CMS, 10-60\%", "v2_btoJpsi_pT_low", "v2_btoJpsi_pT_high", "v2_bmu_pT_ATLAS", "Cent. 10-20\%"}, 0.53, 0.85);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_promptD-btoD-btoJpsi-btomu.pdf");
  delete c;

  // --> v3 <--

  // vs. pT: prompt D, c->mu, prompt Jpsi
  drawhempty(hempty_v3_pt, 1, "#it{#bf{Charm}}");
  drawpoints({"v3_promptD_pT_CMS_charm", "v3_cmu_pT_ATLAS_charm", "v3_promptJpsi_pT_low", "v3_promptJpsi_pT_high"});
  drawleg({"v3_promptD_pT_CMS_charm", "v3_cmu_pT_ATLAS_charm", "Cent. 10-20\%", "[]#bf{Prompt J/#psi} CMS, 10-60\%", "v3_promptJpsi_pT_low", "v3_promptJpsi_pT_high"}, 0.53, 0.85);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v3_PbPb_pT_promptD-cmu-promptJpsi.pdf");
  delete c;

  // vs. pT: prompt Jpsi CMS, incl Jpsi ALICE
  drawhempty(hempty_v3_pt, 1, "");
  drawpoints({"v3_inclJpsi_pT_ALICE", "v3_promptJpsi_pT_low", "v3_promptJpsi_pT_high"});
  drawleg({"[]Prompt J/#psi #bf{CMS}, 10-60\%", "v3_promptJpsi_pT_low", "v3_promptJpsi_pT_high", "[]Inclusive J/#psi #bf{ALICE}, 10-30\%", "v3_inclJpsi_pT_ALICE"}, 0.50, 0.85);
  c->SaveAs("plots/v3_PbPb_pT_Jpsi.pdf");
  delete c;

  // vs. pT: bto D, bto Jpsi, bto mu
  drawhempty(hempty_v3_pt, 1, "#it{#bf{Open Beauty}}");
  drawpoints({"v3_bmu_pT_ATLAS_beauty", "v3_btoD_pT_CMS_beauty", "v3_btoJpsi_pT_low", "v3_btoJpsi_pT_high"});
  drawleg({"v3_btoD_pT_CMS_beauty", "[]#bf{(b#rightarrow) J/#psi} CMS, 10-60\%", "v3_btoJpsi_pT_low", "v3_btoJpsi_pT_high", "v3_bmu_pT_ATLAS_beauty", "Cent. 10-20\%"}, 0.53, 0.85);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v3_PbPb_pT_btoD-bmu-btoJpsi.pdf");
  delete c;

  // --> pPb <--

  // vs. pT: prompt D, prompt Jpsi, bto D
  drawhempty(hempty_v2_pt_pPb, 0, "#bf{CMS}", "8.16 TeV pPb");
  drawpoints({"v2_pPb_btoD_pT", "v2_pPb_promptJpsi_pT", "v2_pPb_promptD_pT"});
  drawleg({"[]|y| < 1", "v2_pPb_promptD_pT", "v2_pPb_btoD_pT"}, 0.68, 0.85);
  drawleg({"[]1.2 < |y| < 2.4", "v2_pPb_promptJpsi_pT"}, 0.43, 0.85);
  xjjroot::drawtex(0.55, 0.23, "185 #leq N_{trk} < 250", tsize);
  c->SaveAs("plots/v2_pPb_pT_promptD-promptJpsi-btoD.pdf");
  delete c;

  // vs. pT: prompt D, prompt Jpsi, bto D
  drawhempty(hempty_v2_pt_PbPb, 0, "", "5.02 TeV PbPb");
  drawpoints({"v2_PbPb_Jpsi_pT", "v2_PbPb_promptD_pT"});
  drawleg({"[]#bf{CMS} |y| < 1", "v2_PbPb_promptD_pT"}, 0.68, 0.46);
  drawleg({"[]#bf{ALICE} 2.5 < |y| < 4", "v2_PbPb_Jpsi_pT"}, 0.35, 0.46);
  xjjroot::drawtex(0.55, 0.23, "Cent. 10-30\%", tsize);
  c->SaveAs("plots/v2_PbPb_pT_promptD-Jpsi-btoD.pdf");
  delete c;

  // --> pp <--

  // vs. pT: prompt D, prompt Jpsi, bto D
  drawhempty(hempty_v2_pt_pp, 0, "", "13 TeV pp");
  drawpoints({"v2_pp_Jpsi_pT", "v2_pp_bmu_pT", "v2_pp_cmu_pT"});
  drawleg({"[]#bf{ATLAS} 60 #leq N_{trk} < 120", "[]|#eta| < 2.4", "v2_pp_cmu_pT", "v2_pp_bmu_pT"}, 0.53, 0.85);
  drawleg({"[]#bf{ALICE} 0-5\%", "[]2.5 < |y| < 4", "v2_pp_Jpsi_pT"}, 0.23, 0.85);
  c->SaveAs("plots/v2_pp_pT_cmu-Jpsi-bmu.pdf");
  delete c;

  return 0;
}

int main()
{
  return draw_v2_PbPb();
}

void drawhempty(TH2F* hempty, int logx, std::string prel, std::string out)
{
  xjjroot::sethempty(hempty, 0, 0.14);
  if(logx)
    hempty->GetXaxis()->SetLabelOffset(-0.01);
  c = new TCanvas("c", "", 600, 600);
  c->SetLogx(logx);
  hempty->Draw("axis");
  xjjroot::drawline(hempty->GetXaxis()->GetXmin(), 0, hempty->GetXaxis()->GetXmax(), 0, kBlack, 2, 1);
  xjjroot::drawtex(0.23, 0.815, Form("%s", prel.c_str()), 0.04, 11);
  xjjroot::drawCMSright(out.c_str(), 0, 0, 0.035);
}

void drawpoints(std::vector<std::string> list)
{
  for(auto& t : list)
    if(t != "")
      dats[t]->grsyst()->Draw("5 same");
  for(auto& t : list)
    if(t != "")
      {
        if(dats[t]->getxw() > 0)
          dats[t]->grstat2()->Draw("pe same");
        else
          dats[t]->grstat()->Draw("pe same");
      }
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
