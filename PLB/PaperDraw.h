#ifndef _PAPERDRAW_H_
#define _PAPERDRAW_H_

Float_t dxp = 10./12;
Float_t dypSigma = 7./12;
Float_t dypFOBor = 2./12;
Float_t dypGMBor = 3./12;
Float_t dypLong = 12./12;
Float_t ypadl = dypGMBor;
Float_t ypadh = dypGMBor+dypFOBor;
Float_t TEXsizeratio = 0.073/0.107; // why?


Float_t leftmarginp        = 0.19;						   // 0.15
Float_t rightmarginp       = 0.025;						   // 0.03
Float_t bottommarginpGMBor = 0.33;						   // 0.33
Float_t topmarginpSigma    = 0.10;						   // 0.07
Float_t bottommarginpLong  = bottommarginpGMBor*dypGMBor;                          // 0.0825
Float_t topmarginpLong     = 1-((1-topmarginpSigma)*dypSigma+dypGMBor+dypFOBor);   //0.040833

Float_t ytitlesizepSigma   = 0.067;						   // 0.05
Float_t ytitlesizepFOBor   = ytitlesizepSigma*dypSigma/dypFOBor;                   // 0.1825
Float_t ytitlesizepGMBor   = ytitlesizepSigma*dypSigma/dypGMBor;                   // 0.12
Float_t ytitlesizepLong    = ytitlesizepSigma*dypSigma/dxp;                        // 0.035

Float_t ylabelsizepSigma   = 0.058;                                                // 0.04571
Float_t ylabelsizepFOBor   = ylabelsizepSigma*dypSigma/dypFOBor;                   // 0.15238
Float_t ylabelsizepGMBor   = ylabelsizepSigma*dypSigma/dypGMBor;                   // 0.10159
Float_t ylabelsizepLong    = ylabelsizepSigma*dypSigma/dxp;                        // 0.032

Float_t xtitlesizepGMBor   = ytitlesizepGMBor;					   // 0.13
Float_t xlabelsizepGMBor   = 0.13;						   // 0.1
Float_t xtitlesizepLong    = ytitlesizepLong;   		                   // 0.037452
Float_t xlabelsizepLong    = xlabelsizepGMBor*dypGMBor/dxp;                        // 0.02881

Float_t ytitleoffsetpSigma = 1.17;                                                 // 1.25
Float_t ytitleoffsetpFOBor = ytitleoffsetpSigma/(dypSigma/dypFOBor);               // 0.36367
Float_t ytitleoffsetpGMBor = ytitleoffsetpSigma/(dypSigma/dypGMBor);               // 0.5455
Float_t ytitleoffsetpLong  = ytitleoffsetpSigma/(dypSigma/dxp);                    // 1.7861

Float_t xtitleoffsetpGMBor = 0.85;                                                 // 0.5455
Float_t xtitleoffsetpLong  = xtitleoffsetpGMBor*(dypGMBor/dypLong)/(dypGMBor/dxp); // 0.86

Float_t CMSxposBor         = 0.23;                                                 // 0.19
Float_t CMSyposBor         = 0.865;                                                // 0.87656
Float_t CMSsizeBor         = 0.090;                                                // 0.107
Float_t CMSxposLong        = CMSxposBor;                                           // 0.19
Float_t CMSyposLong        = CMSyposBor*dypSigma+dypGMBor+dypFOBor;                // 0.928
Float_t CMSsizeLong        = CMSsizeBor*TEXsizeratio;                              // 0.073

Float_t DZEROxposBor       = 0.948;                                                // 0.939
Float_t DZEROyposBor       = 0.895;                                                // 0.915
Float_t DZEROsizeBor       = CMSsizeBor;                                           // 0.107
Float_t DZEROxposLong      = DZEROxposBor;                                         // 0.94
Float_t DZEROyposLong      = DZEROyposBor*dypSigma+dypGMBor+dypFOBor;              // 0.95
Float_t DZEROsizeLong      = DZEROsizeBor*TEXsizeratio;                            // 0.073

Float_t YxposBor           = CMSxposBor;                                           // 0.19
Float_t YyposBor           = CMSyposBor-0.13;                                      // 0.73427
Float_t YsizeBor           = 0.07328;                                              // 0.07328
Float_t YxposLong          = CMSxposBor;                                           // 0.19
Float_t YyposLong          = YyposBor*dypSigma+dypGMBor+dypFOBor;                  // 0.845
Float_t YsizeLong          = YsizeBor*TEXsizeratio;                                // 0.05

Float_t LumixposBor        = 0.98;                                                 // 0.95
Float_t LumiyposBor        = 0.94;                                                 // 0.96
Float_t LumisizeBor        = 0.054;                                                // 0.045
Float_t LumixposLong       = LumixposBor;                                          // 0.95
Float_t LumiyposLong       = LumiyposBor*dypSigma+dypGMBor+dypFOBor;               // 0.976667
Float_t LumisizeLong       = LumisizeBor*TEXsizeratio;                             // 0.03025

TString texper="%";
TString str_texY = "|y| < 1.0";
TString str_texCMS = "CMS";
TString str_texDzero = "#frac{D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}}{2}";

void scaleNsetCrossSection(TH1D* hSigmaStat, TGraphAsymmErrors* gaeCrossSyst, Double_t fscale, Int_t pcolor, Int_t pstyle, Bool_t verbose=false)
{
  Int_t ngrbins = gaeCrossSyst->GetN();
  for(int i=0;i<ngrbins;i++)
    {
      Double_t x,y;
      gaeCrossSyst->GetPoint(i,x,y);
      gaeCrossSyst->SetPoint(i,x,y*fscale);
      Double_t exl = gaeCrossSyst->GetErrorXlow(i);
      Double_t exh = gaeCrossSyst->GetErrorXhigh(i);
      Double_t eyl = gaeCrossSyst->GetErrorYlow(i);
      Double_t eyh = gaeCrossSyst->GetErrorYhigh(i);
      gaeCrossSyst->SetPointError(i,exl,exh,eyl*fscale,eyh*fscale);
      if(verbose)
        {
          std::cout<<std::setiosflags(std::ios::left)<<"  "<<std::setw(5)<<i;
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(8)<<x<<std::setw(15)<<y<<std::setw(15)<<hSigmaStat->GetBinContent(i+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<eyl<<std::setw(15)<<eyh<<std::endl;
        }
    }
  hSigmaStat->Scale(fscale);
  if(verbose) std::cout<<std::endl;

  Size_t msize = 1.5; // 1.5
  if(pstyle==33) msize*=1.6;

  hSigmaStat->SetLineWidth(2);
  hSigmaStat->SetMarkerSize(msize);
  hSigmaStat->SetMarkerStyle(pstyle);
  hSigmaStat->SetLineColor(pcolor);
  hSigmaStat->SetMarkerColor(pcolor);

  gaeCrossSyst->SetMarkerSize(msize);
  gaeCrossSyst->SetMarkerStyle(pstyle);
  gaeCrossSyst->SetFillColor(1);
  gaeCrossSyst->SetFillStyle(0);
  gaeCrossSyst->SetLineWidth(2);
  gaeCrossSyst->SetLineColor(pcolor);
}


Float_t xtitleoffsetpRAA = 1.10;           // 1.10
Float_t ytitleoffsetpRAA = 1.15;           // 1.15
Float_t xtitlesizepRAA   = 0.06;           // 0.06
Float_t ytitlesizepRAA   = 0.06;           // 0.06
Float_t xlabelsizepRAA   = 0.045;          // 0.045
Float_t ylabelsizepRAA   = 0.045;          // 0.045

Float_t xtitleoffsetpFit = 1.00;           // 0.95
Float_t ytitleoffsetpFit = 1.3;            // 1.3
Float_t xtitlesizepFit   = xtitlesizepRAA; // 0.062
Float_t ytitlesizepFit   = ytitlesizepRAA; // 0.062
Float_t xlabelsizepFit   = xlabelsizepRAA; // 0.045
Float_t ylabelsizepFit   = xlabelsizepRAA; // 0.045

Size_t  msizepFit        = 1.3;            // 1.55
Width_t lwidthpFit       = 6;              // 9

Float_t CMSxposRAA       = 0.22;           // 0.22
Float_t CMSyposRAA       = 0.89;           // 0.90
Float_t CMSsizeRAA       = 0.062;          // 0.60
Float_t CMSxposFit       = CMSxposRAA;     // 0.215
Float_t CMSyposFit       = CMSyposRAA;     // 0.87
Float_t CMSsizeFit       = CMSsizeRAA;     // 0.08

Float_t DZEROxposRAA     = CMSxposRAA;     // 0.22
Float_t DZEROyposRAA     = 0.84;           // 0.86
Float_t DZEROsizeRAA     = CMSsizeRAA;     // 0.06
Float_t DZEROxposFit     = DZEROxposRAA;   // 0.218
Float_t DZEROyposFit     = DZEROyposRAA;   // 0.77
Float_t DZEROsizeFit     = DZEROsizeRAA;   // 0.057

Float_t LumixposRAA      = 0.96;           // 0.19
Float_t LumiyposRAA      = 0.936;          // 0.936
Float_t LumisizeRAA      = 0.038;          // 0.038
Float_t LumixposFit      = LumixposRAA;    // 0.945
Float_t LumiyposFit      = LumiyposRAA;    // 0.94
Float_t LumisizeFit      = LumisizeRAA;    // 0.06


#endif
