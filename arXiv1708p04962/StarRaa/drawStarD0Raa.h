#include "../uti.h"
/* STAR result */

TGraphErrors* grRAAstarstat;
TGraphAsymmErrors* grRAAstarsyst;
void drawStarD0Raa()
{
  const int BIN_NUM = 7;
  Float_t apt[BIN_NUM], aptl[BIN_NUM], apth[BIN_NUM], acentral[BIN_NUM], astat[BIN_NUM], asystl[BIN_NUM], asysth[BIN_NUM], azero[BIN_NUM], aptlnarrow[BIN_NUM], apthnarrow[BIN_NUM];
  std::ifstream getdata("StarRaa/StarD0Raa_0_10.dat"); 
  for(int i=0;i<BIN_NUM;i++)
    {
      Float_t tem;
      getdata>>apt[i]>>acentral[i]>>tem>>astat[i]>>tem>>asysth[i];
      //aptl[i] = 0;
      //apth[i] = 0;
      astat[i] = TMath::Abs(astat[i] - acentral[i]);
      asysth[i] = asysth[i] - acentral[i];
      asystl[i] = asysth[i];
      azero[i] = 0;
      aptlnarrow[i] = apt[i]*0.08;
      apthnarrow[i] = apt[i]*0.08;
   }
  grRAAstarstat = new TGraphErrors(BIN_NUM, apt, acentral, azero, astat);
  grRAAstarstat->SetMarkerStyle(20);
  grRAAstarstat->SetMarkerColor(kBlue+2);
  grRAAstarstat->SetMarkerSize(1.2);
  grRAAstarstat->SetLineColor(kBlue+2);
  grRAAstarstat->SetLineWidth(2);
  grRAAstarsyst = new TGraphAsymmErrors(BIN_NUM, apt, acentral, aptlnarrow, apthnarrow, asystl, asysth);
  grRAAstarsyst->SetMarkerStyle(20);
  grRAAstarsyst->SetMarkerColor(kBlue+2);
  grRAAstarsyst->SetMarkerSize(1.2);
  grRAAstarsyst->SetLineColor(kBlue+2);
  grRAAstarsyst->SetLineWidth(2);
  grRAAstarsyst->SetFillStyle(0);

  grRAAstarstat->Draw("pe same");
  grRAAstarsyst->Draw("5 same");

}
