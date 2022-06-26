#include "drawTheoryRAA.h"
#include "drawTheoryV2.h"
#include "drawTheoryRAA_btoD.h"
#include "drawTheoryV2_btoD.h"
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
  drawTheoryRAA::drawcanvas();
  g["RAA_D0_before"]->Draw("2 same");
  drawTheoryRAA::setupNdrawTheory010();
  drawTheoryRAA::drawlegends();
  h["RAA_D0_before"]->Draw("peX0 same");
  xjjroot::saveas(drawTheoryRAA::canvas, "plots/"+conf->v("name")+"/cRAA_theorycurves_promptD.pdf");
  h["RAA_D0_before"]->SetLineColor(kGray+1);
  h["RAA_D0_before"]->Draw("peX0 same");
  g["RAA_D0_after"]->Draw("5 same");
  h["RAA_D0_after"]->Draw("pe1X0 same");
  leg["RAA_D0"]->Draw();
  xjjroot::saveas(drawTheoryRAA::canvas, "plots/"+conf->v("name")+"/cRAA_theorycurves_promptD_proj.pdf");

  // V2
  drawTheoryV2::drawcanvas();
  g["V2_D0_before"]->Draw("2 same");
  drawTheoryV2::setupNdrawTheory3050();
  drawTheoryV2::drawlegends();
  h["V2_D0_before"]->Draw("peX0 same");
  xjjroot::saveas(drawTheoryV2::canvas, "plots/"+conf->v("name")+"/cv2_theorycurves_promptD.pdf");
  h["V2_D0_before"]->SetLineColor(kGray+1);
  h["V2_D0_before"]->Draw("peX0 same");
  g["V2_D0_after"]->Draw("5 same");
  h["V2_D0_after"]->Draw("pe1X0 same");
  leg["V2_D0"]->Draw();
  xjjroot::saveas(drawTheoryV2::canvas, "plots/"+conf->v("name")+"/cv2_theorycurves_promptD_proj.pdf");

  // btoD RAA
  drawTheoryRAAbtoD::drawcanvas();
  g["RAA_btoD0_before"]->Draw("2 same");
  drawTheoryRAAbtoD::setupNdrawTheory0100();
  drawTheoryRAAbtoD::drawlegends();
  h["RAA_btoD0_before"]->Draw("peX0 same");
  xjjroot::saveas(drawTheoryRAAbtoD::canvas, "plots/"+conf->v("name")+"/cRAA_theorycurves_btoD.pdf");
  h["RAA_btoD0_before"]->SetLineColor(kGray+1);
  h["RAA_btoD0_before"]->Draw("peX0 same");
  g["RAA_btoD0_after"]->Draw("5 same");
  h["RAA_btoD0_after"]->Draw("pe1X0 same");
  leg["RAA_btoD0"]->Draw();
  xjjroot::saveas(drawTheoryRAAbtoD::canvas, "plots/"+conf->v("name")+"/cRAA_theorycurves_btoD_proj.pdf");

  // btoD V2
  drawTheoryV2btoD::drawcanvas();
  g["V2_btoD0_before"]->Draw("2 same");
  drawTheoryV2btoD::setupNdrawTheory1030();
  drawTheoryV2btoD::drawlegends();
  h["V2_btoD0_before"]->Draw("peX0 same");
  xjjroot::saveas(drawTheoryV2btoD::canvas, "plots/"+conf->v("name")+"/cv2_theorycurves_btoD.pdf");
  h["V2_btoD0_before"]->SetLineColor(kGray+1);
  h["V2_btoD0_before"]->Draw("peX0 same");
  g["V2_btoD0_after"]->Draw("5 same");
  h["V2_btoD0_after"]->Draw("pe1X0 same");
  leg["V2_btoD0"]->Draw();
  xjjroot::saveas(drawTheoryV2btoD::canvas, "plots/"+conf->v("name")+"/cv2_theorycurves_btoD_proj.pdf");

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
