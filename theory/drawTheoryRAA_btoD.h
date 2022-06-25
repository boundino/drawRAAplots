#ifndef _DRAWTHEORY_RAABTOD_H_
#define _DRAWTHEORY_RAABTOD_H_

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

namespace drawTheoryRAAbtoD
{
  // RAA
  TCanvas* canvas;
  TH2F* hempty;

  TGraph* gCUJET;
  TGraph* gPHSD;
  TGraph* gEPOS;
  TGraph* gTAMU;

  TGraphErrors* fillgadscft(TString datfile);
  TGraph* fillalicecurve(TString datfile);
      
  void setupTheory0100()
  {
    // CUJET
    gCUJET = new TGraph("TheoryPredictions/RAA_btoD_CUJET_sort.dat");
    xjjroot::setthgrstyle(gCUJET, -1, -1, -1, 0, 0, 0, kGreen+3, 0.6, 3481);
    std::cout<<"--- Read... gCUJET"<<std::endl;
    // PHSD w/ shadowing
    gPHSD = new TGraph("TheoryPredictions/RAA_btoD_PHSD.txt");
    xjjroot::setthgrstyle(gPHSD, -1, -1, -1, kAzure-6, 1, 3);
    std::cout<<"--- Read... gPHSD"<<std::endl;
    // EPOS
    gEPOS = new TGraph("TheoryPredictions/RAA_btoD_EPOS_sort.txt");
    xjjroot::setthgrstyle(gEPOS, -1, -1, -1, kAzure+5, 1, 2, kAzure+5, -1, 3345);
    std::cout<<"--- Read... gEPOS"<<std::endl;
    // TAMU
    gTAMU = new TGraph("TheoryPredictions/RAA_btoD_TAMU.txt");
    xjjroot::setthgrstyle(gTAMU, -1, -1, -1, kOrange+1, 1, 3);
    std::cout<<"--- Read... gTAMU"<<std::endl;
  }

  //
  void drawTheory0100()
  {
    gStyle->SetHatchesLineWidth(2);

    gCUJET->Draw("f same");
    gEPOS->Draw("f same");
    gEPOS->Draw("l same");
    gPHSD->Draw("c same");
    gTAMU->Draw("c same");
  }

  //
  void setupNdrawTheory0100() { setupTheory0100(); drawTheory0100(); }

  // Draw
  void drawcanvas()
  {
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(0);
    gStyle->SetMarkerStyle(20);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPadLeftMargin(0.17);
    gStyle->SetPadRightMargin(0.025);
    gStyle->SetPadTopMargin(0.080);
    gStyle->SetPadBottomMargin(0.11);

    canvas = new TCanvas("canvasRAAbtoD", "", 600, 600);
    canvas->cd();
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetLogx();

    float xaxismin = 1, xaxismax = 150;
    // float xaxismin = 0.5, xaxismax = 150;

    hempty = new TH2F("hemptyRAAbtoD",";p_{T} (GeV/c);R_{AA}", 50, xaxismin, xaxismax, 10, 0, 2.);
    hempty->GetXaxis()->SetLabelOffset(0.0);
    hempty->GetXaxis()->CenterTitle();
    hempty->GetYaxis()->CenterTitle();
    hempty->GetXaxis()->SetTitleFont(42);
    hempty->GetYaxis()->SetTitleFont(42);
    hempty->GetXaxis()->SetTitleOffset(1.10);
    hempty->GetYaxis()->SetTitleOffset(1.50);
    hempty->GetXaxis()->SetTitleSize(0.045);
    hempty->GetYaxis()->SetTitleSize(0.045);
    hempty->GetXaxis()->SetLabelSize(0.04);
    hempty->GetYaxis()->SetLabelSize(0.04);
    hempty->GetXaxis()->SetLabelFont(42);
    hempty->GetYaxis()->SetLabelFont(42);
    hempty->SetStats(0);    
    hempty->Draw();

    xjjroot::drawline(xaxismin, 1, xaxismax, 1, kBlack, 2, 2);
    xjjroot::drawCMSleft("CMS", 0.04, -0.08, 0.036);
    xjjroot::drawCMSright("(5.02 TeV PbPb, Centrality 0-100%)", 0, 0, 0.036);
  }

  TLegend* legRAA;
  void drawlegends()
  {
    legRAA = new TLegend(0.59, 0.83-0.041*4, 0.93, 0.83);
    legRAA->SetBorderSize(0);
    legRAA->SetFillStyle(0);
    legRAA->SetTextFont(42);
    legRAA->SetTextSize(0.031);
    legRAA->AddEntry(gPHSD, "PHSD", "l");
    legRAA->AddEntry(gCUJET, "CUJET 3.0", "f");
    legRAA->AddEntry(gTAMU, "TAMU", "l");
    legRAA->AddEntry(gEPOS, "MC@sHQ+EPOS2", "f");
    legRAA->Draw();
    xjjroot::drawtex(0.60, 0.845, "#bf{(b #rightarrow) D#scale[0.6]{#lower[-0.7]{0}}}, |y| < 1", 0.034, 11);
  }

}

#endif
