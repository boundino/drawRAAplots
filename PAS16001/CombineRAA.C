using namespace std;
#include "uti.h"
#include "ChargedHad/RAA_0_10.C"
#include "ChargedHad/RAA_0_100.C"
#include "systematics.C"

void CombineRAA(TString fileMB="ROOTfilesCent10/outputRAAMB.root", TString file="ROOTfilesCent10/outputRAA.root", Float_t centMin=0., Float_t centMax=10., Int_t isHadDupl=1, Int_t isTheoryComparison=2)
{
  gStyle->SetOptTitle(0);   
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  bool superimposedALICE=false;

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");

  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  
  TH1D* hTrackPt_trkCorr_PbPb_copy1 = new TH1D("hTrackPt_trkCorr_PbPb_copy1","",1,0,1);
  hTrackPt_trkCorr_PbPb_copy1->Sumw2();
  hTrackPt_trkCorr_PbPb_copy1->SetLineWidth(2);
  hTrackPt_trkCorr_PbPb_copy1->SetLineColor(kRed);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerStyle(20);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerSize(0.8); 
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerColor(kRed);
  
  TCanvas*canvasRAA=new TCanvas("canvasRAA","canvasRAA",600,600);//550,500
  canvasRAA->cd();
  canvasRAA->SetFillColor(0);
  canvasRAA->SetBorderMode(0);
  canvasRAA->SetBorderSize(2);
  canvasRAA->SetLeftMargin(0.185);//0.200
  canvasRAA->SetRightMargin(0.025);
  canvasRAA->SetTopMargin(0.080);
  canvasRAA->SetBottomMargin(0.150);
  canvasRAA->SetFrameBorderMode(0);
  canvasRAA->SetLogx();

  TH2F* hemptyEff;
  if(isHadDupl==1) hemptyEff=new TH2F("hemptyEff","",50,0.7,400.,10.,0,1.55); else hemptyEff=new TH2F("hemptyEff","",50,1.0,150.,10.,0,1.55);//50,-2,120.,10.,0,1.5
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("D^{0} R_{AA}");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(1.15);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.15);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(0.01);
  hemptyEff->SetMaximum(2);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();

  TLine *line;
  if(isHadDupl==1) line = new TLine(0.7,1,400,1); else line = new TLine(1.0,1,150,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  if(isHadDupl==1)
    {
      if(centMin==0&&centMax==100) RAA_0_100();
      else if(centMin==0&&centMax==10) RAA_0_10();
      else
        {
          cout<<"ERROR: Invalid Centrality range"<<endl;
        }
    }
  gNuclearModification->SetFillColor(5);//1
  gNuclearModification->SetFillStyle(3001);//0 
  gNuclearModification->SetLineWidth(1);//3
  gNuclearModification->SetMarkerSize(1);
  gNuclearModification->SetMarkerStyle(21);
  gNuclearModification->SetLineColor(1);//kGreen+4
  gNuclearModification->SetMarkerColor(1);//kGreen+4
  gNuclearModification->Draw("5same");
  gNuclearModificationMB->SetFillColor(5);//1
  gNuclearModificationMB->SetFillStyle(3001);//0 
  gNuclearModificationMB->SetLineWidth(1);//3
  gNuclearModificationMB->SetMarkerSize(1);
  gNuclearModificationMB->SetMarkerStyle(21);
  gNuclearModificationMB->SetLineColor(1);//kGreen+4
  gNuclearModificationMB->SetMarkerColor(1);//kGreen+4

  gNuclearModificationMB->Draw("5same");
  
  hNuclearModification->SetLineWidth(3);
  hNuclearModification->SetMarkerSize(1);
  hNuclearModification->SetMarkerStyle(21);
  hNuclearModification->SetLineColor(1);//kGreen+4
  hNuclearModification->SetMarkerColor(1);//kGreen+4

  hNuclearModification->Draw("psame");//same
  hNuclearModificationMB->SetLineWidth(3);
  hNuclearModificationMB->SetMarkerSize(1);
  hNuclearModificationMB->SetMarkerStyle(21);
  hNuclearModificationMB->SetLineColor(1);//kGreen+4
  hNuclearModificationMB->SetMarkerColor(1);//kGreen+4
  hNuclearModificationMB->Draw("psame");//same

  Float_t systnorm = normalizationUncertaintyForRAA(centMin,centMax)*1.e-2;
  TBox* bSystnorm;
  if(isHadDupl==1)  bSystnorm= new TBox(0.7,1-systnorm,0.9,1+systnorm);
  else bSystnorm= new TBox(1.0,1-systnorm,1.2,1+systnorm);
  bSystnorm->SetLineColor(16);
  bSystnorm->SetFillColor(16);
  bSystnorm->Draw();

  TLatex* texlumi = new TLatex(0.19,0.936,"25.8 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)");
  texlumi->SetNDC();
  //texlumi->SetTextAlign(31);
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  TLatex* texcms = new TLatex(0.22,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.22,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  TString texper="%";
  //TLatex * tlatexeff2=new TLatex(0.65,0.20,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  TLatex * tlatexeff2 = new TLatex(0.41,0.58,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextSize(0.045);
  tlatexeff2->SetLineWidth(2);
  tlatexeff2->Draw();
  TLatex * texY = new TLatex(0.41,0.53,"|y| < 1");//0.2612903,0.8425793
  texY->SetNDC();
  texY->SetTextColor(1);
  texY->SetTextFont(42);
  texY->SetTextSize(0.045);
  texY->SetLineWidth(2);
  texY->Draw();

  TLegend *legendSigma;
  if(isHadDupl==0 && isTheoryComparison==0) legendSigma=new TLegend(0.5436242,0.7474695,0.942953,0.8457592,"");//0.5100806,0.6268644,0.8084677,0.7805932
  if(isHadDupl==1 && isTheoryComparison==0) legendSigma=new TLegend(0.4436242,0.72,0.842953,0.88,"");//0.5100806,0.6268644,0.8084677,0.7805932
  if(isTheoryComparison==2||isTheoryComparison==3) legendSigma=new TLegend(0.5636242,0.6474695,0.912953,0.9057592,"");//0.5100806,0.6268644,0.8084677,0.7805932
  if(isHadDupl==0 && isTheoryComparison==1) legendSigma=new TLegend(0.5636242,0.6474695,0.912953,0.9057592,"");//0.5100806,0.6268644,0.8084677,0.7805932
  if(isHadDupl==1 && isTheoryComparison==1) legendSigma=new TLegend(0.5636242,0.6474695,0.912953,0.9057592,"");//0.5100806,0.6268644,0.8084677,0.7805932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(0);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.031);//0.05

  TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(gNuclearModification,"R_{AA} D^{0}","pf");
   ent_Dhighpt->SetTextFont(42);
   ent_Dhighpt->SetLineColor(4);
   ent_Dhighpt->SetMarkerColor(4);
   ent_Dhighpt->SetTextSize(0.043);//0.03
   if(isHadDupl==1 && isTheoryComparison==1){ent_Dhighpt->SetTextSize(0.03);}


   //if(isHadDupl==1&&isTheoryComparison==0){
    if(isHadDupl==1){
      TLegendEntry *ent_Charged=legendSigma->AddEntry(hTrackPt_trkCorr_PbPb_copy1,"R_{AA} charged hadrons","pl");//pf
       ent_Charged->SetTextFont(42);
       ent_Charged->SetLineColor(1);
       ent_Charged->SetMarkerColor(1);
       ent_Charged->SetTextSize(0.043);//0.03
      if(isHadDupl==1 && isTheoryComparison==1){ent_Charged->SetTextSize(0.03);}
    } 
   legendSigma->Draw();

  if(isTheoryComparison && centMin==0. && centMax==100.)
    {
      TGraph *gShanshanD5TeV = new TGraph("TheoryPredictions/Shanshan-D-RAA_PbPb5020_00-80.dat");
      gShanshanD5TeV->SetLineWidth(3);
      gShanshanD5TeV->SetLineColor(kRed+1);
      gShanshanD5TeV->Draw("c same");
      TGraph *gMagdalenaD5TeV = new TGraph("TheoryPredictions/Magdalena-5TeV-0100-plot2.txt");
      gMagdalenaD5TeV->SetLineColor(kGreen+4);
      gMagdalenaD5TeV->SetFillColor(kGreen+4);

      gMagdalenaD5TeV->SetFillStyle(3004);
      gMagdalenaD5TeV->Draw("f same");
      gMagdalenaD5TeV->Draw("l same");

      TLegendEntry *ent_theory_Shanshan =legendSigma->AddEntry(gShanshanD5TeV,"S. Cao et al. 0-80%","l");
      TLegendEntry *ent_theory_Magdalena =legendSigma->AddEntry(gMagdalenaD5TeV,"M. Djordjevic","bf");

    }
  if(isTheoryComparison && centMin==0. && centMax==10.)
    {
      TFile* filePredictions = new TFile("TheoryPredictions/PredictionsCUJET3_pt_0_10.root");  
      TGraphAsymmErrors* gRAApion5TeV = (TGraphAsymmErrors*)filePredictions->Get("gRAApion5TeV");
      TGraphAsymmErrors* gRAADmeson5TeV = (TGraphAsymmErrors*)filePredictions->Get("gRAADmeson5TeV");
      TGraphAsymmErrors* gRAABmeson5TeV = (TGraphAsymmErrors*)filePredictions->Get("gRAABmeson5TeV");
      TGraphErrors* gPHSDWOShadowing = new TGraphErrors("TheoryPredictions/phsd502TeVWoShadowing.txt");
      TGraphErrors* gPHSDWShadowing = new TGraphErrors("TheoryPredictions/phsd502TeVWShadowing.txt");
//      TGraph *gMagdalenaD5TeV = new TGraph("Magdalena-5TeV.txt");
      TGraph *gMagdalenaD5TeV = new TGraph("TheoryPredictions/Magdalena-5TeV-plot2.txt");
      TGraph *gShanshanD5TeV = new TGraph("TheoryPredictions/Shanshan-D-RAA_PbPb5020_00-10.dat");
      gRAApion5TeV->SetLineColor(kGreen+1);
      gRAApion5TeV->SetMarkerColor(kGreen+1);
      gRAApion5TeV->SetLineWidth(3);
      gRAApion5TeV->SetMarkerSize(0.15);
      gRAADmeson5TeV->SetLineColor(4);
      gRAADmeson5TeV->SetMarkerColor(4);
      gRAADmeson5TeV->SetLineWidth(3);
      gRAADmeson5TeV->SetMarkerSize(0.15);
      gMagdalenaD5TeV->SetLineColor(kGreen+4);
      gMagdalenaD5TeV->SetFillColor(kGreen+4);
      if (isTheoryComparison==1||isTheoryComparison==2){
      gMagdalenaD5TeV->SetFillStyle(3004);
      gMagdalenaD5TeV->Draw("f same");
      gMagdalenaD5TeV->Draw("l same");
      gRAADmeson5TeV->Draw("psame");

      }
      if (isTheoryComparison==1||isTheoryComparison==3){
      gPHSDWShadowing->SetLineColor(kGreen+2);
      gPHSDWShadowing->SetLineWidth(3);
      gPHSDWShadowing->Draw("c same");
      gPHSDWOShadowing->SetLineColor(kGreen+2);
      gPHSDWOShadowing->SetLineWidth(3);
      gPHSDWOShadowing->SetLineStyle(2);
      gPHSDWOShadowing->Draw("c same");
      gShanshanD5TeV->SetLineWidth(3);
      gShanshanD5TeV->SetLineColor(kRed+1);
      gShanshanD5TeV->Draw("c same");

      }
      //gRAApion5TeV->Draw("psame");
      

      if(superimposedALICE){
      double p9059_d9x1y1_xval[9] = { 1.5, 2.5, 3.5, 4.5, 5.5, 7.0, 10.0, 14.0, 20.0 };
      double p9059_d9x1y1_xerrminus[9] = { 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 2.0, 2.0, 4.0 };
      double p9059_d9x1y1_xerrplus[9] = { 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 2.0, 2.0, 4.0 };
      double p9059_d9x1y1_yval[9] = { 0.695, 0.694, 0.385, 0.245, 0.186, 0.153, 0.155, 0.174, 0.219 };
      double p9059_d9x1y1_yerrminus[9] = { 0.3686583784481237, 0.29960307074527787, 0.123664869708418, 0.07561084578286371, 0.05500909015790027, 0.042485291572496, 0.0442944691807002, 0.06788225099390856, 0.137800580550301 };
      double p9059_d9x1y1_yerrplus[9] = { 0.3318870289722092, 0.2141074496602115, 0.09546203433826454, 0.06264982043070834, 0.05060632371551998, 0.03982461550347976, 0.043416586692184816, 0.06859300255857008, 0.11045361017187261 };
      double p9059_d9x1y1_ystatminus9[] = { 0.21, 0.079, 0.037, 0.026, 0.025, 0.019, 0.021, 0.048, 0.058 };
      double p9059_d9x1y1_ystatplus[9] = { 0.21, 0.079, 0.037, 0.026, 0.025, 0.019, 0.021, 0.048, 0.058 };
      int p9059_d9x1y1_numpoints = 9;
      TGraphAsymmErrors *p9059_d9x1y1 = new TGraphAsymmErrors(p9059_d9x1y1_numpoints, p9059_d9x1y1_xval, p9059_d9x1y1_yval, p9059_d9x1y1_xerrminus, p9059_d9x1y1_xerrplus, p9059_d9x1y1_yerrminus, p9059_d9x1y1_yerrplus);
      p9059_d9x1y1->SetName("/HepData/9059/d9x1y1");
      p9059_d9x1y1->SetLineColor(2);
      p9059_d9x1y1->SetMarkerColor(2);  
      p9059_d9x1y1->SetLineWidth(4);  
      p9059_d9x1y1->SetTitle("/HepData/9059/d9x1y1");
      p9059_d9x1y1->Draw("psame");
      }


      if (isTheoryComparison==1||isTheoryComparison==2){
      TLegendEntry *ent_theory_Magdalena =legendSigma->AddEntry(gMagdalenaD5TeV,"M. Djordjevic","bf");
      TLegendEntry *ent_theoryD=legendSigma->AddEntry(gRAADmeson5TeV,"CUJET3.0 D^{0}","l");//pf
 //     ent_theoryD->SetTextFont(42);
      ent_theoryD->SetLineColor(4);  
      ent_theoryD->SetMarkerColor(4);
      }
  //    ent_theoryD->SetTextSize(0.043);//0.03
      
      //TLegendEntry *ent_theoryCharged=legendSigma->AddEntry(gRAApion5TeV,"CUJET3.0 #pi^{0}, h^{#pm}","l");//pf
      //ent_theoryCharged->SetTextFont(42);
      //ent_theoryCharged->SetLineColor(kGreen+1);
      //ent_theoryCharged->SetMarkerColor(kGreen+1);
      //ent_theoryCharged->SetTextSize(0.043);//0.03

      if (isTheoryComparison==1||isTheoryComparison==3){
      TLegendEntry *ent_theory_Shanshan =legendSigma->AddEntry(gShanshanD5TeV,"S. Cao et al.","l");
      TLegendEntry *ent_theory_PHSDW =legendSigma->AddEntry(gPHSDWShadowing,"PHSD w/ shadowing ","l");
      TLegendEntry *ent_theory_PHSDWO =legendSigma->AddEntry(gPHSDWOShadowing,"PHSD w/o shadowing ","l");
      }
    }
  
  if((isTheoryComparison==1||isTheoryComparison==2)&&centMax==10)
    {
      TGraph *R_PbPb_cen = new TGraph("TheoryPredictions/R-PbPb_cen_cron1.5_eloss1.5.5100GeVD0.txt");
      R_PbPb_cen->SetLineColor(kViolet);
      R_PbPb_cen->SetFillColor(kViolet);
      R_PbPb_cen->SetFillStyle(3011);
      R_PbPb_cen->Draw("f same");
      R_PbPb_cen->Draw("l same");
      TLegendEntry *ent_theory_R_PbPb_cen =legendSigma->AddEntry(R_PbPb_cen,"I.Vitev (g=1.8-2.0)","bf");
    }


  TLatex* texSystnorm = new TLatex(0.23,0.70,"T_{AA} and lumi.");
  texSystnorm->SetNDC();
  texSystnorm->SetTextColor(1);
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.04);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();
  texSystnorm = new TLatex(0.23,0.65,"uncertainty");
  texSystnorm->SetNDC();
  texSystnorm->SetTextColor(1);
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.04);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();
  canvasRAA->Update();
  canvasRAA->RedrawAxis();
    
  if(isHadDupl==0&&isTheoryComparison==0) canvasRAA->SaveAs(Form("plotRAA/canvasRAA_%.0f_%.0f.pdf",centMin,centMax));
  if(isHadDupl==1&&isTheoryComparison==0) canvasRAA->SaveAs(Form("plotRAA/canvasRAAchargedParticle_%.0f_%.0f.pdf",centMin,centMax));
  if(isTheoryComparison==1) canvasRAA->SaveAs(Form("plotRAA/canvasRAAComparisonAll_%.0f_%.0f.pdf",centMin,centMax));
  if(isTheoryComparison==2) canvasRAA->SaveAs(Form("plotRAA/canvasRAAComparisonQCD_%.0f_%.0f.pdf",centMin,centMax));
  if(isTheoryComparison==3) canvasRAA->SaveAs(Form("plotRAA/canvasRAAComparisonTransport_%.0f_%.0f.pdf",centMin,centMax));
  
}

int main(int argc, char *argv[])
{
  if(argc==7)
    {
      CombineRAA(argv[1], argv[2], atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]));
      return 0;
    }
  else
    { 
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}



