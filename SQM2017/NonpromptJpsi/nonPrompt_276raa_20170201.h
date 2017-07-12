TGraphErrors* gre;
TGraphErrors* gre2;

Int_t cifillJ;

void expBeautyCMS_20170201()
{
//=========Macro generated from canvas: c2/c2
//=========  (Wed Feb  1 19:16:45 2017) by ROOT version5.34/36

  Int_t cimarker = kRed+2;//kGray+3
  Int_t cifill = kRed-9;//kGray+2

  cifillJ = cifill;
  gre2 = new TGraphErrors(3);
  gre2->SetName("Graph1");
  gre2->SetTitle("Graph1");
  gre2->SetFillColor(cifill);
  gre2->SetFillColorAlpha(cifill, 0.5);
  gre2->SetMarkerColor(cimarker);
  gre2->SetMarkerStyle(34);
  gre2->SetMarkerSize(1.7);
  //gre2->SetLineColor(cimarker);
  gre2->SetLineColor(0);
  gre2->SetPoint(0,3.75,0.7535804);
  gre2->SetPointError(0,3.75*0.08,0.21432);//0.36
  gre2->SetPoint(1,5,0.6891029);
  gre2->SetPointError(1,5*0.08,0.1218303);//0.4
  gre2->SetPoint(2,6,0.5425812);
  gre2->SetPointError(2,6*0.08,0.08921681);//0.42   
  gre2->Draw("2 same");
  
  TGraphErrors* gre2stat = new TGraphErrors(3);
  gre2stat->SetName("Graph1stat");
  gre2stat->SetTitle("Graph1stat");
  gre2stat->SetMarkerColor(cimarker);
  gre2stat->SetLineColor(cimarker);
  gre2stat->SetMarkerStyle(34);
  gre2stat->SetMarkerSize(1.7);
  gre2stat->SetPoint(0,3.75,0.7535804);
  gre2stat->SetPointError(0,0.75,0.1209346);
  gre2stat->SetPoint(1,5,0.6891029);
  gre2stat->SetPointError(1,0.5,0.1059286);
  gre2stat->SetPoint(2,6,0.5425812);
  gre2stat->SetPointError(2,0.5,0.07363414);
  gre2stat->Draw("p same");
  
  gre = new TGraphErrors(6);
  gre->SetName("Graph0");
  gre->SetTitle("Graph0");
  
  gre->SetFillColor(cifill);
  gre->SetFillColorAlpha(cifill, 0.5);
  gre->SetMarkerColor(cimarker);
  gre->SetMarkerStyle(29);
  gre->SetMarkerSize(2);
  //gre->SetLineColor(cimarker);
  gre->SetLineColor(0);
  gre->SetPoint(0,7.5,0.4664189);
  gre->SetPointError(0,7.5*0.08,0.05427119);//0.44
  gre->SetPoint(1,9,0.4856157);
  gre->SetPointError(1,9*0.08,0.04438349);//0.52
  gre->SetPoint(2,10.25,0.4065521);
  gre->SetPointError(2,10.25*0.08,0.03578226);//0.62
  gre->SetPoint(3,12,0.4536073);
  gre->SetPointError(3,12*0.08,0.05860495);//0.62
  gre->SetPoint(4,14.5,0.3694549);
  gre->SetPointError(4,14.5*0.08,0.0518269);//1.0
  gre->SetPoint(5,23,0.3521646);
  gre->SetPointError(5,23*0.08,0.06848064);//2.0
  gre->Draw("2 same");
  
  TGraphErrors* grestat = new TGraphErrors(6);
  grestat->SetName("Graph0stat");
  grestat->SetTitle("Graph0stat");
  grestat->SetLineColor(cimarker);
  grestat->SetMarkerColor(cimarker);
  grestat->SetMarkerStyle(29);
  grestat->SetMarkerSize(2);
  grestat->SetPoint(0,7.5,0.4664189);
  grestat->SetPointError(0,1,0.02632702);
  grestat->SetPoint(1,9,0.4856157);
  grestat->SetPointError(1,0.5,0.0353226);
  grestat->SetPoint(2,10.25,0.4065521);
  grestat->SetPointError(2,0.75,0.0288783);
  grestat->SetPoint(3,12,0.4536073);
  grestat->SetPointError(3,1,0.03347202);
  grestat->SetPoint(4,14.5,0.3694549);
  grestat->SetPointError(4,1.5,0.03358354);
  grestat->SetPoint(5,23,0.3521646);
  grestat->SetPointError(5,7,0.0311077);
  grestat->Draw("p same");
  
}
