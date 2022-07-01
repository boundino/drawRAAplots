#include "drawTheoryRAApromptDcent010.h"
#include "drawTheoryV2promptDcent3050.h"
#include "drawTheoryRAAbtoDcent0100.h"
#include "drawTheoryRAAbtoDcent010.h"
#include "drawTheoryV2btoDcent1030.h"
#include "config.h"
#include "projection.h"
#include "xjjrootuti.h"

std::map<std::string, TH1F*> h;
std::map<std::string, TGraphErrors*> g;
std::map<std::string, TLegend*> leg;
void setdata(xjjc::config* conf);
void sethist(projection* proj, std::string name, float xleg, float yleg);
int drawTheory(std::string configuration)
{
  xjjc::config* conf = new xjjc::config(configuration);
  setdata(conf);

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadLeftMargin(0.17);
  gStyle->SetPadRightMargin(0.025);
  gStyle->SetPadTopMargin(0.080);
  gStyle->SetPadBottomMargin(0.11);
  gStyle->SetEndErrorSize(5);

  // RAA
  drawTheoryRAApromptDcent010::drawcanvas();
  g["RAA_D0_before"]->Draw("2 same");
  drawTheoryRAApromptDcent010::setupNdrawTheory();
  drawTheoryRAApromptDcent010::drawlegends();
  h["RAA_D0_before"]->Draw("peX0 same");
  xjjroot::saveas(drawTheoryRAApromptDcent010::canvas, "plots/"+conf->v("name")+"/cdrawTheoryRAApromptDcent010_data.pdf");
  h["RAA_D0_before"]->SetLineColor(kGray+1);
  h["RAA_D0_before"]->Draw("peX0 same");
  g["RAA_D0_after"]->Draw("5 same");
  h["RAA_D0_after"]->Draw("pe1X0 same");
  leg["RAA_D0"]->Draw();
  xjjroot::saveas(drawTheoryRAApromptDcent010::canvas, "plots/"+conf->v("name")+"/cdrawTheoryRAApromptDcent010_proj.pdf");

  // V2
  drawTheoryV2promptDcent3050::drawcanvas();
  g["V2_D0_before"]->Draw("2 same");
  drawTheoryV2promptDcent3050::setupNdrawTheory();
  drawTheoryV2promptDcent3050::drawlegends();
  h["V2_D0_before"]->Draw("peX0 same");
  xjjroot::saveas(drawTheoryV2promptDcent3050::canvas, "plots/"+conf->v("name")+"/cdrawTheoryV2promptDcent3050_data.pdf");
  h["V2_D0_before"]->SetLineColor(kGray+1);
  h["V2_D0_before"]->Draw("peX0 same");
  g["V2_D0_after"]->Draw("5 same");
  h["V2_D0_after"]->Draw("pe1X0 same");
  leg["V2_D0"]->Draw();
  xjjroot::saveas(drawTheoryV2promptDcent3050::canvas, "plots/"+conf->v("name")+"/cdrawTheoryV2promptDcent3050_proj.pdf");

  // btoD RAA cent0100
  drawTheoryRAAbtoDcent0100::drawcanvas();
  g["RAA_btoD0_before"]->Draw("2 same");
  drawTheoryRAAbtoDcent0100::setupNdrawTheory();
  drawTheoryRAAbtoDcent0100::drawlegends();
  h["RAA_btoD0_before"]->Draw("peX0 same");
  xjjroot::saveas(drawTheoryRAAbtoDcent0100::canvas, "plots/"+conf->v("name")+"/cdrawTheoryRAAbtoDcent0100_data.pdf");
  h["RAA_btoD0_before"]->SetLineColor(kGray+1);
  h["RAA_btoD0_before"]->Draw("peX0 same");
  g["RAA_btoD0_after"]->Draw("5 same");
  h["RAA_btoD0_after"]->Draw("pe1X0 same");
  leg["RAA_btoD0"]->Draw();
  xjjroot::saveas(drawTheoryRAAbtoDcent0100::canvas, "plots/"+conf->v("name")+"/cdrawTheoryRAAbtoDcent0100_proj.pdf");

  // btoD RAA cent010
  drawTheoryRAAbtoDcent010::drawcanvas();
  drawTheoryRAAbtoDcent010::setupNdrawTheory();
  drawTheoryRAAbtoDcent010::drawlegends();
  xjjroot::saveas(drawTheoryRAAbtoDcent010::canvas, "plots/"+conf->v("name")+"/cdrawTheoryRAAbtoDcent010.pdf");

  // btoD V2
  drawTheoryV2btoDcent1030::drawcanvas();
  g["V2_btoD0_before"]->Draw("2 same");
  drawTheoryV2btoDcent1030::setupNdrawTheory();
  drawTheoryV2btoDcent1030::drawlegends();
  h["V2_btoD0_before"]->Draw("peX0 same");
  xjjroot::saveas(drawTheoryV2btoDcent1030::canvas, "plots/"+conf->v("name")+"/cdrawTheoryV2btoDcent1030_data.pdf");
  h["V2_btoD0_before"]->SetLineColor(kGray+1);
  h["V2_btoD0_before"]->Draw("peX0 same");
  g["V2_btoD0_after"]->Draw("5 same");
  h["V2_btoD0_after"]->Draw("pe1X0 same");
  leg["V2_btoD0"]->Draw();
  xjjroot::saveas(drawTheoryV2btoDcent1030::canvas, "plots/"+conf->v("name")+"/cdrawTheoryV2btoDcent1030_proj.pdf");

  return 0;
}

int main(int argc, char* argv[]) 
{ 
  if(argc==2)
    return drawTheory(argv[1]);
  return 1;
}

void setdata(xjjc::config* conf)
{
  float trkerr = 0.025; //minimum tracking syst (4% => 2.5%)

  float wlumi_RAA_D0_MB = std::sqrt(conf->vf("lumi_after_MB")/conf->vf("lumi_before_RAA_D0_MB")),
    wlumi_RAA_D0_Trigger = std::sqrt(conf->vf("lumi_after_Trigger")/conf->vf("lumi_before_RAA_D0_Trigger")),
    wlumi_V2_D0 = std::sqrt(conf->vf("lumi_after_MB")/conf->vf("lumi_before_V2_D0"));

  projection* proj_RAA_D0 = new projection(conf->v("input_RAA_D0"));
  sethist(proj_RAA_D0, "RAA_D0", 0.45, 0.45);
  project::scale(h["RAA_D0_after"], g["RAA_D0_after"], wlumi_RAA_D0_MB, wlumi_RAA_D0_Trigger, 20, 2*trkerr);

  projection* proj_RAA_btoD0 = new projection(conf->v("input_RAA_btoD0"));
  sethist(proj_RAA_btoD0, "RAA_btoD0", 0.25, 0.25);
  project::scale(h["RAA_btoD0_after"], g["RAA_btoD0_after"], wlumi_RAA_D0_MB, wlumi_RAA_D0_Trigger, 20, 2*trkerr);

  projection* proj_V2_D0 = new projection(conf->v("input_V2_D0"));
  sethist(proj_V2_D0, "V2_D0", 0.65, 0.60);
  project::scale(h["V2_D0_after"], g["V2_D0_after"], wlumi_V2_D0, wlumi_V2_D0, 0, 0);

  projection* proj_V2_btoD0 = new projection(conf->v("input_V2_btoD0"));
  sethist(proj_V2_btoD0, "V2_btoD0", 0.45, 0.30);
  project::scale(h["V2_btoD0_after"], g["V2_btoD0_after"], wlumi_V2_D0, wlumi_V2_D0, 0, 0);

}

void sethist(projection* proj, std::string name, float xleg, float yleg)
{
  h[name+"_before"] = (TH1F*)proj->hstat->Clone(Form("h%s_before", name.c_str()));
  h[name+"_after"] = (TH1F*)proj->hstat->Clone(Form("h%s_after", name.c_str()));
  g[name+"_before"] = (TGraphErrors*)proj->gsyst->Clone(Form("g%s_before", name.c_str()));
  g[name+"_after"] = (TGraphErrors*)proj->gsyst->Clone(Form("g%s_after", name.c_str()));
  xjjroot::setthgrstyle(h[name+"_before"], kBlack, 20, 1.1, kBlack, 1, 2);
  xjjroot::setthgrstyle(g[name+"_before"], kGray+1, 20, 1.1, 0, 0, 0, kGray, 1, 1001);
  xjjroot::setthgrstyle(h[name+"_after"], kBlack, 20, 1.1, kBlack, 1, 2, 0, 0, 0);
  xjjroot::setthgrstyle(g[name+"_after"], kBlack, 20, 1.1, kBlack, 1, 2, 0, 0, 0);
  leg[name] = new TLegend(xleg, yleg-0.04*2, xleg+0.2, yleg);
  xjjroot::setleg(leg[name], 0.031);
  leg[name]->AddEntry(g[name+"_before"], "Current", "ef");
  leg[name]->AddEntry(g[name+"_after"], "Run 3 lumi", "ef");
}
