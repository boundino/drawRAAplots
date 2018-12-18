#include "../uti.h"
/* ALICE SQM 2017 Preliminary result */

TGraphErrors* grRAAalicestat;
TGraphAsymmErrors* grRAAalicesyst;
void drawAliceD0Raa()
{
  const int BIN_NUM = 13;
  Float_t apt[BIN_NUM], aptl[BIN_NUM], apth[BIN_NUM], acentral[BIN_NUM], astat[BIN_NUM], asystl[BIN_NUM], asysth[BIN_NUM], azero[BIN_NUM], aptlnarrow[BIN_NUM], apthnarrow[BIN_NUM];
  std::ifstream getdata("AliceRaa/AliceD0Raa_0_10.dat"); 
  for(int i=0;i<BIN_NUM;i++)
    {
      Float_t tem;
      getdata>>apt[i]>>acentral[i]>>aptl[i]>>tem>>apth[i]>>tem>>tem>>astat[i]>>tem>>asysth[i]>>tem>>asystl[i];
      aptl[i] = apt[i] - aptl[i];
      apth[i] = apth[i] - apt[i];
      astat[i] = TMath::Abs(astat[i] - acentral[i]);
      asysth[i] = asysth[i] - acentral[i];
      asystl[i] = acentral[i] - asystl[i];
      azero[i] = 0;
      aptlnarrow[i] = apt[i]*0.08;
      apthnarrow[i] = apt[i]*0.08;
   }
  grRAAalicestat = new TGraphErrors(BIN_NUM, apt, acentral, aptl, astat);
  grRAAalicestat->SetMarkerStyle(20);
  grRAAalicestat->SetMarkerColor(kRed+2);
  grRAAalicestat->SetMarkerSize(1.2);
  grRAAalicestat->SetLineColor(kRed+2);
  grRAAalicestat->SetLineWidth(2);
  grRAAalicesyst = new TGraphAsymmErrors(BIN_NUM, apt, acentral, aptlnarrow, apthnarrow, asystl, asysth);
  grRAAalicesyst->SetMarkerStyle(20);
  grRAAalicesyst->SetMarkerColor(kRed+2);
  grRAAalicesyst->SetMarkerSize(1.2);
  grRAAalicesyst->SetLineColor(kRed+2);
  grRAAalicesyst->SetLineWidth(2);
  grRAAalicesyst->SetFillStyle(0);

  grRAAalicestat->Draw("pe same");
  grRAAalicesyst->Draw("5 same");

}
