#ifndef _DRAWTHEORY_RAAPROMPTD010_H_
#define _DRAWTHEORY_RAAPROMPTD010_H_

#include <iostream>
#include <fstream>
#include <vector>

#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TH2F.h>
#include <TLatex.h>
#include <TLine.h>
#include "xjjrootuti.h"

namespace drawTheoryRAApromptDcent010
{
  // RAA
  TCanvas* canvas;
  TH2F* hempty;

  TGraphAsymmErrors* gCUJETD5TeV;
  TGraph* gShanshanD5TeV;
  TGraphErrors* gMagdalenaD5TeV;
  TGraphErrors* gPHSDWOShadowing;
  TGraphErrors* gPHSDWShadowing;
  TGraph* gIvanD5TeV;
  TGraphErrors* gADSCFT1D5TeV;
  TGraphErrors* gADSCFT2D5TeV;
  TGraph* gBAMPSlow;
  TGraph* gBAMPShigh;
  TGraph* gBAMPSradlow;
  TGraph* gBAMPSradhigh;
  TGraph* gEPOSnew;
  TGraph* gPOWLANG;
  TGraph* gTAMUnew;

  TGraphErrors* fillgadscft(TString datfile);
      
  void setupTheory()
  {
    // CUJET
    TFile* infCUJETD5TeV = new TFile("TheoryPredictions/RAA_promptD_010/CUJET_D0_RAA_0_10.root");
    gCUJETD5TeV = (TGraphAsymmErrors*)infCUJETD5TeV->Get("gRAADmeson5TeV");
    xjjroot::setthgrstyle(gCUJETD5TeV, -1, -1, -1, 0, 0, 0, kGreen+3, 0.6, 3481);
    std::cout<<"--- Read... gCUJETD5TeV"<<std::endl;
    // Shanshan
    gShanshanD5TeV = new TGraph("TheoryPredictions/RAA_promptD_010/Shanshan-D-RAA_PbPb5020_00-10.dat");
    xjjroot::setthgrstyle(gShanshanD5TeV, -1, -1, -1, kGreen+4, 1, 3);
    std::cout<<"--- Read... gShanshanD5TeV"<<std::endl;
    // Magdalena
    gMagdalenaD5TeV = new TGraphErrors("TheoryPredictions/RAA_promptD_010/Magdalena-5TeV-plot2.txt");
    xjjroot::setthgrstyle(gMagdalenaD5TeV, -1, -1, -1, kRed-7, 1, 2, kRed-4, 0.8, 3344);
    std::cout<<"--- Read... gMagdalenaD5TeV"<<std::endl;
    // PHSD w/o shadowing
    gPHSDWOShadowing = new TGraphErrors("TheoryPredictions/RAA_promptD_010/phsd502TeVWoShadowing.txt");
    xjjroot::setthgrstyle(gPHSDWOShadowing, -1, -1, -1, kAzure-6, 2, 3);
    std::cout<<"--- Read... gPHSDWOShadowing"<<std::endl;
    // PHSD w/ shadowing
    gPHSDWShadowing = new TGraphErrors("TheoryPredictions/RAA_promptD_010/phsd502TeVWShadowing.txt");
    xjjroot::setthgrstyle(gPHSDWShadowing, -1, -1, -1, kAzure-6, 1, 3, kAzure-6, 1, 1001);
    std::cout<<"--- Read... gPHSDWShadowing"<<std::endl;
    // Ivan 
    gIvanD5TeV = new TGraph("TheoryPredictions/RAA_promptD_010/D0cmsCENTPbPb.txt");
    xjjroot::setthgrstyle(gIvanD5TeV, -1, -1, -1, kViolet+1, 1, 2, kViolet+1, 0.8, 3358);
    std::cout<<"--- Read... gIvanD5TeV"<<std::endl;
    // ADSCFT 1
    gADSCFT1D5TeV = fillgadscft("TheoryPredictions/RAA_promptD_010/RAA_5TeV_0010_D0_DiffusionConstant_band.dat");
    gADSCFT1D5TeV->SetName("gADSCFT1D5TeV");
    xjjroot::setthgrstyle(gADSCFT1D5TeV, -1, -1, -1, 0, 0 ,0, kOrange+1, 0.6, 3325);
    std::cout<<"--- Read... gADSCFT1D5TeV"<<std::endl;
    // ADSCFT 2
    gADSCFT2D5TeV = fillgadscft("TheoryPredictions/RAA_promptD_010/RAA_5TeV_0010_D0_DiffusionDynamic_band.dat");
    gADSCFT2D5TeV->SetName("gADSCFT2D5TeV");
    xjjroot::setthgrstyle(gADSCFT2D5TeV, -1, -1, -1, 0, 0, 0, kPink-9, 0.6, 3352);
    std::cout<<"--- Read... gADSCFT2D5TeV"<<std::endl;
    // BAMPS
    gBAMPSlow = new TGraph("TheoryPredictions/RAA_promptD_010/RAA_BAMPS_low.dat");
    xjjroot::setthgrstyle(gBAMPSlow, -1, -1, -1, kGreen+4, 3, 3);
    gBAMPShigh = new TGraph("TheoryPredictions/RAA_promptD_010/RAA_BAMPS_high.dat");
    xjjroot::setthgrstyle(gBAMPShigh, -1, -1, -1, kGreen+4, 3, 3);
    std::cout<<"--- Read... gBAMPS"<<std::endl;
    // BAMPSrad
    gBAMPSradlow = new TGraph("TheoryPredictions/RAA_promptD_010/RAA_BAMPSrad_low.dat");
    xjjroot::setthgrstyle(gBAMPSradlow, -1, -1, -1, kSpring+5, 3, 4);
    gBAMPSradhigh = new TGraph("TheoryPredictions/RAA_promptD_010/RAA_BAMPSrad_high.dat");
    xjjroot::setthgrstyle(gBAMPSradhigh, -1, -1, -1, kSpring+5, 3, 4);
    std::cout<<"--- Read... gBAMPSrad"<<std::endl;
    // EPOS
    gEPOSnew = new TGraph("TheoryPredictions/RAA_promptD_010/RAA_EPOS_new.dat");
    xjjroot::setthgrstyle(gEPOSnew, -1, -1, -1, kAzure+5, 1, 2, kAzure+5, -1, 3345);
    std::cout<<"--- Read... gEPOS"<<std::endl;
    // TAMU
    gTAMUnew = new TGraph("TheoryPredictions/RAA_promptD_010/RAA_TAMU_new.dat");
    xjjroot::setthgrstyle(gTAMUnew, -1, -1, -1, kOrange+1, 1, 1, kOrange+1, 0.6, 1001, 0.6);
    std::cout<<"--- Read... gTAMU"<<std::endl;
    // POWLANG
    gPOWLANG = new TGraph("TheoryPredictions/RAA_promptD_010/RAA_POWLANG_new.dat");
    xjjroot::setthgrstyle(gPOWLANG, -1, -1, -1, kMagenta-7, 2, 3);
    std::cout<<"--- Read... gPOWLANG"<<std::endl;
  }

  //
  void drawTheory()
  {
    gStyle->SetHatchesLineWidth(2);

    gTAMUnew->Draw("f same");
    gEPOSnew->Draw("f same");
    gEPOSnew->Draw("l same");

    // gMagdalenaD5TeV->Draw("f same");
    // gMagdalenaD5TeV->Draw("l same");
    // gIvanD5TeV->Draw("f same");
    // gIvanD5TeV->Draw("l same");
    gADSCFT1D5TeV->Draw("4 same");
    // gPHSDWShadowing->Draw("c4 same");
    gShanshanD5TeV->Draw("c same");
    // gADSCFT2D5TeV->Draw("4 same");
    // gCUJETD5TeV->Draw("3 same");
    
    gPOWLANG->Draw("l same");
  }

  //
  void setupNdrawTheory() { setupTheory(); drawTheory(); }

  //
  TGraphErrors* fillgadscft(TString datfile)
  {
    std::vector<float> bCx, bCy, bCxe, bCye;
    std::ifstream getadscft(datfile);
    while(true)
      {
        float bx, by, bye, dum, temp;
        getadscft>>temp;
        if(getadscft.eof()) { break; }
        bx = temp; getadscft>>by>>dum>>bye; 
        bCx.push_back(bx);
        bCy.push_back(by);
        bCxe.push_back(0);
        bCye.push_back(bye);
      }
    bCx.push_back(bCx[bCx.size()-1]);
    bCy.push_back(bCy[bCy.size()-1]);
    bCxe.push_back(0);
    bCye.push_back(bCye[bCye.size()-1]);

    getadscft.close();
    getadscft.clear();

    TGraphErrors* gadscft = new TGraphErrors(bCx.size(), bCx.data(), bCy.data(), bCxe.data(), bCye.data());
    gadscft->SetName(Form("gr_%s", datfile.Data()));
    return gadscft;
  }

  // Draw
  void drawcanvas()
  {
    canvas = new TCanvas("canvasRAApromptD", "", 600, 600);
    canvas->cd();
    canvas->SetLogx();

    float xaxismin = 0.8, xaxismax = 250;

    hempty = new TH2F("hemptyRAApromptD",";p_{T} (GeV/c);R_{AA}", 50, xaxismin, xaxismax, 10, 0, 1.6);
    xjjroot::sethempty(hempty, -0.04, 0.25);
    hempty->GetXaxis()->SetLabelOffset(-0.008);
    hempty->Draw();

    xjjroot::drawline(xaxismin, 1, xaxismax, 1, kBlack, 2, 2);
    xjjroot::drawCMSleft("Projection", 0.04, -0.08, 0.036);
    xjjroot::drawCMSright("(5.02 TeV PbPb, Centrality 0-10%)", 0, 0, 0.036);
  }

  TLegend* legg;
  void drawlegends()
  {
    gADSCFT1D5TeV->SetLineColor(0);
    gADSCFT2D5TeV->SetLineColor(0);
    legg = new TLegend(0.23, 0.847-0.041*4, 0.93, 0.847);
    xjjroot::setleg(legg, 0.031);
    legg->SetNColumns(2);
    legg->AddEntry(gShanshanD5TeV, "LBT", "l");
    // legg->AddEntry(gPHSDWShadowing, "PHSD", "l");
    // legg->AddEntry(gCUJETD5TeV, "CUJET 3.0", "f");
    // legg->AddEntry(gMagdalenaD5TeV, "Djordjevic et al.", "bf");
     legg->AddEntry(gADSCFT1D5TeV, "AdS/CFT D = const", "f");
    // legg->AddEntry(gIvanD5TeV, "Vitev et al. (g=1.9-2.0)", "bf");
    // legg->AddEntry(gADSCFT2D5TeV, "AdS/CFT D(p)", "f");
    legg->AddEntry((TObject*)0, "", NULL);
    legg->AddEntry((TObject*)0, "", NULL);
    // legg->AddEntry((TObject*)0, "", NULL);
    legg->AddEntry(gPOWLANG, "POWLANG HLT", "l");
    legg->AddEntry(gEPOSnew, "MC@sHQ+EPOS2", "f");
    legg->AddEntry(gTAMUnew, "TAMU", "f");
    legg->AddEntry((TObject*)0, "", NULL);
    legg->Draw();
    xjjroot::drawtex(0.60, 0.857, "#bf{D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}}, |y| < 1", 0.034, 21);
    // xjjroot::drawtex(0.60, 0.652, "#bf{Average D#scale[0.6]{#lower[-0.7]{0}}, D#scale[0.6]{#lower[-1.0]{+}}, D#scale[0.6]{#lower[-0.1]{*}}#scale[0.6]{#lower[-0.9]{+}}}, |y| < 0.5", 0.034, 21);
    xjjroot::drawtex(0.60, 0.652+0.041*3, "#bf{Average D#scale[0.6]{#lower[-0.7]{0}}, D#scale[0.6]{#lower[-1.0]{+}}, D#scale[0.6]{#lower[-0.1]{*}}#scale[0.6]{#lower[-0.9]{+}}}, |y| < 0.5", 0.034, 21);
  }

}

#endif
