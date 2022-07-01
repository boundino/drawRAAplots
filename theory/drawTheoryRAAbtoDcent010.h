#ifndef _DRAWTHEORY_RAABTOD010_H_
#define _DRAWTHEORY_RAABTOD010_H_

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

namespace drawTheoryRAAbtoDcent010
{
  // RAA
  TCanvas* canvas;
  TH2F* hempty;

  TGraph* gCUJET;
  TGraph* gEPOS;
  TGraph* gTAMU;
  TGraph* gLGR;

  void setupTheory()
  {
    // CUJET
    gCUJET = new TGraph("TheoryPredictions/RAA_btoD_010/RAA_btoD_CUJET_010.dat");
    xjjroot::setthgrstyle(gCUJET, -1, -1, -1, 0, 0, 0, kGreen+3, 0.6, 3481);
    std::cout<<"--- Read... gCUJET"<<std::endl;
    // LGR
    gLGR = new TGraph("TheoryPredictions/RAA_btoD_010/RAA_btoD_LGR_010.dat");
    xjjroot::setthgrstyle(gLGR, -1, -1, -1, kMagenta-6, 2, 2, kMagenta-6, -1, 3354);
    std::cout<<"--- Read... gLGR"<<std::endl;
    // EPOS
    gEPOS = new TGraph("TheoryPredictions/RAA_btoD_010/RAA_btoD_EPOS_010.dat");
    xjjroot::setthgrstyle(gEPOS, -1, -1, -1, kAzure+5, 1, 2, kAzure+5, -1, 3345);
    std::cout<<"--- Read... gEPOS"<<std::endl;
    // TAMU
    gTAMU = new TGraph("TheoryPredictions/RAA_btoD_010/RAA_btoD_TAMU_010.dat");
    xjjroot::setthgrstyle(gTAMU, -1, -1, -1, kOrange+1, 1, 3);
    std::cout<<"--- Read... gTAMU"<<std::endl;
  }

  //
  void drawTheory()
  {
    gStyle->SetHatchesLineWidth(2);

    gLGR->Draw("f same");
    gLGR->Draw("l same");
    gCUJET->Draw("f same");
    gEPOS->Draw("f same");
    gEPOS->Draw("l same");
    gTAMU->Draw("c same");
  }

  //
  void setupNdrawTheory() { setupTheory(); drawTheory(); }

  // Draw
  void drawcanvas()
  {
    canvas = new TCanvas("canvasRAAbtoDcent010", "", 600, 600);
    canvas->cd();
    canvas->SetLogx();

    float xaxismin = 0.6, xaxismax = 50;

    hempty = new TH2F("hemptyRAAbtoDcent010",";p_{T} (GeV/c);R_{AA}", 50, xaxismin, xaxismax, 10, 0, 1.7);
    xjjroot::sethempty(hempty, -0.04);
    hempty->GetXaxis()->SetLabelOffset(-0.008);
    hempty->Draw();

    xjjroot::drawline(xaxismin, 1, xaxismax, 1, kBlack, 2, 2);
    xjjroot::drawCMSleft("CMS", 0.05, -0.1, 0.036);
    xjjroot::drawCMSright("(5.02 TeV PbPb, Centrality 0-10%)", 0, 0, 0.036);
  }

  TLegend* legg;
  void drawlegends()
  {
    legg = new TLegend(0.59, 0.83-0.041*4, 0.93, 0.83);
    xjjroot::setleg(legg, 0.031);
    legg->AddEntry(gCUJET, "CUJET 3.0", "f");
    legg->AddEntry(gTAMU, "TAMU", "l");
    legg->AddEntry(gLGR, "LGR", "f");
    legg->AddEntry(gEPOS, "MC@sHQ+EPOS2", "f");
    legg->Draw();
    xjjroot::drawtex(0.60, 0.845, "#bf{(b#rightarrow) D#scale[0.6]{#lower[-0.7]{0}}}, |y| < 1", 0.034, 11);
  }

}

#endif
