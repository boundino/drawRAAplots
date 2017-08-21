TGraphErrors* gre;
TGraphErrors* gre2;

void expBeautyCMS_20170201()
{
  //=========Macro generated from canvas: c2/c2
  //=========  (Wed Feb  1 19:16:45 2017) by ROOT version5.34/36

  Color_t fcolor = kViolet-8; // kGray+2
  Float_t falpha = 0.3; // 0.5
  Color_t mcolor = kViolet+4; // kGray+3
  Float_t logxerrfactor = 0.08;

  gre = new TGraphErrors(6);
  gre->SetName("Graph0");
  gre->SetTitle("Graph0");

  gre->SetFillColor(fcolor);
  gre->SetFillColorAlpha(fcolor, falpha);
  gre->SetMarkerColor(mcolor);
  gre->SetMarkerStyle(29);
  gre->SetMarkerSize(2);
  gre->SetLineColor(0);
  gre->SetPoint(0,      7.5,                 0.4664189);
  gre->SetPointError(0, 7.5*logxerrfactor,   0.05427119); // 0.5
  gre->SetPoint(1,      9,                   0.4856157);
  gre->SetPointError(1, 9*logxerrfactor,     0.04438349); // 0.5
  gre->SetPoint(2,      10.25,               0.4065521);
  gre->SetPointError(2, 10.25*logxerrfactor, 0.03578226); // 0.5
  gre->SetPoint(3,      12,                  0.4536073);
  gre->SetPointError(3, 12*logxerrfactor,    0.05860495); // 0.5
  gre->SetPoint(4,      14.5,                0.3694549);
  gre->SetPointError(4, 14.5*logxerrfactor,  0.0518269);  // 0.5
  gre->SetPoint(5,      23,                  0.3521646);
  gre->SetPointError(5, 23*logxerrfactor,    0.06848064); // 0.5
  gre->Draw("2 same");

  TGraphErrors* grestat = new TGraphErrors(6);
  grestat->SetName("Graph0stat");
  grestat->SetTitle("Graph0stat");
  grestat->SetMarkerColor(mcolor);
  grestat->SetMarkerStyle(29);
  grestat->SetMarkerSize(2);
  grestat->SetLineWidth(1);
  grestat->SetPoint(0,      7.5,   0.4664189);
  grestat->SetPointError(0, 1,     0.02632702);
  grestat->SetPoint(1,      9,     0.4856157);
  grestat->SetPointError(1, 0.5,   0.0353226);
  grestat->SetPoint(2,      10.25, 0.4065521);
  grestat->SetPointError(2, 0.75,  0.0288783);
  grestat->SetPoint(3,      12,    0.4536073);
  grestat->SetPointError(3, 1,     0.03347202);
  grestat->SetPoint(4,      14.5,  0.3694549);
  grestat->SetPointError(4, 1.5,   0.03358354);
  grestat->SetPoint(5,      23,    0.3521646);
  grestat->SetPointError(5, 7,     0.0311077);
  grestat->Draw("p same");
   
  gre2 = new TGraphErrors(6);
  gre2->SetName("Graph1");
  gre2->SetTitle("Graph1");
  gre2->SetFillColor(fcolor);
  gre2->SetFillColorAlpha(fcolor, falpha);
  gre2->SetMarkerColor(mcolor);
  gre2->SetMarkerStyle(34);
  gre2->SetMarkerSize(1.7);
  gre2->SetLineColor(0);
  gre2->SetPoint(0,      3.75,               0.7535804);
  gre2->SetPointError(0, 3.75*logxerrfactor, 0.21432);    // 0.4
  gre2->SetPoint(1,      5,                  0.6891029);
  gre2->SetPointError(1, 5*logxerrfactor,    0.1218303);  // 0.4
  gre2->SetPoint(2,      6,                  0.5425812);
  gre2->SetPointError(2, 6*logxerrfactor,    0.08921681); // 0.4
  gre2->Draw("2 same");

  TGraphErrors* gre2stat = new TGraphErrors(3);
  gre2stat->SetName("Graph1stat");
  gre2stat->SetTitle("Graph1stat");
  gre2stat->SetMarkerColor(mcolor);
  gre2stat->SetMarkerStyle(34);
  gre2stat->SetMarkerSize(1.7);
  gre2stat->SetLineWidth(1);
  gre2stat->SetPoint(0,      3.75, 0.7535804);
  gre2stat->SetPointError(0, 0.75, 0.1209346);
  gre2stat->SetPoint(1,      5,    0.6891029);
  gre2stat->SetPointError(1, 0.5,  0.1059286);
  gre2stat->SetPoint(2,      6,    0.5425812);
  gre2stat->SetPointError(2, 0.5,  0.07363414);
  gre2stat->Draw("p same");
   
}
