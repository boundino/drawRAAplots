void canvasRAA_cent_0_10()
{
//=========Macro generated from canvas: canvasRAA/canvasRAA
//=========  (Mon Aug 21 16:54:48 2017) by ROOT version6.02/13
   TCanvas *canvasRAA = new TCanvas("canvasRAA", "canvasRAA",0,0,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   canvasRAA->SetHighLightColor(2);
   canvasRAA->Range(-0.509591,-0.3409091,2.244955,1.931818);
   canvasRAA->SetFillColor(0);
   canvasRAA->SetBorderMode(0);
   canvasRAA->SetBorderSize(2);
   canvasRAA->SetLogx();
   canvasRAA->SetLeftMargin(0.185);
   canvasRAA->SetRightMargin(0.025);
   canvasRAA->SetTopMargin(0.08);
   canvasRAA->SetBottomMargin(0.15);
   canvasRAA->SetFrameBorderMode(0);
   canvasRAA->SetFrameBorderMode(0);
   
   TH2F *hemptyRAA1 = new TH2F("hemptyRAA1","",50,1,150,10,0,1.75);
   hemptyRAA1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hemptyRAA1->SetLineColor(ci);
   hemptyRAA1->SetMarkerStyle(20);
   hemptyRAA1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hemptyRAA1->GetXaxis()->CenterTitle(true);
   hemptyRAA1->GetXaxis()->SetLabelFont(42);
   hemptyRAA1->GetXaxis()->SetLabelOffset(0);
   hemptyRAA1->GetXaxis()->SetLabelSize(0.045);
   hemptyRAA1->GetXaxis()->SetTitleSize(0.06);
   hemptyRAA1->GetXaxis()->SetTitleOffset(1.1);
   hemptyRAA1->GetXaxis()->SetTitleFont(42);
   hemptyRAA1->GetYaxis()->SetTitle("R_{AA}");
   hemptyRAA1->GetYaxis()->CenterTitle(true);
   hemptyRAA1->GetYaxis()->SetLabelFont(42);
   hemptyRAA1->GetYaxis()->SetLabelSize(0.045);
   hemptyRAA1->GetYaxis()->SetTitleSize(0.06);
   hemptyRAA1->GetYaxis()->SetTitleOffset(1.15);
   hemptyRAA1->GetYaxis()->SetTitleFont(42);
   hemptyRAA1->GetZaxis()->SetLabelFont(42);
   hemptyRAA1->GetZaxis()->SetLabelSize(0.035);
   hemptyRAA1->GetZaxis()->SetTitleSize(0.035);
   hemptyRAA1->GetZaxis()->SetTitleFont(42);
   hemptyRAA1->Draw("");
   TLine *line = new TLine(1,1,150,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   
   Double_t gNuclearModification_fx3001[5] = {
   22.5,
   27.5,
   35,
   50,
   80};
   Double_t gNuclearModification_fy3001[5] = {
   0.3453176,
   0.5039139,
   0.469913,
   0.6665264,
   0.6822249};
   Double_t gNuclearModification_felx3001[5] = {
   2.5,
   2.5,
   5,
   10,
   20};
   Double_t gNuclearModification_fely3001[5] = {
   0.07136701,
   0.1039691,
   0.09920814,
   0.1314584,
   0.1688335};
   Double_t gNuclearModification_fehx3001[5] = {
   2.5,
   2.5,
   5,
   10,
   20};
   Double_t gNuclearModification_fehy3001[5] = {
   0.07136701,
   0.1039691,
   0.09920814,
   0.1314584,
   0.1688335};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,gNuclearModification_fx3001,gNuclearModification_fy3001,gNuclearModification_felx3001,gNuclearModification_fehx3001,gNuclearModification_fely3001,gNuclearModification_fehy3001);
   grae->SetName("gNuclearModification");
   grae->SetTitle("Graph");

   ci = 924;
   color = new TColor(ci, 0.6, 1, 0.6, " ", 0.7);
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#006600");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_gNuclearModification3001 = new TH1F("Graph_gNuclearModification3001","Graph",100,12,108);
   Graph_gNuclearModification3001->SetMinimum(0.2162398);
   Graph_gNuclearModification3001->SetMaximum(0.9087692);
   Graph_gNuclearModification3001->SetDirectory(0);
   Graph_gNuclearModification3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNuclearModification3001->SetLineColor(ci);
   Graph_gNuclearModification3001->SetMarkerStyle(20);
   Graph_gNuclearModification3001->GetXaxis()->SetLabelFont(42);
   Graph_gNuclearModification3001->GetXaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3001->GetXaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3001->GetXaxis()->SetTitleFont(42);
   Graph_gNuclearModification3001->GetYaxis()->SetLabelFont(42);
   Graph_gNuclearModification3001->GetYaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3001->GetYaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3001->GetYaxis()->SetTitleFont(42);
   Graph_gNuclearModification3001->GetZaxis()->SetLabelFont(42);
   Graph_gNuclearModification3001->GetZaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3001->GetZaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gNuclearModification3001);
   
   grae->Draw("5");
   
   Double_t gNuclearModification_fx3002[9] = {
   2.5,
   3.5,
   4.5,
   5.5,
   7,
   9,
   11.25,
   13.75,
   17.5};
   Double_t gNuclearModification_fy3002[9] = {
   0.7613258,
   0.6088896,
   0.3374833,
   0.1668411,
   0.1796246,
   0.175019,
   0.2192556,
   0.2246581,
   0.2634928};
   Double_t gNuclearModification_felx3002[9] = {
   0.5,
   0.5,
   0.5,
   0.5,
   1,
   1,
   1.25,
   1.25,
   2.5};
   Double_t gNuclearModification_fely3002[9] = {
   0.1834239,
   0.1256258,
   0.06710301,
   0.03284859,
   0.03465358,
   0.03506534,
   0.04191744,
   0.04295087,
   0.05947879};
   Double_t gNuclearModification_fehx3002[9] = {
   0.5,
   0.5,
   0.5,
   0.5,
   1,
   1,
   1.25,
   1.25,
   2.5};
   Double_t gNuclearModification_fehy3002[9] = {
   0.1834239,
   0.1256258,
   0.06710301,
   0.03284859,
   0.03465358,
   0.03506534,
   0.04191744,
   0.04295087,
   0.05947879};
   grae = new TGraphAsymmErrors(9,gNuclearModification_fx3002,gNuclearModification_fy3002,gNuclearModification_felx3002,gNuclearModification_fehx3002,gNuclearModification_fely3002,gNuclearModification_fehy3002);
   grae->SetName("gNuclearModification");
   grae->SetTitle("Graph");

   ci = 925;
   color = new TColor(ci, 0.6, 1, 0.6, " ", 0.7);
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#006600");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_gNuclearModification3002 = new TH1F("Graph_gNuclearModification3002","Graph",100,0.2,21.8);
   Graph_gNuclearModification3002->SetMinimum(0.05291682);
   Graph_gNuclearModification3002->SetMaximum(1.025825);
   Graph_gNuclearModification3002->SetDirectory(0);
   Graph_gNuclearModification3002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNuclearModification3002->SetLineColor(ci);
   Graph_gNuclearModification3002->SetMarkerStyle(20);
   Graph_gNuclearModification3002->GetXaxis()->SetLabelFont(42);
   Graph_gNuclearModification3002->GetXaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3002->GetXaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3002->GetXaxis()->SetTitleFont(42);
   Graph_gNuclearModification3002->GetYaxis()->SetLabelFont(42);
   Graph_gNuclearModification3002->GetYaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3002->GetYaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3002->GetYaxis()->SetTitleFont(42);
   Graph_gNuclearModification3002->GetZaxis()->SetLabelFont(42);
   Graph_gNuclearModification3002->GetZaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3002->GetZaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gNuclearModification3002);
   
   grae->Draw("5");
   TBox *box = new TBox(1,0.9572332,1.2,1.035917);
   box->SetFillColor(16);
   box->SetLineColor(16);
   box->Draw();
   Double_t xAxis1[6] = {20, 25, 30, 40, 60, 100}; 
   
   TH1D *hNuclearModification2 = new TH1D("hNuclearModification2","",5, xAxis1);
   hNuclearModification2->SetBinContent(1,0.3453176);
   hNuclearModification2->SetBinContent(2,0.5039139);
   hNuclearModification2->SetBinContent(3,0.469913);
   hNuclearModification2->SetBinContent(4,0.6665264);
   hNuclearModification2->SetBinContent(5,0.6822249);
   hNuclearModification2->SetBinError(1,0.05165208);
   hNuclearModification2->SetBinError(2,0.06051077);
   hNuclearModification2->SetBinError(3,0.05437967);
   hNuclearModification2->SetBinError(4,0.04949815);
   hNuclearModification2->SetBinError(5,0.07886204);
   hNuclearModification2->SetEntries(396.3965);
   hNuclearModification2->SetLineWidth(3);

   ci = TColor::GetColor("#006600");
   hNuclearModification2->SetMarkerColor(ci);
   hNuclearModification2->SetMarkerStyle(21);
   hNuclearModification2->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
   hNuclearModification2->GetXaxis()->SetLabelFont(42);
   hNuclearModification2->GetXaxis()->SetLabelSize(0.035);
   hNuclearModification2->GetXaxis()->SetTitleSize(0.035);
   hNuclearModification2->GetXaxis()->SetTitleFont(42);
   hNuclearModification2->GetYaxis()->SetTitle("Uncorrected dN(D^{0})/dp_{T}");
   hNuclearModification2->GetYaxis()->SetLabelFont(42);
   hNuclearModification2->GetYaxis()->SetLabelSize(0.035);
   hNuclearModification2->GetYaxis()->SetTitleSize(0.035);
   hNuclearModification2->GetYaxis()->SetTitleFont(42);
   hNuclearModification2->GetZaxis()->SetLabelFont(42);
   hNuclearModification2->GetZaxis()->SetLabelSize(0.035);
   hNuclearModification2->GetZaxis()->SetTitleSize(0.035);
   hNuclearModification2->GetZaxis()->SetTitleFont(42);
   hNuclearModification2->Draw("psame");
   Double_t xAxis2[10] = {2, 3, 4, 5, 6, 8, 10, 12.5, 15, 20}; 
   
   TH1D *hNuclearModification3 = new TH1D("hNuclearModification3","",9, xAxis2);
   hNuclearModification3->SetBinContent(1,0.7613258);
   hNuclearModification3->SetBinContent(2,0.6088896);
   hNuclearModification3->SetBinContent(3,0.3374833);
   hNuclearModification3->SetBinContent(4,0.1668411);
   hNuclearModification3->SetBinContent(5,0.1796246);
   hNuclearModification3->SetBinContent(6,0.175019);
   hNuclearModification3->SetBinContent(7,0.2192556);
   hNuclearModification3->SetBinContent(8,0.2246581);
   hNuclearModification3->SetBinContent(9,0.2634928);
   hNuclearModification3->SetBinError(1,0.1612207);
   hNuclearModification3->SetBinError(2,0.09220124);
   hNuclearModification3->SetBinError(3,0.03483479);
   hNuclearModification3->SetBinError(4,0.02012718);
   hNuclearModification3->SetBinError(5,0.0181541);
   hNuclearModification3->SetBinError(6,0.01447137);
   hNuclearModification3->SetBinError(7,0.01991343);
   hNuclearModification3->SetBinError(8,0.02353607);
   hNuclearModification3->SetBinError(9,0.03073991);
   hNuclearModification3->SetEntries(223.7202);
   hNuclearModification3->SetLineWidth(3);

   ci = TColor::GetColor("#006600");
   hNuclearModification3->SetMarkerColor(ci);
   hNuclearModification3->SetMarkerStyle(21);
   hNuclearModification3->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
   hNuclearModification3->GetXaxis()->SetLabelFont(42);
   hNuclearModification3->GetXaxis()->SetLabelSize(0.035);
   hNuclearModification3->GetXaxis()->SetTitleSize(0.035);
   hNuclearModification3->GetXaxis()->SetTitleFont(42);
   hNuclearModification3->GetYaxis()->SetTitle("Uncorrected dN(D^{0})/dp_{T}");
   hNuclearModification3->GetYaxis()->SetLabelFont(42);
   hNuclearModification3->GetYaxis()->SetLabelSize(0.035);
   hNuclearModification3->GetYaxis()->SetTitleSize(0.035);
   hNuclearModification3->GetYaxis()->SetTitleFont(42);
   hNuclearModification3->GetZaxis()->SetLabelFont(42);
   hNuclearModification3->GetZaxis()->SetLabelSize(0.035);
   hNuclearModification3->GetZaxis()->SetTitleSize(0.035);
   hNuclearModification3->GetZaxis()->SetTitleFont(42);
   hNuclearModification3->Draw("psame");
   TLatex *   tex = new TLatex(0.96,0.936,"27.4 pb^{-1} (5.02 TeV pp) + 530 #mub^{-1} (5.02 TeV PbPb)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.22,0.89,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextSize(0.062);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.22,0.84,"D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextSize(0.062);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.95,0.27,"|y| < 1");
tex->SetNDC();
   tex->SetTextAlign(32);
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.955,0.22,"Cent. 0-10%");
tex->SetNDC();
   tex->SetTextAlign(32);
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.654,0.8,1.073,0.89,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.043);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("gNuclearModification","R_{AA}","pf");

   ci = 924;
   color = new TColor(ci, 0.6, 1, 0.6, " ", 0.7);
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#006600");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
      tex = new TLatex(0.23,0.64,"T_{AA} and lumi.");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.23,0.6,"uncertainty");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TH2F *hemptyRAA_copy4 = new TH2F("hemptyRAA_copy4","",50,1,150,10,0,1.75);
   hemptyRAA_copy4->SetDirectory(0);
   hemptyRAA_copy4->SetStats(0);

   ci = TColor::GetColor("#000099");
   hemptyRAA_copy4->SetLineColor(ci);
   hemptyRAA_copy4->SetMarkerStyle(20);
   hemptyRAA_copy4->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hemptyRAA_copy4->GetXaxis()->CenterTitle(true);
   hemptyRAA_copy4->GetXaxis()->SetLabelFont(42);
   hemptyRAA_copy4->GetXaxis()->SetLabelOffset(0);
   hemptyRAA_copy4->GetXaxis()->SetLabelSize(0.045);
   hemptyRAA_copy4->GetXaxis()->SetTitleSize(0.06);
   hemptyRAA_copy4->GetXaxis()->SetTitleOffset(1.1);
   hemptyRAA_copy4->GetXaxis()->SetTitleFont(42);
   hemptyRAA_copy4->GetYaxis()->SetTitle("R_{AA}");
   hemptyRAA_copy4->GetYaxis()->CenterTitle(true);
   hemptyRAA_copy4->GetYaxis()->SetLabelFont(42);
   hemptyRAA_copy4->GetYaxis()->SetLabelSize(0.045);
   hemptyRAA_copy4->GetYaxis()->SetTitleSize(0.06);
   hemptyRAA_copy4->GetYaxis()->SetTitleOffset(1.15);
   hemptyRAA_copy4->GetYaxis()->SetTitleFont(42);
   hemptyRAA_copy4->GetZaxis()->SetLabelFont(42);
   hemptyRAA_copy4->GetZaxis()->SetLabelSize(0.035);
   hemptyRAA_copy4->GetZaxis()->SetTitleSize(0.035);
   hemptyRAA_copy4->GetZaxis()->SetTitleFont(42);
   hemptyRAA_copy4->Draw("sameaxis");
   canvasRAA->Modified();
   canvasRAA->cd();
   canvasRAA->SetSelected(canvasRAA);
}
