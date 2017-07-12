TGraphErrors* gre;
TGraphErrors* gre2;

Int_t cifillJ;

void expBeautyCMS()
{
//=========Macro generated from canvas: c2/c2
//=========  (Wed Feb  1 19:16:45 2017) by ROOT version5.34/36

  Int_t cimarker = kRed+2;//kGray+3
  Int_t cifill = kRed-9;//kGray+2

  cifillJ = cifill;

  Double_t bin_3_syst_fx3011[3] = {
    3.75,
    5,
    6};
  Double_t bin_3_syst_fy3011[3] = {
    0.7389477,
    0.6345531,
    0.5167278};
  Double_t bin_3_syst_felx3011[3] = {
    3.75*0.08,
    5*0.08,
    6*0.08};
  Double_t bin_3_syst_fely3011[3] = {
    0.2613933,
    0.1109919,
    0.05985485};
  gre2 = new TGraphErrors(3,bin_3_syst_fx3011,bin_3_syst_fy3011,bin_3_syst_felx3011,bin_3_syst_fely3011);
  gre2->SetName("Graph1");
  gre2->SetTitle("Graph1");
  gre2->SetFillColor(cifill);
  gre2->SetFillColorAlpha(cifill, 0.5);
  gre2->SetMarkerColor(cimarker);
  gre2->SetMarkerStyle(34);
  gre2->SetMarkerSize(1.7);
  gre2->SetLineColor(0);

  gre2->Draw("2 same");
  
  Double_t bin_3_fx3012[3] = {
    3.75,
    5,
    6};
  Double_t bin_3_fy3012[3] = {
    0.7389477,
    0.6345531,
    0.5167278};
  Double_t bin_3_felx3012[3] = {
    0.75,
    0.5,
    0.5};
  Double_t bin_3_fely3012[3] = {
    0.0634266,
    0.04242643,
    0.0343517};
  TGraphErrors* gre2stat = new TGraphErrors(3,bin_3_fx3012,bin_3_fy3012,bin_3_felx3012,bin_3_fely3012);
  gre2stat->SetName("Graph1stat");
  gre2stat->SetTitle("Graph1stat");
  gre2stat->SetMarkerColor(cimarker);
  gre2stat->SetLineColor(cimarker);
  gre2stat->SetMarkerStyle(34);
  gre2stat->SetMarkerSize(1.7);

  gre2stat->Draw("p same");
  
  Double_t bin_0_syst_fx3013[12] = {
    7,
    8,
    9,
    10.25,
    12,
    14,
    16.25,
    18.75,
    22.5,
    27.5,
    32.5,
    42.5};
  Double_t bin_0_syst_fy3013[12] = {
    0.5205617,
    0.4780894,
    0.4616475,
    0.4371907,
    0.4263492,
    0.4585017,
    0.4234693,
    0.4502758,
    0.4407601,
    0.4666347,
    0.6018213,
    0.473903};
  Double_t bin_0_syst_felx3013[12] = {
    7*0.08,
    8*0.08,
    9*0.08,
    10.25*0.08,
    12*0.08,
    14*0.08,
    16.25*0.08,
    18.75*0.08,
    22.5*0.08,
    27.5*0.08,
    32.5*0.08,
    42.5*0.08};
  Double_t bin_0_syst_fely3013[12] = {
    0.05704963,
    0.03986511,
    0.03372379,
    0.02713588,
    0.02404351,
    0.02512273,
    0.02306843,
    0.02731351,
    0.02398772,
    0.02865439,
    0.05034567,
    0.04050557};
  gre = new TGraphErrors(12,bin_0_syst_fx3013,bin_0_syst_fy3013,bin_0_syst_felx3013,bin_0_syst_fely3013);
  gre->SetName("Graph0");
  gre->SetTitle("Graph0");
  
  gre->SetFillColor(cifill);
  gre->SetFillColorAlpha(cifill, 0.5);
  gre->SetMarkerColor(cimarker);
  gre->SetMarkerStyle(29);
  gre->SetMarkerSize(2);
  gre->SetLineColor(0);

  gre->Draw("2 same");
  
  Double_t bin_0_fx3014[12] = {
    7,
    8,
    9,
    10.25,
    12,
    14,
    16.25,
    18.75,
    22.5,
    27.5,
    32.5,
    42.5};
  Double_t bin_0_fy3014[12] = {
    0.5205617,
    0.4780894,
    0.4616475,
    0.4371907,
    0.4263492,
    0.4585017,
    0.4234693,
    0.4502758,
    0.4407601,
    0.4666347,
    0.6018213,
    0.473903};
  Double_t bin_0_felx3014[12] = {
    0.5,
    0.5,
    0.5,
    0.75,
    1,
    1,
    1.25,
    1.25,
    2.5,
    2.5,
    2.5,
    7.5};
  Double_t bin_0_fely3014[12] = {
    0.01781202,
    0.01397327,
    0.01285977,
    0.0107817,
    0.01086009,
    0.01418445,
    0.01554696,
    0.02139503,
    0.02221882,
    0.03530909,
    0.06675377,
    0.06164125};

  TGraphErrors* grestat = new TGraphErrors(12,bin_0_fx3014,bin_0_fy3014,bin_0_felx3014,bin_0_fely3014);
  grestat->SetName("Graph0stat");
  grestat->SetTitle("Graph0stat");
  grestat->SetLineColor(cimarker);
  grestat->SetMarkerColor(cimarker);
  grestat->SetMarkerStyle(29);
  grestat->SetMarkerSize(2);

  grestat->Draw("p same");
  
}
