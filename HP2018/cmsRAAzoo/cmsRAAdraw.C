#include "ChargedHad/RAA_0_10.C"
#include "ChargedHad/RAA_0_100.C"
#include "BmesonRaa/canvasRAAPbPb_0_100_ThmRAA.C"
#include "BtoDmesonRaa/canvasRAAPbPb_0_100_BtoDRAA.C"
#include "NonpromptJpsi/nonPrompt_276raa_20170201.h"
#include "NonpromptJpsi/nonPrompt_502raa_20170712.h"
#include "NonpromptJpsi/Prompt_502raa.h"
#include "systematics.h"

#include "cmsRAA.h"

void cmsRAAdraw(TString fileMB, TString file, Float_t centmin, Float_t centmax, 
                int isD, Int_t isHad, Int_t isB, Int_t isNjpsi, Int_t isND, Int_t isPjpsi,
                bool savepng=false)
{
  if(centmin!=0 || (centmax!=100 && (isB || isNjpsi || isND || isPjpsi))) { return; }

  gStyle->SetOptTitle(0);   
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  gStyle->SetLineWidth(2); 
  gStyle->SetFrameLineWidth(2);

  // prompt D0 -->  
  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");
  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  cmsRAA::setthgrstyle(gNuclearModification, kGreen+3, 21, 1, 1, 1, 1, kGreen-9, 0.7, 1001);
  cmsRAA::setthgrstyle(gNuclearModificationMB, kGreen+3, 21, 1, 1, 1, 1, kGreen-9, 0.7, 1001);
  cmsRAA::setthgrstyle(hNuclearModification, kGreen+3, 21, 1, 1, 1, 3);
  cmsRAA::setthgrstyle(hNuclearModificationMB, kGreen+3, 21, 1, 1, 1, 3);
  // <-- prompt D0

  TCanvas* canvasRAA = new TCanvas("canvasRAA", "canvasRAA", 600, 600);
  canvasRAA->cd();
  canvasRAA->SetFillColor(0);
  canvasRAA->SetBorderMode(0);
  canvasRAA->SetBorderSize(2);
  canvasRAA->SetLeftMargin(0.185);
  canvasRAA->SetRightMargin(0.025);
  canvasRAA->SetTopMargin(0.080);
  canvasRAA->SetBottomMargin(0.150);
  canvasRAA->SetFrameBorderMode(0);
  canvasRAA->SetLogx();

  Float_t xaxismin = 0.7; // 0.7, 1.0
  Float_t xaxismax = 400; // 150, 400
  TH2F* hemptyRAA = new TH2F("hemptyRAA", ";p_{T} (GeV/c);R_{AA}", 50, xaxismin, xaxismax, 10, 0, 1.75);
  cmsRAA::sethemptystyle(hemptyRAA, 1.10, 1.15, 0.06, 0.06, 0.045, 0.045);
  hemptyRAA->GetXaxis()->SetLabelOffset(0.0);
  hemptyRAA->Draw();

  cmsRAA::drawline(xaxismin, 1, xaxismax, 1, kBlack, 2, 2);

  /* <-- syst --> */
  // charged particles
  if(isHad==1)
    { if(centmin==0 && centmax==100) { RAA_0_100(); }
      if(centmin==0 && centmax==10) { RAA_0_10(); } }
  // prompt D0
  if(isD)
    { gNuclearModification->Draw("5same");
      gNuclearModificationMB->Draw("5same"); }
  // B+
  if(isB==1 && centmin==0 && centmax==100)
    { bplus::canvasRAAPbPb_0_100_ThmRAA(); }
  // nonprompt jpsi 2.76 TeV
  if(isNjpsi==2 && centmin==0 && centmax==100)
    { npjpsi2::expBeautyCMS_20170201(); }
  // nonprompt jpsi 5.02 TeV
  if(isNjpsi==1 && centmin==0 && centmax==100)
    { npjpsi5::expBeautyCMS(); }
  // nonprompt D0
  if(isND==1 && centmin==0 && centmax==100)
    { npd::canvasRAAPbPb_0_100_BtoDRAA(); }
  // nonprompt jpsi 5.02 TeV
  if(isPjpsi && centmin==0 && centmax==100)
    { pjpsi5::expBeautyCMS(); }

  /* <-- markers --> */
  if(isHad==1)
    { if(centmin==0 && centmax==100) { RAA_0_100_marker(); }
      if(centmin==0 && centmax==10) { RAA_0_10_marker(); } }
  if(isD)
    { hNuclearModification->Draw("5same");
      hNuclearModificationMB->Draw("5same"); }
  if(isB==1 && centmin==0 && centmax==100)
    { bplus::canvasRAAPbPb_0_100_ThmRAA_marker(); }
  if(isNjpsi==2 && centmin==0 && centmax==100)
    { npjpsi2::expBeautyCMS_20170201_marker(); }
  if(isNjpsi==1 && centmin==0 && centmax==100)
    { npjpsi5::expBeautyCMS_marker(); }
  if(isND==1 && centmin==0 && centmax==100)
    { npd::canvasRAAPbPb_0_100_BtoDRAA_marker(); }
  if(isPjpsi && centmin==0 && centmax==100)
    { pjpsi5::expBeautyCMS_marker(); }

  Float_t systnormup = normalizationUncertaintyForRAA(centmin, centmax, true)*1.e-2;
  Float_t systnormlo = normalizationUncertaintyForRAA(centmin, centmax, false)*1.e-2;
  TBox* bSystnorm = new TBox(xaxismin, 1-systnormlo, xaxismin+0.2, 1+systnormup);
  bSystnorm->SetLineColor(16);
  bSystnorm->SetFillColor(16);
  bSystnorm->Draw();

  TString tlumi_ = Form("%s%s%s", ((isD||isND)?"530/":""), (isHad?"404/":""), (isB||isNjpsi||isPjpsi?"368/":""));
  TString tlumi(tlumi_, tlumi_.Length()-1);
  cmsRAA::drawtex(0.96, 0.936, Form("5.02 TeV pp (27.4 pb^{-1}) + PbPb (%s #mub^{-1})", tlumi.Data()), 0.038, 31);
  cmsRAA::drawtex(0.22, 0.89, "#bf{CMS}#scale[0.6]{#it{ Supplementary}}", 0.062, 13);
  cmsRAA::drawtex(0.95, 0.27, "|y| < 1", 0.04, 32);
  cmsRAA::drawtex(0.955, 0.22, Form("Cent. %.0f-%.0f%s", centmin, centmax, "%"), 0.04, 32);

  // legend preset -- >
  const std::string theader[] = {"Light", "Charm", "Beauty", "Open charm"};
  int nlinel = -1, nliner = -1, itheaderl = -1, itheaderll = -1, itheaderr = -1;
  // charged + charm + beauty
  if(isHad && isD && isB && isNjpsi && isND && !isPjpsi) { nlinel = 3; nliner = 5; itheaderl = 0; itheaderll = 1; itheaderr = 2; }
  // charm only
  if(!isHad && isD && !isB && !isNjpsi && !isND && !isPjpsi) { nlinel = 1; nliner = 0; itheaderl = 1; itheaderll = -1; itheaderr = -1; }
  // beauty only
  if(!isHad && !isD && isB && isNjpsi && isND && !isPjpsi) { nlinel = 0; nliner = 5; itheaderl = -1; itheaderll = -1; itheaderr = 2; }
  // charm + beauty
  if(!isHad && isD && isB && isNjpsi && isND && !isPjpsi) { nlinel = 1; nliner = 5; itheaderl = 1; itheaderll = -1; itheaderr = 2; }
  // charm + charged
  if(isHad && isD && !isB && !isNjpsi && !isND && !isPjpsi) { nlinel = 3; nliner = 0; itheaderl = 0; itheaderll = 1; itheaderr = -1; }
  // beauty + charged
  if(isHad && !isD && isB && isNjpsi && isND && !isPjpsi) { nlinel = 1; nliner = 5; itheaderl = 0; itheaderll = -1; itheaderr = 2; }
  // charm + nonprompt jpsi
  if(!isHad && isD && !isB && isNjpsi && !isND && !isPjpsi) { nlinel = 1; nliner = 3; itheaderl = 1; itheaderll = -1; itheaderr = 2; }
  // charm + nonprompt D
  if(!isHad && isD && !isB && !isNjpsi && isND && !isPjpsi) { nlinel = 1; nliner = 1; itheaderl = 1; itheaderll = -1; itheaderr = 2; }
  // charm + prompt jpsi
  if(!isHad && isD && !isB && !isNjpsi && !isND && isPjpsi) { nlinel = 0; nliner = 5; itheaderl = -1; itheaderll = -1; itheaderr = 3; }
  // 
  // charged + charm + B + NPD
  if(isHad && isD && isB && !isNjpsi && isND && !isPjpsi) { nlinel = 3; nliner = 2; itheaderl = 0; itheaderll = 1; itheaderr = 2; }
  // charged + charm + B + NPjpsi
  if(isHad && isD && isB && isNjpsi && !isND && !isPjpsi) { nlinel = 3; nliner = 4; itheaderl = 0; itheaderll = 1; itheaderr = 2; }
  // charged + charm + B
  if(isHad && isD && isB && !isNjpsi && !isND && !isPjpsi) { nlinel = 3; nliner = 1; itheaderl = 0; itheaderll = 1; itheaderr = 2; }
  // D + B
  if(!isHad && isD && isB && !isNjpsi && !isND && !isPjpsi) { nlinel = 1; nliner = 1; itheaderl = 1; itheaderll = -1; itheaderr = 2; }
  // charged + charm + NPjpsi
  if(isHad && isD && !isB && isNjpsi && !isND && !isPjpsi) { nlinel = 3; nliner = 3; itheaderl = 0; itheaderll = 1; itheaderr = 2; }
  // charged + charm + NPD
  if(isHad && isD && !isB && !isNjpsi && isND && !isPjpsi) { nlinel = 3; nliner = 1; itheaderl = 0; itheaderll = 1; itheaderr = 2; }
  if(nlinel < 0 || nliner < 0) { std::cout << " \033[31;1mwarning: this combination is not predefiend: " 
                                           << isD << " " << isHad << " " << isB << " " << isNjpsi << " " << isND << " " << isPjpsi<< "\033[0m" << std::endl; return; }
  // <-- legend preset

  double legx1_r = 0.65, legx2_r = legx1_r + 0.460, legy2_r = 0.860 - (0.0486/2)*(5-nliner)*0.8, legy1_r = 0.617 + (0.0486/2)*(5-nliner)*1.2;
  double yheadderr = itheaderr>=0?legy2_r + 0.01:-1;
  double legx1_l = 0.22, legx2_l = legx1_l + 0.45, legy2_l = itheaderl>=0?0.78:0.82, legy1_l = legy2_l - 0.0468*nlinel;
  double yheadderl = itheaderl>=0?legy2_l + 0.01:-1, yheadderll = itheaderll>=0?yheadderl-0.0486*2:-1;

  TLegend* legendRAA_r = new TLegend(legx1_r, legy1_r, legx2_r, legy2_r, "");
  cmsRAA::setleg(legendRAA_r, 0.034);
  TLegend* legendRAA_l = new TLegend(legx1_l, legy1_l, legx2_l, legy2_l, "");
  cmsRAA::setleg(legendRAA_l, 0.034);
  
  if(isHad) 
    {
      legendRAA_l->AddEntry(gTrackPt_leg, "h^{#pm}", "pf");
      if(isD) { legendRAA_l->AddEntry((TObject*)0, "", NULL); }
    }
  if(isD)
    {
      TLegend* leg = isPjpsi?legendRAA_r:legendRAA_l;
      leg->AddEntry(gNuclearModification, "D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}", "pf");
    }
  if(isB && centmin==0 && centmax==100)
    { legendRAA_r->AddEntry(bplus::grae, "B^{#pm} |y| < 2.4", "pf"); } 

  if(isND)
    { legendRAA_r->AddEntry(npd::grae2, "(b #rightarrow) D^{0}", "pf"); }

  if(isNjpsi==2 && centmin==0 && centmax==100)
    {
      legendRAA_r->AddEntry((TObject*)0, "", NULL);
      legendRAA_r->AddEntry(npjpsi2::gre2TeV2, "1.6 < |y| < 2.4", "pf");
      legendRAA_r->AddEntry(npjpsi2::gre2TeV, "|y| < 2.4", "pf");
      cmsRAA::drawtex(legx1_r+0.02, legy1_r+0.0486*2+0.014, "(b #rightarrow) J/#psi (2.76 TeV)", 0.034, 11);
    }

  if(isNjpsi==1 && centmin==0 && centmax==100)
    {
      legendRAA_r->AddEntry((TObject*)0, "", NULL);
      legendRAA_r->AddEntry(npjpsi5::gre5TeV2, "1.8 < |y| < 2.4", "pf");
      legendRAA_r->AddEntry(npjpsi5::gre5TeV, "|y| < 2.4", "pf");
      cmsRAA::drawtex(legx1_r+0.02, legy1_r+0.0486*2+0.014, "(b #rightarrow) J/#psi", 0.034, 11);
    }

  if(isPjpsi && centmin==0 && centmax==100)
    {
      legendRAA_r->AddEntry((TObject*)0, "", NULL);
      legendRAA_r->AddEntry((TObject*)0, "", NULL);
      legendRAA_r->AddEntry(pjpsi5::gre5TeV2, "1.8 < |y| < 2.4", "pf");
      legendRAA_r->AddEntry(pjpsi5::gre5TeV, "|y| < 2.4", "pf");
      cmsRAA::drawtex(legx1_r+0.02, legy1_r+0.0486*3, "Hidden charm", 0.034, 11, 72);
      cmsRAA::drawtex(legx1_r+0.02, legy1_r+0.0486*2+0.01, "prompt J/#psi", 0.034, 11);
    }

  if(nliner) { legendRAA_r->Draw(); }
  if(nlinel) { legendRAA_l->Draw(); }

  if(yheadderr > 0) cmsRAA::drawtex(legx1_r+0.017, yheadderr, theader[itheaderr].c_str(), 0.034, -1, 72);
  if(yheadderl > 0) cmsRAA::drawtex(legx1_l+0.017, yheadderl, theader[itheaderl].c_str(), 0.034, -1, 72);
  if(yheadderll > 0) cmsRAA::drawtex(legx1_l+0.017, yheadderll, theader[itheaderll].c_str(), 0.034, -1, 72);
  
  cmsRAA::drawtex(0.23, 0.61, "T_{AA} and lumi.", 0.03, 12, 42, kGray+1);
  cmsRAA::drawtex(0.23, 0.58, "uncert.", 0.03, 12, 42, kGray+1);

  canvasRAA->Update();
  canvasRAA->RedrawAxis();

  TString texHad = isHad?"_charged":"";
  TString texD = isD?"_D":"";
  TString texB = isB?"_B":"";
  TString texNjpsi = isNjpsi>0?(isNjpsi==2?"_Njpsi2TeV":"_Njpsi5TeV"):"";
  TString texND = isND?"_BtoD":"";    
  TString texPjpsi = isPjpsi?"_Pjpsi5TeV":"";

  TString filename = Form("canvasRAA%s%s%s%s%s%s_cent_%.0f_%.0f", texHad.Data(), texD.Data(), texB.Data(), texNjpsi.Data(), texND.Data(), texPjpsi.Data(), centmin, centmax);
  canvasRAA->SaveAs(Form("plotRAA/%s.pdf", filename.Data()));
  if(savepng) canvasRAA->SaveAs(Form("plotRAA/%s.png", filename.Data()));

  std::cout<<"\033[33;1m| [[%ATTACHURL%/"<<filename<<".pdf][<img alt=\""<<filename<<".png\" src=\"%ATTACHURLPATH%/"<<filename<<".png\" width=\"200\" />]]\033[0m"<<std::endl;
}

int main(int argc, char *argv[])
{
  if(argc==11)
    {
      cmsRAAdraw(argv[1], argv[2], atof(argv[3]), atof(argv[4]), 
                 atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), atoi(argv[9]), atoi(argv[10]));
      return 0;
    }
  std::cout << "Wrong number of inputs" << std::endl;
  return 1;
}
