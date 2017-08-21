#include "uti.h"
#include "ChargedHad/RAA_0_10.C"
#include "ChargedHad/RAA_0_100.C"
#include "BmesonRaa/canvasRAAPbPb_0_100_ThmRAA.C"
#include "NonpromptJpsi/nonPrompt_276raa_20170201.h"
#include "AliceRaa/drawAliceD0Raa.h"
#include "StarRaa/drawStarD0Raa.h"
#include "systematics.h"
#include "drawTheory.h"
#include "PaperDraw.h"

void CombineRAA(TString fileMB="ROOTfilesCent10/outputRAAMB.root", TString file="ROOTfilesCent10/outputRAA.root", Float_t centmin=0., Float_t centmax=10., Int_t isHadDupl=1, Int_t isBnNjpsi=1, Int_t isTheoryComparison=2, Int_t isAlice=0, Bool_t verbose=false)
{
  gStyle->SetOptTitle(0);   
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");
  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  
  gNuclearModification->SetFillColor(kGreen-9);
  gNuclearModification->SetFillColorAlpha(kGreen-9, 0.7);
  gNuclearModification->SetFillStyle(1001);
  gNuclearModification->SetLineWidth(1);
  gNuclearModification->SetMarkerSize(1);
  gNuclearModification->SetMarkerStyle(21);
  gNuclearModification->SetLineColor(1);
  gNuclearModification->SetMarkerColor(kGreen+3);

  gNuclearModificationMB->SetFillColor(kGreen-9);
  gNuclearModificationMB->SetFillColorAlpha(kGreen-9, 0.7);
  gNuclearModificationMB->SetFillStyle(1001);
  gNuclearModificationMB->SetLineWidth(1);
  gNuclearModificationMB->SetMarkerSize(1);
  gNuclearModificationMB->SetMarkerStyle(21);
  gNuclearModificationMB->SetLineColor(1);
  gNuclearModificationMB->SetMarkerColor(kGreen+3);

  hNuclearModification->SetLineWidth(3);
  hNuclearModification->SetMarkerSize(1);
  hNuclearModification->SetMarkerStyle(21);
  hNuclearModification->SetLineColor(1);
  hNuclearModification->SetMarkerColor(kGreen+3);

  hNuclearModificationMB->SetLineWidth(3);
  hNuclearModificationMB->SetMarkerSize(1);
  hNuclearModificationMB->SetMarkerStyle(21);
  hNuclearModificationMB->SetLineColor(1);
  hNuclearModificationMB->SetMarkerColor(kGreen+3);

  TCanvas* canvasRAA = new TCanvas("canvasRAA","canvasRAA",600,600);
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

  Float_t xaxismin = (isHadDupl==1 || isAlice==1)?0.7:1.0;
  Float_t xaxismax = isHadDupl==1?400:150;
  TH2F* hemptyRAA = new TH2F("hemptyRAA",";p_{T} (GeV/c);R_{AA}", 50, xaxismin, xaxismax, 10, 0, 1.75);
  sethemptystyle(hemptyRAA, xtitleoffsetpRAA, ytitleoffsetpRAA, xtitlesizepRAA, ytitlesizepRAA, xlabelsizepRAA, ylabelsizepRAA);
  hemptyRAA->GetXaxis()->SetLabelOffset(0.0);
  hemptyRAA->Draw();

  TLine* line = new TLine(xaxismin, 1, xaxismax, 1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  if(isHadDupl==1)
    {
      if(centmin==0 && centmax==100) RAA_0_100();
      else if(centmin==0 && centmax==10) RAA_0_10();
      else return;
    }

  if(isBnNjpsi==1 && centmin==0 && centmax==100)
    {
      canvasRAAPbPb_0_100_ThmRAA();
      expBeautyCMS_20170201();
    }

  gNuclearModification->Draw("5same");
  gNuclearModificationMB->Draw("5same");  

  Float_t systnormup = normalizationUncertaintyForRAA(centmin,centmax,true)*1.e-2;
  Float_t systnormlo = normalizationUncertaintyForRAA(centmin,centmax,false)*1.e-2;
  TBox* bSystnorm = new TBox(xaxismin,1-systnormlo,xaxismin+0.2,1+systnormup);
  bSystnorm->SetLineColor(16);
  bSystnorm->SetFillColor(16);
  bSystnorm->Draw();

  if(isTheoryComparison && centmin==0 && centmax==100) drawTheory0100();
  if(isTheoryComparison && centmin==0 && centmax==10) drawTheory010(isTheoryComparison);
  
  hNuclearModification->Draw("psame");
  hNuclearModificationMB->Draw("psame");

  if(isAlice==1 && centmin==0 && centmax==10)
    {
      drawAliceD0Raa();
      drawStarD0Raa();
    }

  TLatex* texlumi = new TLatex(LumixposRAA, LumiyposRAA, "27.4 pb^{-1} (5.02 TeV pp) + 530 #mub^{-1} (5.02 TeV PbPb)");
  settex(texlumi, LumisizeRAA, 31);
  texlumi->Draw();
  TLatex* texcms = new TLatex(CMSxposRAA, CMSyposRAA, "CMS");
  settex(texcms, CMSsizeRAA, 13, 62);
  texcms->Draw();
  TLatex* texDzero = new TLatex(DZEROxposRAA, DZEROyposRAA, "D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
  settex(texDzero, DZEROsizeRAA, 13, 62);
  if(!(isBnNjpsi==1||isHadDupl==1)) texDzero->Draw();
  TString texper="%";
  TLatex * texY = new TLatex(0.95, 0.27, Form("|y| < 1",centmin,centmax,texper.Data()));
  settex(texY, 0.045, 32);
  texY->Draw();
  TLatex * tlatexcent = new TLatex(0.955, 0.22, Form("Cent. %.0f-%.0f%s",centmin,centmax,texper.Data()));
  settex(tlatexcent, 0.045, 32);
  tlatexcent->Draw();

  Double_t legx1[]      = {0.654,          0.594,          0.554,          0.574,          0.574};
  Double_t legy1[]      = {0.800,          0.760,          0.617,          0.647,          0.597};
  Double_t legx2[]      = {legx1[0]+0.419, legx1[1]+0.460, legx1[2]+0.460, legx1[3]+0.389, legx1[4]+0.389};
  Double_t legy2[]      = {0.890,          0.890,          0.906,          0.906,          0.906};
  Double_t legtexsize[] = {0.043,          0.035,          0.035,          0.030,          0.030};

  Int_t pindx = -1;
  // D RAA only
  if(isHadDupl==0 && isTheoryComparison==0) pindx = 0;
  // D and charged particles || compare Alice
  if((isHadDupl==1 && isBnNjpsi==0) || (isAlice==1 && isHadDupl==0 && isBnNjpsi==0)) pindx = 1;
  // D, B, jpsi and charged particles
  if(isHadDupl==1 && isBnNjpsi==1) pindx = 2;
  // separate theories
  if(isTheoryComparison==2||isTheoryComparison==3) pindx = 3;
  // all theories
  if(isTheoryComparison==1) pindx = 4;
  if(pindx<0) return;

  TLegend* legendRAA = new TLegend(legx1[pindx], legy1[pindx], legx2[pindx], legy2[pindx], "");
  setleg(legendRAA, legtexsize[pindx]);
  
  TString str_ent_Dzero = (isHadDupl==1 || isBnNjpsi==1)?"D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}":"R_{AA}";
  legendRAA->AddEntry(gNuclearModification, str_ent_Dzero, "pf");
  
  if(isHadDupl==1) legendRAA->AddEntry(gTrackPt_leg, "charged hadrons", "pf");

  if(isBnNjpsi==1 && centmin==0 && centmax==100)
    {
      legendRAA->AddEntry(grae, "B^{#pm} |y| < 2.4", "pf");
      legendRAA->AddEntry((TObject*)0, "", NULL);
      legendRAA->AddEntry(gre2, "1.6 < |y| < 2.4", "pf");
      legendRAA->AddEntry(gre, "|y| < 2.4", "pf");
      TLatex* texNJpsi = new TLatex(0.57, 0.728, "nonprompt J/#psi (2.76 TeV)");
      texNJpsi->SetNDC();
      texNJpsi->SetTextColor(1);
      texNJpsi->SetTextFont(42);
      texNJpsi->SetTextSize(0.035);
      texNJpsi->Draw();
    } 

  if(isAlice==1) legendRAA->AddEntry(grRAAalicesyst, "ALICE |y| < 0.5","pf");

  if(isTheoryComparison && centmin==0. && centmax==100.)
    {
      legendRAA->AddEntry(gShanshanD5TeV, "Cao et al. 0-80%", "l");
      legendRAA->AddEntry(gMagdalenaD5TeV, "Djordjevic et al.", "bf");
      legendRAA->AddEntry(gCUJETD5TeV, "CUJET 3.0", "f");
      gADSCFT1D5TeV->SetLineColor(0);
      legendRAA->AddEntry(gADSCFT1D5TeV, "AdS/CFT HH D = const", "f");
      gADSCFT2D5TeV->SetLineColor(0);
      legendRAA->AddEntry(gADSCFT2D5TeV, "AdS/CFT HH D(p)", "f");
    }
  if(isTheoryComparison && centmin==0. && centmax==10.)
    {
      if(isTheoryComparison==1||isTheoryComparison==2)
        {
          legendRAA->AddEntry(gMagdalenaD5TeV, "Djordjevic et al.", "bf");
          legendRAA->AddEntry(gCUJETD5TeV, "CUJET 3.0", "f");
          legendRAA->AddEntry(gIvanD5TeV, "Vitev et al. (g=1.9-2.0)", "bf");
        }
      if (isTheoryComparison==1||isTheoryComparison==3)
        {
          legendRAA->AddEntry(gShanshanD5TeV, "Cao et al.", "l");
          legendRAA->AddEntry(gPHSDWShadowing, "PHSD w/ shadowing ", "l");
          legendRAA->AddEntry(gPHSDWOShadowing, "PHSD w/o shadowing ", "l");
          gADSCFT1D5TeV->SetLineColor(0);
          legendRAA->AddEntry(gADSCFT1D5TeV, "AdS/CFT HH D = const", "f");
          gADSCFT2D5TeV->SetLineColor(0);
          legendRAA->AddEntry(gADSCFT2D5TeV, "AdS/CFT HH D(p)", "f");
        }
    }
  legendRAA->Draw();  
  
  TLatex* texSystnorm = new TLatex(0.23,0.64,"T_{AA} and lumi.");
  texSystnorm->SetNDC();
  texSystnorm->SetTextColor(1);
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.04);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();
  texSystnorm = new TLatex(0.23,0.60,"uncertainty");
  texSystnorm->SetNDC();
  texSystnorm->SetTextColor(1);
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.04);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();

  canvasRAA->Update();
  canvasRAA->RedrawAxis();

  TString texHadDupl = (isHadDupl==1)?"_charged":"";
  TString texBnNjpsi = (isBnNjpsi==1)?"_BnNjpsi":"";
  TString texAlice = (isAlice==1)?"_AliceComparison":"";
  TString texTheories[3] = {"All","QCD","Transport"};
  TString texTheory = (isTheoryComparison>0)?Form("_theory%s",texTheories[isTheoryComparison-1].Data()):"";

  canvasRAA->SaveAs(Form("plotRAA/canvasRAA%s%s%s%s_cent_%.0f_%.0f.pdf",texAlice.Data(),texHadDupl.Data(),texBnNjpsi.Data(),texTheory.Data(),centmin,centmax));
  if(isHadDupl==0&&isTheoryComparison==0&&isAlice==0&&isBnNjpsi==0) canvasRAA->SaveAs(Form("plotRAA/canvasRAA_cent_%.0f_%.0f.C",centmin,centmax));

  if(verbose)
    {
      for(int i=0;i<(hNuclearModificationMB->GetSize()-2);i++) 
        {
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModificationMB->GetBinCenter(i+1)-hNuclearModificationMB->GetBinWidth(i+1)/2.;
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModificationMB->GetBinCenter(i+1)+hNuclearModificationMB->GetBinWidth(i+1)/2.;
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModificationMB->GetBinCenter(i+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModificationMB->GetBinContent(i+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModificationMB->GetBinError(i+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<gNuclearModificationMB->GetErrorYhigh(i);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<gNuclearModificationMB->GetErrorYlow(i)<<std::endl;
        }
      for(int i=0;i<(hNuclearModification->GetSize()-2);i++)
        {
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModification->GetBinCenter(i+1)-hNuclearModification->GetBinWidth(i+1)/2.;
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModification->GetBinCenter(i+1)+hNuclearModification->GetBinWidth(i+1)/2.;
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModification->GetBinCenter(i+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModification->GetBinContent(i+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hNuclearModification->GetBinError(i+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<gNuclearModification->GetErrorYhigh(i);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<gNuclearModification->GetErrorYlow(i)<<std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
  if(argc==9)
    {
      CombineRAA(argv[1], argv[2], atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]));
      return 0;
    }
  else
    { 
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}
