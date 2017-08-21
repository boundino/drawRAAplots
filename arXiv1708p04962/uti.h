#ifndef _UTI_H_
#define _UTI_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <TFile.h>
#include <TDirectoryFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLatex.h>
#include <TLegend.h>
#include "TLegendEntry.h"
#include <TLine.h>
#include <TBox.h>
#include <TCut.h>
#include <TMath.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TProfile.h>
#include <TFitResult.h>
#include <TFitter.h>
#include "TGaxis.h"
#include <TColor.h>


// Remove error
void removeError(TH1F* h)
{
  for(int i=1;i<=h->GetNbinsX();i++)
    {
      h->SetBinError(i,0);
    }	
}

// divide by bin width
void divideBinWidth(TH1* h)
{
  //h->Sumw2();
  for(int i=1;i<=h->GetNbinsX();i++)
    {
      Float_t val = h->GetBinContent(i);
      Float_t valErr = h->GetBinError(i);
      val/=h->GetBinWidth(i);
      valErr/=h->GetBinWidth(i);
      h->SetBinContent(i,val);
      h->SetBinError(i,valErr);
    }
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
}

// make a histogram from TF1 function
TH1F* functionHist(TF1* f, TH1F* h, TString fHistname)
{
  TH1F* hF = (TH1F*)h->Clone(fHistname);
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      Double_t var = f->Integral(h->GetBinLowEdge(i),h->GetBinLowEdge(i+1))/h->GetBinWidth(i);
      hF->SetBinContent(i,var);
      hF->SetBinError(i,0);
    }
  return hF;
}

TLegend* myLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2)
{
  TLegend* leg = new TLegend(x1,y1,x2,y2);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  return leg; 
}


void sethempty(TH2F* hempty)
{
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetTitleOffset(1.10);
  hempty->GetYaxis()->SetTitleOffset(1.30);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.045);
  hempty->GetYaxis()->SetLabelSize(0.045);
  hempty->SetStats(0);
}


template <class T>
void sethemptystyle(T* hempty, Float_t xtitleoffset=-1, Float_t ytitleoffset=-1, Float_t xtitlesize=-1, Float_t ytitlesize=-1, Float_t xlabelsize=-1, Float_t ylabelsize=-1)
{
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  if(xtitleoffset>=0) hempty->GetXaxis()->SetTitleOffset(xtitleoffset);
  if(ytitleoffset>=0) hempty->GetYaxis()->SetTitleOffset(ytitleoffset);
  if(xtitlesize>=0) hempty->GetXaxis()->SetTitleSize(xtitlesize);
  if(ytitlesize>=0) hempty->GetYaxis()->SetTitleSize(ytitlesize);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  if(xlabelsize>=0) hempty->GetXaxis()->SetLabelSize(xlabelsize);
  if(ylabelsize>=0) hempty->GetYaxis()->SetLabelSize(ylabelsize);
  hempty->SetStats(0);
}

template <class T>
void setthgrstyle(T* h, Color_t mcolor=-1, Style_t mstyle=-1, Size_t msize=-1, Color_t lcolor=-1, Style_t lstyle=-1, Width_t lwidth=-1, Color_t fcolor=-1, Float_t falpha=-1, Style_t fstyle=-1)
{
  if(mcolor>=0) h->SetMarkerColor(mcolor);
  if(mstyle>=0) h->SetMarkerStyle(mstyle);
  if(msize>=0) h->SetMarkerSize(msize);
  if(lcolor>=0) h->SetLineColor(lcolor);
  if(lstyle>=0) h->SetLineStyle(lstyle);
  if(lwidth>=0) h->SetLineWidth(lwidth);
  if(fcolor>=0) h->SetFillColor(fcolor);
  if(falpha>=0) h->SetFillColorAlpha(fcolor, falpha);
  if(fstyle>=0) h->SetFillStyle(fstyle);
}

template <class T>
void setthgr(T* h)
{
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetYaxis()->SetTitleOffset(0.95);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.035);
  h->GetYaxis()->SetLabelSize(0.035);
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.0);
}

void drawCMS(TString collision)
{
  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collision.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();
}

void settex(TLatex* tex, Float_t tsize=0.04, Short_t align=11, Font_t tfont=42)
{
  tex->SetNDC();
  tex->SetTextFont(tfont);
  tex->SetTextAlign(align);
  tex->SetTextSize(tsize);
}

void setleg(TLegend* leg, Float_t size=0.04)
{
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(size);
}

void setgstyle()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
}



/*
void settgraphasymmerrors(TGraphAsymmErrors* gr)
{
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->CenterTitle();
  gr->GetXaxis()->SetTitleOffset(0.9);
  gr->GetYaxis()->SetTitleOffset(0.95);
  gr->GetXaxis()->SetTitleSize(0.05);
  gr->GetYaxis()->SetTitleSize(0.05);
  gr->GetXaxis()->SetTitleFont(42);
  gr->GetYaxis()->SetTitleFont(42);
  gr->GetXaxis()->SetLabelFont(42);
  gr->GetYaxis()->SetLabelFont(42);
  gr->GetXaxis()->SetLabelSize(0.035);
  gr->GetYaxis()->SetLabelSize(0.035);
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(1.0);
}

void setth1f(TH1F* hempty)
{
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(0.9);
  hempty->GetYaxis()->SetTitleOffset(0.95);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);
  hempty->SetStats(0);
}

void setth1d(TH1D* hempty)
{
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(0.9);
  hempty->GetYaxis()->SetTitleOffset(0.95);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);
  hempty->SetStats(0);
}
*/

#endif
