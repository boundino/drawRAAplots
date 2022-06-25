#ifndef _DRAWTHEORY_V2_H_
#define _DRAWTHEORY_V2_H_

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

namespace drawTheoryV2
{
  // v2
  TCanvas* canvas;
  TH2F* hempty;

  TGraph* gv2Dmeson5TeV_PHSD;
  TGraph* gv2Dmeson5TeV_SUBATECH;
  TGraph* gv2Dmeson5TeV_LBT;
  TGraphAsymmErrors* gv2Dmeson5TeV_TAMU;
  TGraph* gv2Dmeson5TeV_TAMUSMC;
  TGraphErrors* gv2Dmeson5TeV_CUJET3;
  TGraph* gv2Dmeson5TeV_EPOS;
  TGraph* gv2Dmeson5TeV_BAMPS;
  TGraph* gv2Dmeson5TeV_BAMPSrad;
  TGraph* gv2Dmeson5TeV_POWLANG;

  TGraph* fillalicecurve(TString datfile);

  void setupTheory3050()
  {
    // PHSD
    TFile* inputPHSD = new TFile("TheoryPredictions/PHSD_v2v3_interpolation_from0p5.root");
    gv2Dmeson5TeV_PHSD = (TGraph*)inputPHSD->Get("gv2Dmeson5TeV_PHSD_cent30to50");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_PHSD, -1, -1, -1, kAzure-6, 1, 3);
    std::cout<<"--- Read... gv2Dmeson5TeV_PHSD"<<std::endl;
    // SUBATECH
    gv2Dmeson5TeV_SUBATECH = new TGraph("TheoryPredictions/5TeV30-50v2D_CMS.dat");
    gv2Dmeson5TeV_SUBATECH->SetName("gv2Dmeson5TeV_SUBATECH_cent30to50");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_SUBATECH, -1, -1, -1, kMagenta-2, 8, 3);
    std::cout<<"--- Read... gv2Dmeson5TeV_SUBATECH"<<std::endl;
    // LBT
    gv2Dmeson5TeV_LBT = new TGraph("TheoryPredictions/v2_cen-30-50.dat");
    gv2Dmeson5TeV_LBT->SetName("gv2Dmeson5TeV_LBT_cent30to50");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_LBT, -1, -1, -1, kRed+1, 1, 3);
    std::cout<<"--- Read... gv2Dmeson5TeV_LBT"<<std::endl;
    // TAMU
    TFile* inputTAMU = new TFile("TheoryPredictions/PredictionsTAMU_Dv2_pt.root");
    gv2Dmeson5TeV_TAMU = (TGraphAsymmErrors*)inputTAMU->Get("gv2Dmeson5TeV_TAMU_cent30to50");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_TAMU, -1, -1, -1, kGray, 1, 1, kGray, -1, 1001);
    std::cout<<"--- Read... gv2Dmeson5TeV_TAMU"<<std::endl;
    // TAMUSMC
    gv2Dmeson5TeV_TAMUSMC = new TGraph("TheoryPredictions/v2_TAMU-SMC_3050_sort.txt");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_TAMUSMC, -1, -1, -1, kOrange+1, 1, 1, kOrange+1, 0.6, 1001, 0.6);
    std::cout<<"--- Read... gv2Dmeson5TeV_TAMUSMC"<<std::endl;
    // CUJET3
    TFile* inputCUJET3 = new TFile("TheoryPredictions/CUJET_v2.root");
    gv2Dmeson5TeV_CUJET3 = (TGraphErrors*)inputCUJET3->Get("gv2Dmeson5TeV_CUJET_cent30to50");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_CUJET3, -1, -1, -1, 0, 0, 0, kGreen+3, 0.6, 3481);
    std::cout<<"--- Read... gv2Dmeson5TeV_CUJET3"<<std::endl;
    // BAMPS
    gv2Dmeson5TeV_BAMPS = fillalicecurve("TheoryPredictions/v2_BAMPS.dat");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_BAMPS, -1, -1, -1, kGreen+4, 3, 3);
    std::cout<<"--- Read... gv2Dmeson5TeV_BAMPS"<<std::endl;
    // BAMPSrad
    gv2Dmeson5TeV_BAMPSrad = fillalicecurve("TheoryPredictions/v2_BAMPSrad.dat");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_BAMPSrad, -1, -1, -1, kSpring+5, 3, 3);
    std::cout<<"--- Read... gv2Dmeson5TeV_BAMPSrad"<<std::endl;
    // POWLANG
    gv2Dmeson5TeV_POWLANG = fillalicecurve("TheoryPredictions/v2_POWLANG_new.dat");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_POWLANG, -1, -1, -1, kMagenta-7, 2, 3);
    std::cout<<"--- Read... gv2Dmeson5TeV_POWLANG"<<std::endl;
    // EPOS
    gv2Dmeson5TeV_EPOS = new TGraph("TheoryPredictions/v2_EPOS_new.dat");
    gv2Dmeson5TeV_EPOS->SetName("gv2Dmeson5TeV_EPOS_cent30to50");
    xjjroot::setthgrstyle(gv2Dmeson5TeV_EPOS, -1, -1, -1, kAzure+5, 1, 2, kAzure+5, -1, 3345);
    std::cout<<"--- Read... gv2Dmeson5TeV_EPOS"<<std::endl;
  }

  void drawTheory3050()
  {
    gStyle->SetHatchesLineWidth(2);

    // gv2Dmeson5TeV_TAMU->Draw("4 same");
    gv2Dmeson5TeV_TAMUSMC->Draw("f same");
    gv2Dmeson5TeV_CUJET3->Draw("4 same");
    gv2Dmeson5TeV_EPOS->Draw("f same");
    gv2Dmeson5TeV_EPOS->Draw("l same");
    gv2Dmeson5TeV_PHSD->Draw("c same");
    gv2Dmeson5TeV_SUBATECH->Draw("c same");
    gv2Dmeson5TeV_LBT->Draw("c same");
    // gv2Dmeson5TeV_BAMPS->Draw("l same");
    // gv2Dmeson5TeV_BAMPSrad->Draw("l same");
    gv2Dmeson5TeV_POWLANG->Draw("l same");    
  }

  void setupNdrawTheory3050() { setupTheory3050(); drawTheory3050(); }

  // Draw
  void drawcanvas()
  {
    canvas = new TCanvas("canvasV2promptD", "", 600, 600);
    canvas->cd();
 
    // float xaxismin = 0, xaxismax = 35;
    float xaxismin = 0.8, xaxismax = 80;

    gPad->SetLogx();
    hempty = new TH2F("hemptyV2promptD",";p_{T} (GeV/c);v_{2}", 50, xaxismin, xaxismax, 10, -0.04, 0.32);
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

    xjjroot::drawline(xaxismin, 0, xaxismax, 0, kBlack, 2, 2);    
    xjjroot::drawCMSleft("CMS", 0.04, -0.08, 0.036);
    xjjroot::drawCMSright("(5.02 TeV PbPb, Centrality 30-50%)", 0, 0, 0.036);
  }

  TLegend *legV2, *legV2p;
  void drawlegends()
  {
    legV2 = new TLegend(0.23, 0.847-0.041*2, 0.97, 0.847);
    legV2->SetNColumns(3);
    legV2->SetBorderSize(0);
    legV2->SetFillStyle(0);
    legV2->SetTextFont(42);
    legV2->SetTextSize(0.031);
    legV2p = new TLegend(0.23, 0.715-0.041*1, 0.93, 0.715);
    legV2p->SetNColumns(2);
    legV2p->SetBorderSize(0);
    legV2p->SetFillStyle(0);
    legV2p->SetTextFont(42);
    legV2p->SetTextSize(0.031);
    legV2->AddEntry(gv2Dmeson5TeV_LBT, "LBT", "l");
    legV2->AddEntry(gv2Dmeson5TeV_PHSD, "PHSD", "l");
    legV2->AddEntry(gv2Dmeson5TeV_SUBATECH, "SUBATECH", "l");
    legV2->AddEntry(gv2Dmeson5TeV_CUJET3, "CUJET 3.0", "f");
    // legV2->AddEntry(gv2Dmeson5TeV_TAMU, "TAMU", "f");
    legV2->AddEntry(gv2Dmeson5TeV_TAMUSMC, "TAMU", "f");
    // legV2p->AddEntry(gv2Dmeson5TeV_BAMPSrad, "BAMPS el.+rad.", "l");
    legV2p->AddEntry(gv2Dmeson5TeV_POWLANG, "POWLANG HLT", "l");
    // legV2p->AddEntry(gv2Dmeson5TeV_BAMPS, "BAMPS el.", "l");
    legV2p->AddEntry(gv2Dmeson5TeV_EPOS, "MC@sHQ+EPOS2", "f");
    legV2->Draw();
    legV2p->Draw();
    xjjroot::drawtex(0.60, 0.857, "#bf{D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}}, |y| < 1", 0.034, 21);
    xjjroot::drawtex(0.60, 0.725, "#bf{Average D#scale[0.6]{#lower[-0.7]{0}}, D#scale[0.6]{#lower[-1.0]{+}}, D#scale[0.6]{#lower[-0.1]{*}}#scale[0.6]{#lower[-0.9]{+}}}, |y| < 0.8", 0.034, 21);
  }

  TGraph* fillalicecurve(TString datfile)
  {
    std::ifstream getdata(datfile.Data());
    std::vector<float> vx, vy;
    while(true)
      {
        float x, y;
        getdata >> x;
        if(getdata.eof()) { break; }
        getdata >> y;
        vx.push_back(x);
        vy.push_back(y);
      }
    int nx = vx.size();
    TGraph* gr = new TGraph(nx, vx.data(), vy.data());
    gr->SetName(Form("gr_%s", datfile.Data()));
    return gr;
  }
}

#endif
