using namespace std;
#include "../uti.h"

void readCUJETnew(TString infile, TString output)
{
  double temp;
  ifstream countlines(infile.Data());
  int counter=0;
  while(!countlines.eof()) 
    {
      countlines>>temp>>temp>>temp;
      counter++;
    }
  //cout<<counter<<endl;
  countlines.close();
  countlines.clear();
  ifstream getdata(infile.Data());

  const int size = counter;
  double pt[size],RAAhigh[size],RAAlow[size],RAA[size],RAAerr[size];
  double zero[size];
  double width[size];
  
  for(int i=0;i<size;i++)
    {
      getdata>>pt[i]>>RAAhigh[i]>>RAAlow[i];
      RAA[i] = (RAAhigh[i]+RAAlow[i])/2.;
      RAAerr[i] = (RAAhigh[i]-RAAlow[i])/2.;
      width[i]=0.5;
    }
  getdata.close();
    
  TGraphAsymmErrors* gRAADmeson5TeV = new TGraphAsymmErrors(size,pt,RAA,width,width,RAAerr,RAAerr);
  gRAADmeson5TeV->SetName("gRAADmeson5TeV");
  //gRAADmeson5TeV->SetMarkerStyle(20);
  //gRAADmeson5TeV->SetMarkerSize(0.8);
  //gRAADmeson5TeV->SetLineColor(2);
  //gRAADmeson5TeV->SetMarkerColor(2);
  gRAADmeson5TeV->SetFillColor(2);

    
  TCanvas* canvas = new TCanvas("canvas","",600,600);
  canvas->cd();
  TH2F* hempty=new TH2F("hempty","",50,0,110,10,0.,1);
  hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hempty->GetYaxis()->CenterTitle();
  hempty->GetYaxis()->SetTitle("R_{AA}");
  hempty->GetXaxis()->SetTitleOffset(1.1);
  hempty->GetYaxis()->SetTitleOffset(1.3);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.05);
  hempty->GetYaxis()->SetLabelSize(0.05);  
  hempty->Draw();
  gRAADmeson5TeV->Draw("3 same");
    
  TFile* foutput=new TFile(output.Data(),"recreate");
  foutput->cd();
  //gRAApion5TeV->Write();
  gRAADmeson5TeV->Write();
  //gRAABmeson5TeV->Write();
  foutput->Close();

  
}
