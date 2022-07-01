#ifndef _DRAWTHEORY_V2BTOD_H_
#define _DRAWTHEORY_V2BTOD_H_

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

namespace drawTheoryV2btoDcent1030
{
  // v2
  TCanvas* canvas;
  TH2F* hempty;

  TGraph* gv2Dmeson5TeV_PHSD;
  TGraph* gv2Dmeson5TeV_LBT;
  TGraph* gv2Dmeson5TeV_TAMU;
  TGraph* gv2Dmeson5TeV_CUJET3;

  void setupTheory()
  {
    // PHSD
    gv2Dmeson5TeV_PHSD = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_PHSD_10-30.txt");
    gv2Dmeson5TeV_PHSD->SetName("gv2Dmeson5TeV_PHSD");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_PHSD, -1, -1, -1, kAzure-6, 1, 3);
    std::cout<<"--- Read... gv2Dmeson5TeV_PHSD"<<std::endl;
    // LBT
    gv2Dmeson5TeV_LBT = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_LBT_10-30.dat");
    gv2Dmeson5TeV_LBT->SetName("gv2Dmeson5TeV_LBT_cent10to30");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_LBT, -1, -1, -1, kRed+1, 1, 3);
    std::cout<<"--- Read... gv2Dmeson5TeV_LBT"<<std::endl;
    // TAMU
    gv2Dmeson5TeV_TAMU = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_TAMU_20-40_sort.txt");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_TAMU, -1, -1, -1, kOrange+1, 1, 1, kOrange+1, 0.6, 1001, 0.6);
    std::cout<<"--- Read... gv2Dmeson5TeV_TAMU"<<std::endl;
    // CUJET3
    gv2Dmeson5TeV_CUJET3 = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_CUJET3_10-30_sort.dat");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_CUJET3, -1, -1, -1, 0, 0, 0, kGreen+3, 0.6, 3481);
    std::cout<<"--- Read... gv2Dmeson5TeV_CUJET3"<<std::endl;
  }

  void drawTheory()
  {
    gStyle->SetHatchesLineWidth(2);

    gv2Dmeson5TeV_TAMU->Draw("f same");
    gv2Dmeson5TeV_CUJET3->Draw("f same");
    gv2Dmeson5TeV_PHSD->Draw("l same");
    gv2Dmeson5TeV_LBT->Draw("l same");
  }

  void setupNdrawTheory() { setupTheory(); drawTheory(); }

  // Draw
  void drawcanvas()
  {
    canvas = new TCanvas("canvasV2btoD", "", 600, 600);
    canvas->cd();

    float xaxismin = 0, xaxismax = 30;
    // float xaxismin = 0.8, xaxismax = 80;

    gPad->SetLogx(0);
    hempty = new TH2F("hemptyV2btoD",";p_{T} (GeV/c);v_{2}", 50, xaxismin, xaxismax, 10, -0.05, 0.11);
    xjjroot::sethempty(hempty, -0.04);
    hempty->GetXaxis()->SetLabelOffset(-0.008);
    hempty->Draw();

    xjjroot::drawline(xaxismin, 0, xaxismax, 0, kBlack, 2, 2);    
    xjjroot::drawCMSleft("Preliminary", 0.05, -0.1, 0.036);
    xjjroot::drawCMSright("(5.02 TeV PbPb, Centrality 10-30%)", 0, 0, 0.036);
  }

  TLegend *legg;
  void drawlegends()
  {
    legg = new TLegend(0.59, 0.83-0.041*4, 0.93, 0.83);
    xjjroot::setleg(legg, 0.031);
    legg->AddEntry(gv2Dmeson5TeV_PHSD, "PHSD", "l");
    legg->AddEntry(gv2Dmeson5TeV_CUJET3, "CUJET 3.0", "f");
    legg->AddEntry(gv2Dmeson5TeV_TAMU, "TAMU (20-40%)", "f");
    legg->AddEntry(gv2Dmeson5TeV_LBT, "LBT", "l");
    legg->Draw();
    xjjroot::drawtex(0.60, 0.845, "#bf{(b#rightarrow) D#scale[0.6]{#lower[-0.7]{0}}}, |y| < 1", 0.034, 11);
  }
}

#endif
