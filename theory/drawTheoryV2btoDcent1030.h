#ifndef _DRAWTHEORY_V2BTODCENT1030_H_
#define _DRAWTHEORY_V2BTODCENT1030_H_

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

  TGraph* grPHSD;
  TGraph* grLBT;
  TGraph* grTAMU;
  TGraph* grCUJET3;
  TGraph* grLGR;

  void setupTheory()
  {
    // PHSD
    grPHSD = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_PHSD_10-30.txt");
    xjjroot::setthgrstyle(grPHSD, -1, -1, -1, kAzure-6, 1, 3);
    std::cout<<"--- Read... grPHSD"<<std::endl;
    // LBT
    grLBT = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_LBT_10-30.dat");
    xjjroot::setthgrstyle(grLBT, -1, -1, -1, kRed+1, 1, 3);
    std::cout<<"--- Read... grLBT"<<std::endl;
    // TAMU
    grTAMU = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_TAMU_20-40_sort.txt");
    xjjroot::setthgrstyle(grTAMU, -1, -1, -1, kOrange+1, 1, 1, kOrange+1, 0.6, 1001, 0.6);
    std::cout<<"--- Read... grTAMU"<<std::endl;
    // CUJET3
    grCUJET3 = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_CUJET3_10-30_sort.dat");
    xjjroot::setthgrstyle(grCUJET3, -1, -1, -1, 0, 0, 0, kGreen+3, 0.6, 3481);
    std::cout<<"--- Read... grCUJET3"<<std::endl;
    // LGR
    grLGR = new TGraph("TheoryPredictions/v2_btoD_1030/v2_btoD_LGR_30-50_sort.txt");
    xjjroot::setthgrstyle(grLGR, -1, -1, -1, kMagenta-6, 2, 2, kMagenta-6, -1, 3354);
    std::cout<<"--- Read... grLGR"<<std::endl;
  }

  void drawTheory()
  {
    gStyle->SetHatchesLineWidth(2);

    grTAMU->Draw("f same");
    grLGR->Draw("f same");
    grLGR->Draw("l same");
    grCUJET3->Draw("f same");
    grPHSD->Draw("l same");
    grLBT->Draw("l same");
  }

  void setupNdrawTheory() { setupTheory(); drawTheory(); }

  // Draw
  void drawcanvas()
  {
    canvas = new TCanvas("canvasV2btoD", "", 600, 600);
    canvas->cd();

    float xaxismin = 0, xaxismax = 30;

    gPad->SetLogx(0);
    hempty = new TH2F("hemptyV2btoD",";p_{T} (GeV/c);v_{2}", 50, xaxismin, xaxismax, 10, -0.05, 0.13);
    xjjroot::sethempty(hempty, -0.04);
    // hempty->GetXaxis()->SetLabelOffset(-0.008);
    hempty->Draw();

    xjjroot::drawline(xaxismin, 0, xaxismax, 0, kBlack, 2, 2);    
    xjjroot::drawCMSleft("Preliminary", 0.05, -0.1, 0.036);
    xjjroot::drawCMSright("(5.02 TeV PbPb, Centrality 10-30%)", 0, 0, 0.036);
  }

  TLegend *legg;
  void drawlegends()
  {
    legg = new TLegend(0.59, 0.83-0.041*5, 0.93, 0.83);
    xjjroot::setleg(legg, 0.031);
    legg->AddEntry(grPHSD, "PHSD", "l");
    legg->AddEntry(grCUJET3, "CUJET 3.0", "f");
    legg->AddEntry(grTAMU, "TAMU (20-40%)", "f");
    legg->AddEntry(grLGR, "LGR (30-50%)", "f");
    legg->AddEntry(grLBT, "LBT", "l");
    legg->Draw();
    xjjroot::drawtex(0.60, 0.845, "#bf{(b#rightarrow) D#scale[0.6]{#lower[-0.7]{0}}}, |y| < 1", 0.034, 11);
  }
}

#endif
