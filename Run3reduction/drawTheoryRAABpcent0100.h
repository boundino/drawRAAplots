#ifndef _DRAWTHEORY_RAABP100_H_
#define _DRAWTHEORY_RAABP100_H_

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

namespace drawTheoryRAABpcent0100
{
  // RAA
  TCanvas* canvas;
  TH2F* hempty;

  TGraph* gCUJET;

  void setupTheory()
  {

  }

  //
  void drawTheory()
  {
    gStyle->SetHatchesLineWidth(2);

  }

  //
  void setupNdrawTheory() { setupTheory(); drawTheory(); }

  // Draw
  void drawcanvas()
  {
    canvas = new TCanvas("canvasRAABp", "", 600, 600);
    canvas->cd();
    canvas->SetLogx();

    float xaxismin = 4, xaxismax = 70;

    hempty = new TH2F("hemptyRAABp",";p_{T} (GeV/c);R_{AA}", 50, xaxismin, xaxismax, 10, 0, 1.8);
    xjjroot::sethempty(hempty, -0.04, 0.25);
    hempty->GetXaxis()->SetLabelOffset(-0.008);
    hempty->Draw();

    xjjroot::drawline(xaxismin, 1, xaxismax, 1, kBlack, 2, 2);
    xjjroot::drawCMSleft("Projection", 0.05, -0.1, 0.036);
    xjjroot::drawCMSright("(5.02 TeV PbPb, Centrality 0-90%)", 0, 0, 0.036);
  }

  TLegend* legg;
  void drawlegends()
  {
    legg = new TLegend(0.59, 0.83-0.041*4, 0.93, 0.83);
    xjjroot::setleg(legg, 0.031);
    legg->Draw();
  }

}

#endif
