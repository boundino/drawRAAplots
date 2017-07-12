using namespace std;
#include "uti.h"
#include "ChargedHad/RAA_0_10.C"
#include "ChargedHad/RAA_0_100.C"
#include "BmesonRaa/canvasRAAPbPb_0_100_ThmRAA.C"
#include "NonpromptJpsi/nonPrompt_276raa_20170201.h"
#include "drawTheory.h"

void CombineRAA(TString fileMB, TString file, Float_t centMin=0., Float_t centMax=10., Int_t isHadDupl=1, Int_t isBnNjpsi=1, Int_t isTheoryComparison=2)
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
  
  Int_t cimarker = TColor::GetColor("#006600");
  Int_t cifill = kGreen-9;
  gNuclearModification->SetFillStyle(1001);//0 
  gNuclearModification->SetFillColor(cifill);//1
  gNuclearModification->SetFillColorAlpha(cifill, 0.5);//1
  gNuclearModification->SetLineWidth(1);//3
  gNuclearModification->SetMarkerSize(1.2);
  gNuclearModification->SetMarkerStyle(21);
  gNuclearModification->SetLineColor(1);//kGreen+4
  gNuclearModification->SetMarkerColor(cimarker);//kGreen+4

  gNuclearModificationMB->SetFillStyle(1001);//0 
  gNuclearModificationMB->SetFillColor(cifill);//1
  gNuclearModificationMB->SetFillColorAlpha(cifill, 0.5);//1
  gNuclearModificationMB->SetLineWidth(1);//3
  gNuclearModificationMB->SetMarkerSize(1.2);
  gNuclearModificationMB->SetMarkerStyle(21);
  gNuclearModificationMB->SetLineColor(1);//kGreen+4
  gNuclearModificationMB->SetMarkerColor(cimarker);//kGreen+4
  
  hNuclearModification->SetLineWidth(3);
  hNuclearModification->SetMarkerSize(1.2);
  hNuclearModification->SetMarkerStyle(21);
  hNuclearModification->SetLineColor(1);//kGreen+4
  hNuclearModification->SetMarkerColor(cimarker);//kGreen+4

  hNuclearModificationMB->SetLineWidth(3);
  hNuclearModificationMB->SetMarkerSize(1.2);
  hNuclearModificationMB->SetMarkerStyle(21);
  hNuclearModificationMB->SetLineColor(1);//kGreen+4
  hNuclearModificationMB->SetMarkerColor(cimarker);//kGreen+4
  
  TCanvas* canvasRAA = new TCanvas("canvasRAA","canvasRAA",600,600);//550,500
  canvasRAA->cd();
  canvasRAA->SetFillColor(0);
  canvasRAA->SetBorderMode(0);
  canvasRAA->SetBorderSize(2);
  canvasRAA->SetLeftMargin(0.185);//0.200
  canvasRAA->SetRightMargin(0.025);
  canvasRAA->SetTopMargin(0.080);
  canvasRAA->SetBottomMargin(0.150);
  canvasRAA->SetFrameBorderMode(0);
  canvasRAA->SetLogx();

  Float_t xaxismin = isHadDupl==1?0.5:1.0;
  Float_t xaxismax = isHadDupl==1?700:150;
  TH2F* hemptyEff = new TH2F("hemptyEff","",50,xaxismin,xaxismax,10.,0,1.55);
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("R_{AA}");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(1.15);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.15);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(0.01);
  hemptyEff->SetMaximum(2);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();

  TLine* line = new TLine(xaxismin,1,xaxismax,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  if(isHadDupl==1)
    {
      if(centMin==0&&centMax==100) RAA_0_100();
      else if(centMin==0&&centMax==10) RAA_0_10();
      else
        {
          cout<<"ERROR: Invalid Centrality range"<<endl;
        }
    }

  gNuclearModification->Draw("5same");
  gNuclearModificationMB->Draw("5same");
  hNuclearModification->Draw("psame");//same
  hNuclearModificationMB->Draw("psame");//same

  if(isBnNjpsi==1) 
    {
      canvasRAAPbPb_0_100_ThmRAA();
      expBeautyCMS_20170201();
    }
  
  if(isHadDupl==1)
    {
      Float_t systnormCh, systnormD, systnormBhi, systnormBlo, systnormJhi, systnormJlo;
      if(centMax==100)
        {
          systnormCh = 0.0940744386111339;
          systnormD = 0.150734866570412;
          systnormBhi = 0.045662;
          systnormBlo = 0.041388;
          systnormJhi = 0.045662;
          systnormJlo = 0.041388;
        }
      if(centMax==10)
        {
          systnormCh = 0.0348998567332303;
          systnormD = 0.122837290754884;
        }
      TBox* bSystnormCh = new TBox(0.5,1-systnormCh,0.6,1+systnormCh);
      Int_t ci = TColor::GetColor("#ffcc00");
      bSystnormCh->SetLineColor(ci);
      bSystnormCh->SetFillColor(ci);
      bSystnormCh->Draw();
      TBox* bSystnormD = new TBox(0.6,1-systnormD,0.74,1+systnormD);
      bSystnormD->SetFillStyle(1001);
      bSystnormD->SetFillColor(cifill);//1
      bSystnormD->SetFillColorAlpha(cifill, 0.5);//1
      bSystnormD->SetLineColor(0);//1
      bSystnormD->Draw();
      if(isBnNjpsi==1 && centMax==100)
        {
          TBox* bSystnormB = new TBox(0.74,1-systnormBlo,0.9,1+systnormBhi);
          bSystnormB->SetFillStyle(1001);
          bSystnormB->SetFillColor(cifillB);//1
          bSystnormB->SetFillColorAlpha(cifillB, 0.5);//1
          bSystnormB->SetLineColor(0);//1
          bSystnormB->Draw();
          TBox* bSystnormJ = new TBox(0.9,1-systnormJlo,1.1,1+systnormJhi);
          bSystnormJ->SetFillStyle(1001);
          bSystnormJ->SetFillColor(cifillJ);//1
          bSystnormJ->SetFillColorAlpha(cifillJ, 0.5);//1
          bSystnormJ->SetLineColor(0);//1
          bSystnormJ->Draw();
        }
    }
  else
    {
      //Float_t systnorm = normalizationUncertaintyForRAA(centMin,centMax)*1.e-2;
      Float_t systnorm;
      if(centMax==100)
        {
          systnorm = 0.150734866570412;
        }
      if(centMax==10)
        {
          systnorm = 0.122837290754884;
        }
      TBox* bSystnorm = new TBox(1.0,1-systnorm,1.2,1+systnorm);
      bSystnorm->SetFillStyle(1001);
      bSystnorm->SetFillColor(cifill);//1
      bSystnorm->SetFillColorAlpha(cifill, 0.5);//1
      bSystnorm->SetLineColor(0);//1
      bSystnorm->Draw();
    }

  if(isTheoryComparison && centMin==0. && centMax==100.) drawTheory0100();
  if(isTheoryComparison && centMin==0. && centMax==10.) drawTheory010(isTheoryComparison);

  //

  TLatex* texlumi = new TLatex(0.19,0.936,"25.8 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)");
  texlumi->SetNDC();
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  TLatex* texcms = new TLatex(0.22,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.22,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.05);
  texpre->SetLineWidth(2);
  texpre->Draw();

  TString texper="%";
  TLatex * tlatexeff2 = new TLatex(0.955,0.22,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextAlign(32);
  tlatexeff2->SetTextSize(0.045);
  tlatexeff2->SetLineWidth(2);
  tlatexeff2->Draw();
  TLatex * texY = new TLatex(0.41,0.53,"|y| < 1");//0.2612903,0.8425793
  texY->SetNDC();
  texY->SetTextColor(1);
  texY->SetTextFont(42);
  texY->SetTextSize(0.045);
  texY->SetLineWidth(2);
  //texY->Draw();

  TLegend *legendSigma;
  if(isHadDupl==0 && isTheoryComparison==0) legendSigma = new TLegend(0.5436242,0.7474695,0.942953,0.8457592,"");
  if(isHadDupl==1 && isBnNjpsi==0 && isTheoryComparison==0) legendSigma = new TLegend(0.4436242,0.72,0.842953,0.88,"");
  if(isHadDupl==1 && isBnNjpsi==1 && isTheoryComparison==0) legendSigma = new TLegend(0.4436242+0.04,0.655,0.852953+0.04,0.9077592,"");
  if(isTheoryComparison==2||isTheoryComparison==3) legendSigma = new TLegend(0.5636242,0.6474695,0.912953,0.9057592,"");
  if(isHadDupl==0 && isTheoryComparison==1) legendSigma = new TLegend(0.5636242,0.6474695,0.912953,0.9057592,"");
  if(isHadDupl==1 && isTheoryComparison==1) legendSigma = new TLegend(0.5636242,0.6474695,0.912953,0.9057592,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(0);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.031);//0.05

  if(isHadDupl==1&&isTheoryComparison==0)
    {
      TLegendEntry *ent_Charged = legendSigma->AddEntry(hTrackPt_trkCorr_PbPb_copy1,"charged hadrons |y| < 1","p");//pf
      ent_Charged->SetTextFont(42);
      ent_Charged->SetLineColor(1);
      ent_Charged->SetMarkerColor(1);
      if(isBnNjpsi>0) ent_Charged->SetTextSize(0.035);//0.03
      else ent_Charged->SetTextSize(0.043);//0.03
    } 

  TString tDzero = (isHadDupl||isBnNjpsi)?"D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}} |y| < 1":"D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}";
  TLegendEntry *ent_Dhighpt = legendSigma->AddEntry(gNuclearModification,Form("%s",tDzero.Data()),"p");
  ent_Dhighpt->SetTextFont(42);
  ent_Dhighpt->SetLineColor(4);
  ent_Dhighpt->SetMarkerColor(4);
  ent_Dhighpt->SetTextSize(0.043);//0.03
  if(isBnNjpsi>0) ent_Dhighpt->SetTextSize(0.035);
  if(isTheoryComparison==1) ent_Dhighpt->SetTextSize(0.03);
    
  if(isBnNjpsi==1 && centMin==0 && centMax==100)
    {
      TLegendEntry* ent_BnNjpsi = legendSigma->AddEntry(grae,"B^{#pm} |y| < 2.4","p");
      ent_BnNjpsi->SetTextFont(42);
      ent_BnNjpsi->SetTextSize(0.035);
      TLegendEntry* ent_Njpsi = legendSigma->AddEntry((TObject*)0,"",NULL);
      ent_Njpsi->SetTextFont(42);
      ent_Njpsi->SetTextSize(0.035);
      TLegendEntry* ent_Njpsi1 = legendSigma->AddEntry(gre2,"1.8 < |y| < 2.4","p");
      ent_Njpsi1->SetTextFont(42);
      ent_Njpsi1->SetTextSize(0.035);
      TLegendEntry* ent_Njpsi2 = legendSigma->AddEntry(gre,"|y| < 2.4","p");
      ent_Njpsi2->SetTextFont(42);
      ent_Njpsi2->SetTextSize(0.035);
      TLatex* texNJpsi = new TLatex(0.587,0.75,"nonprompt J/#psi");
      texNJpsi->SetNDC();
      texNJpsi->SetTextColor(1);
      texNJpsi->SetTextFont(42);
      texNJpsi->SetTextSize(0.035);
      texNJpsi->Draw();
    }

  if(isTheoryComparison && centMin==0. && centMax==100.)
    {
      legendSigma->AddEntry(gShanshanD5TeV,"Cao et al. 0-80%","l");
      legendSigma->AddEntry(gMagdalenaD5TeV,"Djordjevic et al.","bf");
      legendSigma->AddEntry(gCUJETD5TeV,"CUJET 3.0","f");
      gADSCFT1D5TeV->SetLineColor(0);
      legendSigma->AddEntry(gADSCFT1D5TeV,"AdS/CFT HH D = const","f");
      gADSCFT2D5TeV->SetLineColor(0);
      legendSigma->AddEntry(gADSCFT2D5TeV,"AdS/CFT HH D(p)","f");
    }
  if(isTheoryComparison && centMin==0. && centMax==10.)
    {
      if(isTheoryComparison==1||isTheoryComparison==2)
        {
          legendSigma->AddEntry(gMagdalenaD5TeV,"Djordjevic et al.","bf");
          legendSigma->AddEntry(gCUJETD5TeV,"CUJET 3.0","f");//pf
          legendSigma->AddEntry(gIvanD5TeV,"Vitev et al. (g=1.9-2.0)","bf");
        }
      if (isTheoryComparison==1||isTheoryComparison==3)
        {
          legendSigma->AddEntry(gShanshanD5TeV,"Cao et al.","l");
          legendSigma->AddEntry(gPHSDWShadowing,"PHSD w/ shadowing ","l");
          legendSigma->AddEntry(gPHSDWOShadowing,"PHSD w/o shadowing ","l");
          gADSCFT1D5TeV->SetLineColor(0);
          legendSigma->AddEntry(gADSCFT1D5TeV,"AdS/CFT HH D = const","f");
          gADSCFT2D5TeV->SetLineColor(0);
          legendSigma->AddEntry(gADSCFT2D5TeV,"AdS/CFT HH D(p)","f");
        }
    }

  legendSigma->Draw();

  Float_t pxtexSystnorm;
  if(isHadDupl==0 && isBnNjpsi==0) pxtexSystnorm = 0.225;
  if(isHadDupl==1 && isBnNjpsi==0) pxtexSystnorm = 0.245;
  if(isHadDupl==1 && isBnNjpsi==1) pxtexSystnorm = 0.285;
  TLatex* texSystnorm = new TLatex(pxtexSystnorm,0.7,"T_{AA} + lumi.");
  texSystnorm->SetNDC();
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.035);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();
  texSystnorm = new TLatex(pxtexSystnorm,0.66,"uncertainty");
  texSystnorm->SetNDC();
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.035);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();

  canvasRAA->Update();
  canvasRAA->RedrawAxis();
  
  if(isHadDupl==0&&isTheoryComparison==0) canvasRAA->SaveAs(Form("plotRAA/canvasRAA_%.0f_%.0f.pdf",centMin,centMax));
  if(isHadDupl==1&&isBnNjpsi==0&&isTheoryComparison==0) canvasRAA->SaveAs(Form("plotRAA/canvasRAAchargedParticle_%.0f_%.0f.pdf",centMin,centMax));
  if(isHadDupl==1&&isBnNjpsi==1&&isTheoryComparison==0) canvasRAA->SaveAs(Form("plotRAA/canvasRAAchargedParticleBnNPjpsi_%.0f_%.0f.pdf",centMin,centMax));
  if(isTheoryComparison==1) canvasRAA->SaveAs(Form("plotRAA/canvasRAAComparisonTheoryAll_%.0f_%.0f.pdf",centMin,centMax));
  if(isTheoryComparison==2) canvasRAA->SaveAs(Form("plotRAA/canvasRAAComparisonTheoryQCD_%.0f_%.0f.pdf",centMin,centMax));
  if(isTheoryComparison==3) canvasRAA->SaveAs(Form("plotRAA/canvasRAAComparisonTheoryTransport_%.0f_%.0f.pdf",centMin,centMax));
}

int main(int argc, char *argv[])
{
  if(argc==8)
    {
      CombineRAA(argv[1], argv[2], atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
      return 0;
    }
  else
    { 
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}



