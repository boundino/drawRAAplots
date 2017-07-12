#include "uti.h"

// RAA
TGraphAsymmErrors* gCUJETD5TeV;
TGraph* gShanshanD5TeV;
TGraphErrors* gMagdalenaD5TeV;
TGraphErrors* gPHSDWOShadowing;
TGraphErrors* gPHSDWShadowing;
TGraph* gIvanD5TeV;
TGraphErrors* gADSCFT1D5TeV;
TGraphErrors* gADSCFT2D5TeV;
// pp
TGraphAsymmErrors* gGMVFNSD5TeV;
TGraphAsymmErrors* gGMVFNSD5TeVunity;

TGraphErrors* fillgadscft(TString datfile);
Int_t findbin(Float_t bincenter, Float_t* ptmin, Float_t* ptmax, Int_t nbin);

//
void drawTheory0100()
{
  gStyle->SetHatchesLineWidth(3);

  // CUJET
  TFile* infCUJETD5TeV = new TFile("TheoryPredictions/CUJET_D0_RAA_0_100.root");
  gCUJETD5TeV = (TGraphAsymmErrors*)infCUJETD5TeV->Get("gRAADmeson5TeV");
  gCUJETD5TeV->SetLineWidth(1);
  gCUJETD5TeV->SetLineColor(0);//4
  gCUJETD5TeV->SetFillColor(kAzure-1);//4
  gCUJETD5TeV->SetFillColorAlpha(kAzure-2,0.6);
  gCUJETD5TeV->SetFillStyle(3481);//3001
  // Shanshan
  gShanshanD5TeV = new TGraph("TheoryPredictions/Shanshan-D-RAA_PbPb5020_00-80.dat");
  gShanshanD5TeV->SetLineWidth(3);
  gShanshanD5TeV->SetLineColor(kRed+1);
  // Magdalena
  gMagdalenaD5TeV = new TGraphErrors("TheoryPredictions/Magdalena-5TeV-0100-plot2.txt");
  gMagdalenaD5TeV->SetLineWidth(3);
  gMagdalenaD5TeV->SetLineColor(kRed-7);//kCyan+1
  gMagdalenaD5TeV->SetFillColor(kRed-4);//kCyan+1
  gMagdalenaD5TeV->SetFillColorAlpha(kRed-4,0.5);//kCyan+1
  gMagdalenaD5TeV->SetFillStyle(3344);//3004

  // ADSCFT 1
  gADSCFT1D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0080_D0_DiffusionConstant_band.dat");
  gADSCFT1D5TeV->SetName("gADSCFT1D5TeV");
  gADSCFT1D5TeV->SetLineColor(0);
  gADSCFT1D5TeV->SetFillColor(kOrange+1);//kGreen-2
  gADSCFT1D5TeV->SetFillColorAlpha(kOrange+1,0.6);//kGreen-2
  gADSCFT1D5TeV->SetFillStyle(3325);
  // ADSCFT 2
  gADSCFT2D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0080_D0_DiffusionDynamic_band.dat");
  gADSCFT2D5TeV->SetName("gADSCFT2D5TeV");
  gADSCFT2D5TeV->SetLineColor(0);//kViolet-8
  gADSCFT2D5TeV->SetFillColor(kPink-9);//kViolet-8
  gADSCFT2D5TeV->SetFillColorAlpha(kPink-9,0.6);//kViolet-8
  gADSCFT2D5TeV->SetFillStyle(3352);

  //
  gADSCFT1D5TeV->Draw("4 same");
  gMagdalenaD5TeV->Draw("f same");
  gMagdalenaD5TeV->Draw("l same");
  gCUJETD5TeV->Draw("3 same");
  gShanshanD5TeV->Draw("c same");
  gADSCFT2D5TeV->Draw("4 same");
}

void drawTheory010(Int_t isTheoryComparison)
{
  gStyle->SetHatchesLineWidth(3);

  // CUJET
  TFile* infCUJETD5TeV = new TFile("TheoryPredictions/CUJET_D0_RAA_0_10.root");
  gCUJETD5TeV = (TGraphAsymmErrors*)infCUJETD5TeV->Get("gRAADmeson5TeV");
  gCUJETD5TeV->SetLineWidth(1);
  gCUJETD5TeV->SetLineColor(0);//4
  gCUJETD5TeV->SetFillColor(kAzure-1);//4
  gCUJETD5TeV->SetFillColorAlpha(kAzure-2,0.6);
  gCUJETD5TeV->SetFillStyle(3481);//3001
  // Shanshan
  gShanshanD5TeV = new TGraph("TheoryPredictions/Shanshan-D-RAA_PbPb5020_00-10.dat");
  gShanshanD5TeV->SetLineWidth(3);
  gShanshanD5TeV->SetLineColor(kRed+1);
  // Magdalena
  gMagdalenaD5TeV = new TGraphErrors("TheoryPredictions/Magdalena-5TeV-plot2.txt");
  gMagdalenaD5TeV->SetLineWidth(3);
  gMagdalenaD5TeV->SetLineColor(kRed-7);//kCyan+1
  gMagdalenaD5TeV->SetFillColor(kRed-4);//kCyan+1
  gMagdalenaD5TeV->SetFillColorAlpha(kRed-4,0.5);//kCyan+1
  gMagdalenaD5TeV->SetFillStyle(3344);//3004
  // PHSD w/o shadowing
  gPHSDWOShadowing = new TGraphErrors("TheoryPredictions/phsd502TeVWoShadowing.txt");
  gPHSDWOShadowing->SetLineColor(kAzure-6);//kGreen+2
  gPHSDWOShadowing->SetLineWidth(3);
  gPHSDWOShadowing->SetLineStyle(2);
  // PHSD w/ shadowing
  gPHSDWShadowing = new TGraphErrors("TheoryPredictions/phsd502TeVWShadowing.txt");
  gPHSDWShadowing->SetLineColor(kAzure-6);//kGreen+2
  gPHSDWShadowing->SetLineWidth(3);
  gPHSDWShadowing->SetLineStyle(1);
  // Ivan 
  //gIvanD5TeV = new TGraph("TheoryPredictions/R-PbPb_cen_cron1.5_eloss1.5.5100GeVD0.txt");
  gIvanD5TeV = new TGraph("TheoryPredictions/D0cmsCENTPbPb.txt");
  gIvanD5TeV->SetLineColor(kViolet+1);//kViolet
  gIvanD5TeV->SetFillColor(kViolet+1);//kViolet
  gIvanD5TeV->SetFillColorAlpha(kViolet+1,0.5);
  gIvanD5TeV->SetFillStyle(3358);//3011
  gIvanD5TeV->SetLineWidth(3);

  // ADSCFT 1
  gADSCFT1D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0010_D0_DiffusionConstant_band.dat");
  gADSCFT1D5TeV->SetName("gADSCFT1D5TeV");
  gADSCFT1D5TeV->SetLineColor(0);
  gADSCFT1D5TeV->SetFillColor(kOrange+1);//kGreen-2
  gADSCFT1D5TeV->SetFillColorAlpha(kOrange+1,0.6);//kGreen-2
  gADSCFT1D5TeV->SetFillStyle(3325);
  // ADSCFT 2
  gADSCFT2D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0010_D0_DiffusionDynamic_band.dat");
  gADSCFT2D5TeV->SetName("gADSCFT2D5TeV");
  gADSCFT2D5TeV->SetLineColor(0);//kViolet-8
  gADSCFT2D5TeV->SetFillColor(kPink-9);//kViolet-8
  gADSCFT2D5TeV->SetFillColorAlpha(kPink-9,0.6);//kViolet-8
  gADSCFT2D5TeV->SetFillStyle(3352);

  if(isTheoryComparison==1||isTheoryComparison==2)
    {
      gMagdalenaD5TeV->Draw("f same");
      gMagdalenaD5TeV->Draw("l same");
      gIvanD5TeV->Draw("f same");
      gIvanD5TeV->Draw("l same");
      gCUJETD5TeV->Draw("3 same");
    }
  if (isTheoryComparison==1||isTheoryComparison==3)
    {
      gADSCFT1D5TeV->Draw("4 same");
      gPHSDWShadowing->Draw("c same");
      gPHSDWOShadowing->Draw("c same");
      gShanshanD5TeV->Draw("c same");
      gADSCFT2D5TeV->Draw("4 same");
    }

}

TGraphErrors* fillgadscft(TString datfile)
{
  const int n = 1000;
  Float_t bCx[n],bCy[n],bCye[n],bDummy[n];
  Int_t nbin=0;
  ifstream getadscft(datfile);
  if(!getadscft.is_open()) cout<<"Opening the file fails: ADS/CFT DiffusionConstant"<<endl;
  nbin=0;
  while(!getadscft.eof())
    {
      getadscft>>bCx[nbin]>>bCy[nbin]>>bDummy[nbin]>>bCye[nbin];
      nbin++;
    }
  bCx[nbin] = bCx[nbin-1];
  bCy[nbin] = bCy[nbin-1];
  bCye[nbin] = bCye[nbin-1];
  nbin++;
  Float_t* aADSCFTD5TeVx = new Float_t[nbin];
  Float_t* aADSCFTD5TeVxe = new Float_t[nbin];
  Float_t* aADSCFTD5TeVy = new Float_t[nbin];
  Float_t* aADSCFTD5TeVye = new Float_t[nbin];
  for(int i=0;i<nbin;i++)
    {
      aADSCFTD5TeVx[i] = bCx[i];
      aADSCFTD5TeVxe[i] = 0;
      aADSCFTD5TeVy[i] = bCy[i];
      aADSCFTD5TeVye[i] = bCye[i];
    }
  getadscft.close();
  getadscft.clear();

  TGraphErrors* gadscft = new TGraphErrors(nbin, aADSCFTD5TeVx, aADSCFTD5TeVy, aADSCFTD5TeVxe, aADSCFTD5TeVye);
  return gadscft;
}

void drawTheoryPP(Bool_t isRatio, TH1D* hSigmaStatMB=0, TH1D* hSigmaStat=0, TGraphAsymmErrors* gaeCrossSystMB=0, TGraphAsymmErrors* gaeCrossSyst=0, Bool_t verbose=false)
{
  const int npost = 15;
  TString postfix[npost] = {"111","112","11h","121","122","1h1","1hh","211","212","221","222","h11","h1h","hh1","hhh"};
  TString suffix = "TheoryPredictions/cms5_d0_22_32/cms5_d0_22_32";
  const int n = 1000;
  Float_t ptmin[n],ptmax[n];
  Int_t nbin=0;
  ifstream getgmvfns_init(Form("%s_%s.dat",suffix.Data(),postfix[0].Data()));
  if(!getgmvfns_init.is_open()) cout<<"Opening the file fails: "<<Form("%s_%s.dat",suffix.Data(),postfix[0].Data())<<endl;
  nbin=0;
  while(!getgmvfns_init.eof())
    {
      Float_t temp;
      getgmvfns_init>>ptmin[nbin];
      if(getgmvfns_init.eof()) break;
      getgmvfns_init>>ptmax[nbin]>>temp>>temp>>temp>>temp>>temp;      
      nbin++;
    }
  getgmvfns_init.close();
  getgmvfns_init.clear();

  Float_t yall[npost][nbin];
  Float_t ymin[nbin],ymax[nbin];
  Int_t xmin[nbin],xmax[nbin];
  for(int j=0;j<npost;j++)
    {
      ifstream getgmvfns(Form("%s_%s.dat",suffix.Data(),postfix[j].Data()));
      if(!getgmvfns.is_open()) cout<<"Opening the file fails: "<<Form("%s_%s.dat",suffix.Data(),postfix[j].Data())<<endl;
      for(int i=0;i<nbin;i++)
        {
          Float_t temp;
          getgmvfns>>temp>>temp>>temp>>temp>>temp>>temp>>yall[j][i];
          yall[j][i]*=1000;
          if(j==0)
            {
              ymin[i] = yall[j][i];
              ymax[i] = yall[j][i];
              xmin[i] = j;
              xmax[i] = j;
            }
          else
            {
              if(yall[j][i]<ymin[i]) 
                {
                  ymin[i] = yall[j][i];
                  xmin[i] = j;
                }
              if(yall[j][i]>ymax[i]) 
                {
                  ymax[i] = yall[j][i];
                  xmax[i] = j;
                }
            }
        }
    }

  Float_t* aGMVFNSD5TeVx = new Float_t[nbin];
  Float_t* aGMVFNSD5TeVxe = new Float_t[nbin];
  Float_t* aGMVFNSD5TeVy = new Float_t[nbin];
  Float_t* aGMVFNSD5TeVyel = new Float_t[nbin];
  Float_t* aGMVFNSD5TeVyeh = new Float_t[nbin];
  Float_t* aGMVFNSD5TeVuy = new Float_t[nbin];
  Float_t* aGMVFNSD5TeVuyel = new Float_t[nbin];
  Float_t* aGMVFNSD5TeVuyeh = new Float_t[nbin];
  for(int i=0;i<nbin;i++)
    {
      aGMVFNSD5TeVx[i] = (ptmax[i]+ptmin[i])/2.;
      aGMVFNSD5TeVxe[i] = (ptmax[i]-ptmin[i])/2.;
      aGMVFNSD5TeVy[i] = yall[0][i];
      aGMVFNSD5TeVyel[i] = yall[0][i] - ymin[i];
      aGMVFNSD5TeVyeh[i] = ymax[i] - yall[0][i];
      if(verbose)
        {
          if(i==0) cout<<left<<"  "<<setw(8)<<"pT min"<<setw(8)<<"pT max"<<setw(10)<<"xsec min"<<setw(10)<<"xsec max"<<setw(10)<<"xsec"<<endl;
          cout<<left<<"  "<<setw(8)<<ptmin[i]<<setw(8)<<ptmax[i]<<setw(10)<<postfix[xmin[i]]<<setw(10)<<postfix[xmax[i]]<<setw(10)<<yall[0][i]<<endl;
        }
      aGMVFNSD5TeVuy[i] = 1;
      aGMVFNSD5TeVuyel[i] = aGMVFNSD5TeVyel[i]/aGMVFNSD5TeVy[i];
      aGMVFNSD5TeVuyeh[i] = aGMVFNSD5TeVyeh[i]/aGMVFNSD5TeVy[i];
    }
  gGMVFNSD5TeV = new TGraphAsymmErrors(nbin, aGMVFNSD5TeVx, aGMVFNSD5TeVy, aGMVFNSD5TeVxe, aGMVFNSD5TeVxe, aGMVFNSD5TeVyel, aGMVFNSD5TeVyeh);
  /*
  gGMVFNSD5TeV->SetFillColor(kRed-4);
  gGMVFNSD5TeV->SetFillColorAlpha(kRed-4,0.5);
  gGMVFNSD5TeV->SetFillStyle(1001);
  gGMVFNSD5TeV->SetLineWidth(1);
  gGMVFNSD5TeV->SetLineColor(4);
  */
  gGMVFNSD5TeV->SetFillColor(kGreen-5);// kRed-7
  gGMVFNSD5TeV->SetFillColorAlpha(kGreen-5,0.1);
  //gGMVFNSD5TeV->SetFillStyle(1001);
  gGMVFNSD5TeV->SetFillStyle(3001);
  gGMVFNSD5TeV->SetLineWidth(2);
  gGMVFNSD5TeV->SetLineColor(kGreen+3);// kRed+2
  if(!isRatio) gGMVFNSD5TeV->Draw("5same");

  //
  if(!isRatio) return;
  //

  gGMVFNSD5TeVunity = new TGraphAsymmErrors(nbin, aGMVFNSD5TeVx, aGMVFNSD5TeVuy, aGMVFNSD5TeVxe, aGMVFNSD5TeVxe, aGMVFNSD5TeVuyel, aGMVFNSD5TeVuyeh);
  /*
  gGMVFNSD5TeVunity->SetFillColor(kRed-4);
  gGMVFNSD5TeVunity->SetFillColorAlpha(kRed-4,0.5);
  gGMVFNSD5TeVunity->SetFillStyle(1001);
  gGMVFNSD5TeVunity->SetLineWidth(1);
  gGMVFNSD5TeVunity->SetLineColor(4);
  */
  gGMVFNSD5TeVunity->SetFillColor(kGreen-5); // kRed-7
  gGMVFNSD5TeVunity->SetFillColorAlpha(kGreen-5,0.1);
  //gGMVFNSD5TeVunity->SetFillStyle(1001);
  gGMVFNSD5TeVunity->SetFillStyle(3001);
  gGMVFNSD5TeVunity->SetLineWidth(2);
  gGMVFNSD5TeVunity->SetLineColor(kGreen+3);// kRed+2
  gGMVFNSD5TeVunity->Draw("5same");

  TH1D* hRatioSigmaStatMB = (TH1D*)hSigmaStatMB->Clone("hRatioSigmaStatMB");
  TGraphAsymmErrors* gaeRatioCrossSystMB = (TGraphAsymmErrors*)gaeCrossSystMB->Clone("gaeRatioCrossSystMB");
  TH1D* hRatioSigmaStat = (TH1D*)hSigmaStat->Clone("hRatioSigmaStat");
  TGraphAsymmErrors* gaeRatioCrossSyst = (TGraphAsymmErrors*)gaeCrossSyst->Clone("gaeRatioCrossSyst");
  Int_t endbinMB=0,endbin=0, ibin=0;
  while(!(endbinMB&&endbin))
    {
      if(ibin>(hSigmaStatMB->GetSize()-3)) endbinMB++;
      else
        {
          Int_t getbinMB = findbin(hSigmaStatMB->GetBinCenter(ibin+1),ptmin,ptmax,nbin);
          hRatioSigmaStatMB->SetBinContent(ibin+1,hSigmaStatMB->GetBinContent(ibin+1)/aGMVFNSD5TeVy[getbinMB]);
          hRatioSigmaStatMB->SetBinError(ibin+1,hSigmaStatMB->GetBinError(ibin+1)/aGMVFNSD5TeVy[getbinMB]);
          Double_t xxMB,yyMB,eylMB,eyhMB;
          gaeCrossSystMB->GetPoint(ibin,xxMB,yyMB);
          gaeRatioCrossSystMB->SetPoint(ibin,xxMB,yyMB/aGMVFNSD5TeVy[getbinMB]);
          eylMB = gaeCrossSystMB->GetErrorYlow(ibin);
          eyhMB = gaeCrossSystMB->GetErrorYhigh(ibin);
          gaeRatioCrossSystMB->SetPointEYlow(ibin,eylMB/aGMVFNSD5TeVy[getbinMB]);
          gaeRatioCrossSystMB->SetPointEYhigh(ibin,eyhMB/aGMVFNSD5TeVy[getbinMB]);
        }
      if(ibin>(hSigmaStat->GetSize()-3)) endbin++;
      else
        {
          Int_t getbin = findbin(hSigmaStat->GetBinCenter(ibin+1),ptmin,ptmax,nbin);
          hRatioSigmaStat->SetBinContent(ibin+1,hSigmaStat->GetBinContent(ibin+1)/aGMVFNSD5TeVy[getbin]);
          hRatioSigmaStat->SetBinError(ibin+1,hSigmaStat->GetBinError(ibin+1)/aGMVFNSD5TeVy[getbin]);
          Double_t xx,yy,eyl,eyh;
          gaeCrossSyst->GetPoint(ibin,xx,yy);
          gaeRatioCrossSyst->SetPoint(ibin,xx,yy/aGMVFNSD5TeVy[getbin]);
          eyl = gaeCrossSyst->GetErrorYlow(ibin);
          eyh = gaeCrossSyst->GetErrorYhigh(ibin);
          gaeRatioCrossSyst->SetPointEYlow(ibin,eyl/aGMVFNSD5TeVy[getbin]);
          gaeRatioCrossSyst->SetPointEYhigh(ibin,eyh/aGMVFNSD5TeVy[getbin]);
        }
      ibin++;
    }
  hRatioSigmaStatMB->Draw("epsame");
  gaeRatioCrossSystMB->Draw("5same");
  hRatioSigmaStat->Draw("epsame");
  gaeRatioCrossSyst->Draw("5same");
}


Int_t findbin(Float_t bincenter, Float_t* ptmin, Float_t* ptmax, Int_t nbin)
{
  for(int i=0;i<nbin;i++)
    {
      if(bincenter>=ptmin[i] && bincenter<ptmax[i]) return i;
    }
  cout<<"  Error: findbin error."<<endl;
  return -1;
}
