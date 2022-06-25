#include "drawTheoryRAA.h"
#include "drawTheoryV2.h"
#include "drawTheoryRAA_btoD.h"
#include "drawTheoryV2_btoD.h"
#include "config.h"
#include "projection.h"
#include "xjjrootuti.h"

TH1F *hRAA_D0_after, *hv2_D0_after;
TGraphErrors *gRAA_D0_after, *gv2_D0_after;
TLegend *legRAA, *legv2;
void setdata(xjjc::config* conf);

int drawTheory(std::string configuration)
{
  xjjc::config* conf = new xjjc::config(configuration);
  // setdata(conf);

  // RAA
  drawTheoryRAA::drawcanvas();
  drawTheoryRAA::setupNdrawTheory010();
  drawTheoryRAA::drawlegends();
  // gRAA_D0_after->Draw("5 same");
  // hRAA_D0_after->Draw("pe same");
  // legRAA->Draw();
  xjjroot::saveas(drawTheoryRAA::canvas, "plots/"+conf->v("name")+"/cRAA_theorycurves_promptD.pdf");

  // V2
  drawTheoryV2::drawcanvas();
  drawTheoryV2::setupNdrawTheory3050();
  drawTheoryV2::drawlegends();
  // gv2_D0_after->Draw("5 same");
  // hv2_D0_after->Draw("pe same");
  // legv2->Draw();
  xjjroot::saveas(drawTheoryV2::canvas, "plots/"+conf->v("name")+"/cv2_theorycurves_promptD.pdf");

  // btoD RAA
  drawTheoryRAAbtoD::drawcanvas();
  drawTheoryRAAbtoD::setupNdrawTheory0100();
  drawTheoryRAAbtoD::drawlegends();
  // gv2_D0_after->Draw("5 same");
  // hv2_D0_after->Draw("pe same");
  // legv2->Draw();
  xjjroot::saveas(drawTheoryRAAbtoD::canvas, "plots/"+conf->v("name")+"/cRAA_theorycurves_btoD.pdf");

  // btoD V2
  drawTheoryV2btoD::drawcanvas();
  drawTheoryV2btoD::setupNdrawTheory1030();
  drawTheoryV2btoD::drawlegends();
  // gv2_D0_after->Draw("5 same");
  // hv2_D0_after->Draw("pe same");
  // legv2->Draw();
  xjjroot::saveas(drawTheoryV2btoD::canvas, "plots/"+conf->v("name")+"/cv2_theorycurves_btoD.pdf");

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
    wlumi_v2_D0 = std::sqrt(conf->vf("lumi_after_MB")/conf->vf("lumi_before_v2_D0"));
  
  projection* proj_RAA_D0 = new projection(conf->v("input_RAA_D0_010"));
  hRAA_D0_after = (TH1F*)proj_RAA_D0->hstat->Clone("hRAA_D0_after");
  gRAA_D0_after = (TGraphErrors*)proj_RAA_D0->gsyst->Clone("gRAA_D0_after");
  project::scale(hRAA_D0_after, gRAA_D0_after, wlumi_RAA_D0_MB, wlumi_RAA_D0_Trigger, 20, 2*trkerr);
  xjjroot::setthgrstyle(hRAA_D0_after, kBlack, 21, 1.2, kBlack, 1, 2, 0, 0, 0);
  xjjroot::setthgrstyle(gRAA_D0_after, kBlack, 21, 1.2, kBlack, 1, 2, 0, 0, 0);
  legRAA = new TLegend(0.45, 0.45-0.05, 0.70, 0.45);
  xjjroot::setleg(legRAA, 0.031);
  legRAA->AddEntry(gRAA_D0_after, "CMS Run 3 Projection", "p");

  projection* proj_v2_D0 = new projection(conf->v("input_v2_D0"));
  hv2_D0_after = (TH1F*)proj_v2_D0->hstat->Clone("hv2_D0_after");
  gv2_D0_after = (TGraphErrors*)proj_v2_D0->gsyst->Clone("gv2_D0_after");
  project::scale(hv2_D0_after, gv2_D0_after, wlumi_v2_D0, wlumi_v2_D0, 0, 0);
  xjjroot::setthgrstyle(hv2_D0_after, kBlack, 21, 1.2, kBlack, 1, 2, 0, 0, 0);
  xjjroot::setthgrstyle(gv2_D0_after, kBlack, 21, 1.2, kBlack, 1, 2, 0, 0, 0);
  legv2 = new TLegend(0.57, 0.60-0.05, 0.82, 0.60);
  xjjroot::setleg(legv2, 0.031);
  legv2->AddEntry(gv2_D0_after, "CMS Run 3 Projection", "p");
}
