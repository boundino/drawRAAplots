#include "uti.h"
#include "systematics.C"

void CombineCrossSections(TString fileMB="ROOTfiles/CrossSectionFONLLPPMB.root", TString file="ROOTfiles/CrossSectionFONLLPP.root", Int_t isPbPb=0, Float_t centMin=0., Float_t centMax=100.)
{

  bool doComparisonLHC=false;
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TString texPbPb = "PbPb";
  if(isPbPb==0) texPbPb = "PP";

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstatMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsystMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSystMB = (TGraphAsymmErrors*)filePPMB->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReferenceMB = (TGraphAsymmErrors*)filePPMB->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunityMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaPPStatMB = (TH1D*)filePPMB->Get("hPtSigma");
  TH1D* hfPromptMB = (TH1D*)filePPMB->Get("hfprompt");

  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstat = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsyst = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSyst = (TGraphAsymmErrors*)filePP->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)filePP->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunity = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaPPStat = (TH1D*)filePP->Get("hPtSigma");
  TH1D* hfPrompt = (TH1D*)filePP->Get("hfprompt");


  TCanvas* cSigma = new TCanvas("cSigma","",750,750);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigma->SetFillColor(0);
  cSigma->SetBorderMode(0);
  cSigma->SetBorderSize(2);
  cSigma->SetLeftMargin(0.12);//0.1451613
  cSigma->SetRightMargin(0.03);//0.05443548
  cSigma->SetTopMargin(0.07);//0.08474576
  cSigma->SetBottomMargin(0.15);//0.1165254
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetLogx();
  cSigma->cd();
  TPad* pSigma = new TPad("pSigma","",0,0.30,1,1);
  pSigma->SetFillColor(0);
  pSigma->SetBorderMode(0);
  pSigma->SetBorderSize(2);
  pSigma->SetLeftMargin(0.12);//0.1451613
  pSigma->SetRightMargin(0.03);//0.05443548
  pSigma->SetTopMargin(0.07);//0.08474576
  pSigma->SetBottomMargin(0);
  pSigma->SetLogy();
  pSigma->SetLogx();
  pSigma->Draw();
  pSigma->cd();

  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1.1,1.e10);  
  hemptySigma->GetXaxis()->CenterTitle();
  hemptySigma->GetYaxis()->CenterTitle();
  hemptySigma->GetYaxis()->SetTitle("d#sigma / dp_{T}( pb GeV^{-1}c)");
  if(isPbPb==1) hemptySigma->GetYaxis()->SetTitle("1/T_{AA} * dN / dp_{T}( pb GeV^{-1}c)");
  hemptySigma->GetXaxis()->SetTitleOffset(0.7);
  hemptySigma->GetYaxis()->SetTitleOffset(0.9);//1.3
  hemptySigma->GetXaxis()->SetTitleSize(0.05);
  hemptySigma->GetYaxis()->SetTitleSize(0.055);
  hemptySigma->GetXaxis()->SetTitleFont(42);
  hemptySigma->GetYaxis()->SetTitleFont(42);
  hemptySigma->GetXaxis()->SetLabelFont(42);
  hemptySigma->GetYaxis()->SetLabelFont(42);
  hemptySigma->GetXaxis()->SetLabelSize(0.04);
  hemptySigma->GetYaxis()->SetLabelSize(0.045);  
  hemptySigma->SetMaximum(2);
  hemptySigma->SetMinimum(0.);
  hemptySigma->Draw();

  gaeBplusReferenceMB->SetFillColor(5);//2
  gaeBplusReferenceMB->SetFillStyle(1001);//3001 
  gaeBplusReferenceMB->SetLineWidth(1);//3
  gaeBplusReferenceMB->SetLineColor(4);//2
  gaeBplusReferenceMB->Draw("5same");
  gaeBplusReference->SetFillColor(5);//2
  gaeBplusReference->SetFillStyle(1001);//3001 
  gaeBplusReference->SetLineWidth(1);//3
  gaeBplusReference->SetLineColor(4);//2
  gaeBplusReference->Draw("5same");

  hSigmaPPStatMB->SetLineWidth(2);
  hSigmaPPStatMB->SetMarkerSize(1);//4
  hSigmaPPStatMB->SetMarkerStyle(20);
  hSigmaPPStatMB->SetLineColor(1);//kGreen+4
  hSigmaPPStatMB->SetMarkerColor(1);//kGreen+4
  hSigmaPPStatMB->Draw("epsame"); 

  hSigmaPPStat->SetLineWidth(2);
  hSigmaPPStat->SetMarkerSize(1);//4
  hSigmaPPStat->SetMarkerStyle(20);
  hSigmaPPStat->SetLineColor(1);//kGreen+4
  hSigmaPPStat->SetMarkerColor(1);//kGreen+4
  hSigmaPPStat->Draw("epsame"); 

  gaeCrossSystMB->SetFillColor(1);
  gaeCrossSystMB->SetFillStyle(0); 
  gaeCrossSystMB->SetLineWidth(2);
  gaeCrossSystMB->SetLineColor(1);//kGreen+4
  gaeCrossSystMB->Draw("5same");  

  gaeCrossSyst->SetFillColor(1);
  gaeCrossSyst->SetFillStyle(0); 
  gaeCrossSyst->SetLineWidth(2);
  gaeCrossSyst->SetLineColor(1);//kGreen+4
  gaeCrossSyst->Draw("5same");  

  TString texper="%";
  TLatex* texCent = new TLatex(0.55,0.85,Form("Centrality %.0f - %.0f%s",centMin,centMax,texper.Data()));
  texCent->SetNDC();
  texCent->SetTextFont(42);
  texCent->SetTextSize(0.045);
  if(isPbPb==1) texCent->Draw();

  TLatex* texY = new TLatex(0.55,0.79,"|y| < 1.0");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.045);
  texY->SetLineWidth(2);
  texY->Draw();

  Float_t systnorm;
  if(isPbPb==1) systnorm = normalizationUncertaintyForPbPb(centMin,centMax);
  else systnorm = normalizationUncertaintyForPP();
  TLatex* texSystnorm = new TLatex(0.55,0.61,Form("Global uncert. %.1f%s",systnorm,texper.Data()));
  texSystnorm->SetNDC();
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.045);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();

  TLegend *legendSigma=new TLegend(0.54,0.66,0.87,0.77,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);


  TLegendEntry *ent_SigmaPPMB = legendSigma->AddEntry(hSigmaPPStatMB,"data","pf");
  ent_SigmaPPMB->SetTextFont(42);
  ent_SigmaPPMB->SetLineColor(2);
  ent_SigmaPPMB->SetMarkerColor(2);

  TLegendEntry *ent_SigmaFONLL = legendSigma->AddEntry(gaeBplusReferenceMB,"FONLL pp ref.","f");
  ent_SigmaFONLL->SetTextFont(42);
  ent_SigmaFONLL->SetLineColor(5);
  ent_SigmaFONLL->SetMarkerColor(1);
  legendSigma->Draw("same");
   
  TLatex * tlatex1;
  if(isPbPb==0) tlatex1 = new TLatex(0.95,0.96,"25.8 pb^{-1} (5.02 TeV pp)");
  else tlatex1 = new TLatex(0.95,0.96,"404 #mub^{-1} (5.02 TeV PbPb)");
  tlatex1->SetNDC();
  tlatex1->SetTextAlign(32);
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();

  TLatex* texcms = new TLatex(0.15,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.15,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  cSigma->cd();
  TPad* pRatio = new TPad("pRatio","",0,0,1,0.30);
  pRatio->SetLeftMargin(0.12);//0.1451613
  pRatio->SetRightMargin(0.03);//0.05443548
  pRatio->SetTopMargin(0);
  pRatio->SetBottomMargin(0.33);//0.25
  pRatio->SetLogx();
  pRatio->Draw();
  pRatio->cd();

  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,0.,110.,10.,0.,2.7);//50,0.,110.,10.,0.,4
  hemptyRatio->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Data / FONLL");
  hemptyRatio->GetXaxis()->SetTitleOffset(1.0);//0.9
  hemptyRatio->GetYaxis()->SetTitleOffset(0.4);//0.5
  hemptyRatio->GetXaxis()->SetTitleSize(0.13);//0.12
  hemptyRatio->GetYaxis()->SetTitleSize(0.12);
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelOffset(0.015);
  hemptyRatio->GetXaxis()->SetLabelSize(0.1);
  hemptyRatio->GetYaxis()->SetLabelSize(0.1);  

  hemptyRatio->Draw();

  TLine* l = new TLine(2.2,1,110,1);//10,1,105,1
  l->SetLineWidth(1);
  l->SetLineStyle(2);

  gaeRatioCrossFONLLunityMB->SetFillColor(5);
  gaeRatioCrossFONLLunityMB->SetFillStyle(1001);
  gaeRatioCrossFONLLunityMB->SetLineWidth(1);
  gaeRatioCrossFONLLunityMB->SetLineColor(4);
  gaeRatioCrossFONLLunityMB->Draw("5same");
  
  
  if(doComparisonLHC){
  const int nBinsATLAS=9;
  double ptBinsATLAS[nBinsATLAS+1] = {3.5,5.0,6.5,8.0,12.0,20.0,30.,40.,60.,100.};
  double ptBinscenterATLAS[nBinsATLAS];
  double zerosATLAS[nBinsATLAS];

  const int nBinsALICE=9;
  double ptBinsALICE[nBinsALICE+1] = {1.,2.,3.,4.,5.,6.,7.,8.,12.,16.};
  double ptBinscenterALICE[nBinsALICE];
  double zerosALICE[nBinsALICE];

  double valuesALICE[nBinsALICE]={1.6,1.75,1.8,1.75,1.5,1.4,1.2,1.4,1.1};
  double errorsvaluesALICEup[nBinsALICE]={0.5,0.25,0.3,0.3,0.25,0.25,0.25,0.23,0.23};
  double errorsvaluesALICElow[nBinsALICE]={1.0,0.5,0.3,0.3,0.25,0.25,0.25,0.23,0.23};

  double valuesATLAS[nBinsATLAS]={1./0.55,1./0.5,1./0.55,1./0.54,1./0.8,1./0.7,1./0.7,1./0.7,1./0.7};
  double errorsvaluesATLASup[nBinsATLAS];
  double errorsvaluesATLASlow[nBinsATLAS];
  
  errorsvaluesATLASup[0]=valuesATLAS[0]*0.15;
  errorsvaluesATLASlow[0]=valuesATLAS[0]*0.15;
  errorsvaluesATLASup[1]=valuesATLAS[1]*0.12;
  errorsvaluesATLASlow[1]=valuesATLAS[1]*0.12;
  errorsvaluesATLASup[2]=valuesATLAS[2]*0.10;
  errorsvaluesATLASlow[2]=valuesATLAS[2]*0.10;
  errorsvaluesATLASup[3]=valuesATLAS[3]*0.17;
  errorsvaluesATLASlow[3]=valuesATLAS[3]*0.17;
  errorsvaluesATLASup[4]=valuesATLAS[4]*0.10;
  errorsvaluesATLASlow[4]=valuesATLAS[4]*0.10;
  errorsvaluesATLASup[5]=valuesATLAS[5]*0.10;
  errorsvaluesATLASlow[5]=valuesATLAS[5]*0.10;
  errorsvaluesATLASup[6]=valuesATLAS[6]*0.12;
  errorsvaluesATLASlow[6]=valuesATLAS[6]*0.12;
  errorsvaluesATLASup[7]=valuesATLAS[7]*0.10;
  errorsvaluesATLASlow[7]=valuesATLAS[7]*0.10;
  errorsvaluesATLASup[8]=valuesATLAS[8]*0.2;
  errorsvaluesATLASlow[8]=valuesATLAS[8]*0.2;

  double aptlATLAS[nBinsATLAS];
  double aptlALICE[nBinsALICE];
  
  for (int i=0;i<nBinsATLAS;i++){
  ptBinscenterATLAS[i]=(ptBinsATLAS[i]+ptBinsATLAS[i+1])/2.;
  ptBinscenterALICE[i]=(ptBinsALICE[i]+ptBinsALICE[i+1])/2.;
  zerosATLAS[i]=0.;
  zerosALICE[i]=0.;
  aptlATLAS[i] = (ptBinsATLAS[i+1]-ptBinsATLAS[i])/2;
  aptlALICE[i] = (ptBinsALICE[i+1]-ptBinsALICE[i])/2;
  }
    
  TGraphAsymmErrors* gaeCrossSystATLAS = new TGraphAsymmErrors(nBinsATLAS,ptBinscenterATLAS,valuesATLAS,aptlATLAS,aptlATLAS,errorsvaluesATLASlow,errorsvaluesATLASup);
  gaeCrossSystATLAS->SetName("gaeCrossSystATLAS");
  gaeCrossSystATLAS->SetLineWidth(2);
  gaeCrossSystATLAS->SetLineColor(kRed);
  gaeCrossSystATLAS->SetFillColor(kRed);
  gaeCrossSystATLAS->SetFillStyle(3002);
  gaeCrossSystATLAS->Draw("5same");
  
  TGraphAsymmErrors* gaeCrossSystALICE = new TGraphAsymmErrors(nBinsALICE,ptBinscenterALICE,valuesALICE,aptlALICE,aptlALICE,errorsvaluesALICElow,errorsvaluesALICEup);
  gaeCrossSystALICE->SetName("gaeCrossSystALICE");
  gaeCrossSystALICE->SetLineWidth(2);
  gaeCrossSystALICE->SetLineColor(kBlue);
  gaeCrossSystALICE->SetFillColor(kBlue);
  gaeCrossSystALICE->SetFillStyle(3002);
  gaeCrossSystALICE->Draw("5same");
  
  TLegend *legendOtherexp=new TLegend(0.5385906,0.6925208,0.8691275,0.9252078,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendOtherexp->SetBorderSize(0);
  legendOtherexp->SetLineColor(0);
  legendOtherexp->SetFillColor(0);
  legendOtherexp->SetFillStyle(1001);
  legendOtherexp->SetTextFont(42);
  legendOtherexp->SetTextSize(0.055);

  TLegendEntry *entATLAS = legendOtherexp->AddEntry(gaeCrossSystATLAS,"ATLAS 7 TeV (|y|<2)","pf");
  entATLAS->SetTextFont(42);
  entATLAS->SetLineColor(kRed);
  entATLAS->SetMarkerColor(kRed);
  entATLAS->SetTextColor(kRed);

  TLegendEntry *entALICE = legendOtherexp->AddEntry(gaeCrossSystALICE,"ALICE 7 TeV (|y|<0.5)","pf");
  entALICE->SetTextFont(42);
  entALICE->SetLineColor(kBlue);
  entALICE->SetMarkerColor(kBlue);
  entALICE->SetTextColor(kBlue);
  legendOtherexp->Draw();
  }
  
  gaeRatioCrossFONLLstatMB->SetMarkerSize(1);
  gaeRatioCrossFONLLstatMB->SetLineWidth(2);
  gaeRatioCrossFONLLstatMB->SetLineColor(1);//kGreen+4 
  gaeRatioCrossFONLLstatMB->SetMarkerColor(1);//kGreen+4

  gaeRatioCrossFONLLstatMB->Draw("epsame");

  gaeRatioCrossFONLLsystMB->SetLineWidth(3);
  gaeRatioCrossFONLLsystMB->SetLineColor(1);//kGreen+4
  gaeRatioCrossFONLLsystMB->Draw("5same");

  gaeRatioCrossFONLLunity->SetFillColor(5);
  gaeRatioCrossFONLLunity->SetFillStyle(1001);
  gaeRatioCrossFONLLunity->SetLineWidth(1);
  gaeRatioCrossFONLLunity->SetLineColor(4);
  gaeRatioCrossFONLLunity->Draw("5same");

  gaeRatioCrossFONLLstat->SetMarkerSize(1);
  gaeRatioCrossFONLLstat->SetLineWidth(2);
  gaeRatioCrossFONLLstat->SetLineColor(1);//kGreen+4
  gaeRatioCrossFONLLstat->SetMarkerColor(1);//kGreen+4
   
  gaeRatioCrossFONLLstat->Draw("epsame");

  gaeRatioCrossFONLLsyst->SetLineWidth(3);
  gaeRatioCrossFONLLsyst->SetLineColor(1);//kGreen+4
  gaeRatioCrossFONLLsyst->Draw("5same");

  l->Draw("same");
  if(!doComparisonLHC){
  if(isPbPb==1) cSigma->SaveAs(Form("plotCrossSection/CrossSectionComparison_%s_%.0f_%.0f.pdf",texPbPb.Data(),centMin,centMax));
  else cSigma->SaveAs(Form("plotCrossSection/CrossSectionComparison_%s.pdf",texPbPb.Data()));
  }
  else{
  if(isPbPb==1) cSigma->SaveAs(Form("plotCrossSection/CrossSectionComparisonExperiments_%s_%.0f_%.0f.pdf",texPbPb.Data(),centMin,centMax));
  else cSigma->SaveAs(Form("plotCrossSection/CrossSectionComparisonExperiments_%s.pdf",texPbPb.Data()));  
  }
  
  TCanvas* cFprompt = new TCanvas("cFprompt","",550,500);
  TH2F* hemptyPrompt=new TH2F("hemptyPrompt","",50,0.,110.,10.,0,1.3);  
  hemptyPrompt->GetXaxis()->CenterTitle();
  hemptyPrompt->GetYaxis()->CenterTitle();
  hemptyPrompt->GetYaxis()->SetTitle("f_{prompt}");
  hemptyPrompt->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyPrompt->GetXaxis()->SetTitleOffset(0.9);
  hemptyPrompt->GetYaxis()->SetTitleOffset(1.05);
  hemptyPrompt->GetXaxis()->SetTitleSize(0.045);
  hemptyPrompt->GetYaxis()->SetTitleSize(0.045);
  hemptyPrompt->GetXaxis()->SetTitleFont(42);
  hemptyPrompt->GetYaxis()->SetTitleFont(42);
  hemptyPrompt->GetXaxis()->SetLabelFont(42);
  hemptyPrompt->GetYaxis()->SetLabelFont(42);
  hemptyPrompt->GetXaxis()->SetLabelSize(0.04);
  hemptyPrompt->GetYaxis()->SetLabelSize(0.04);  
  hemptyPrompt->SetMaximum(2);
  hemptyPrompt->SetMinimum(0.);
  hemptyPrompt->Draw();
  cFprompt->cd();
  hemptyPrompt->Draw();
  hfPromptMB->SetLineWidth(2);
  hfPromptMB->SetLineColor(1);
  hfPromptMB->SetMarkerStyle(23);
  hfPromptMB->SetMarkerSize(1);
  hfPromptMB->Draw("psame");
  hfPrompt->SetLineWidth(2);
  hfPrompt->SetLineColor(1);
  hfPrompt->SetMarkerStyle(23);
  hfPrompt->SetMarkerSize(1);
  hfPrompt->Draw("psame");
  
}


int main(int argc, char *argv[])
{
  if(argc==6)
    {
      CombineCrossSections(argv[1], argv[2], atoi(argv[3]), atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else if(argc==4)
    {
      CombineCrossSections(argv[1], argv[2], atoi(argv[3]));
      return 0;
    }
  else if(argc==3)
    {
      CombineCrossSections(argv[1], argv[2]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}

