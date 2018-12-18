using namespace std;
#include "../uti.h"

void ReadFile(TString infile="CUJET3_RAA-pT_0-10.dat",TString output="PredictionsCUJET3_pt_0_10.root")
{
  double a,b,c,d,e,f,g;
  FILE *fp=fopen(infile.Data(),"r");
  FILE *fp2=fopen(infile.Data(),"r");
  
  int counter=0;
  while(fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f,&g)!=EOF) 
    {
      counter++;
      //cout<<a<<endl;
    }
  const int size=counter;
  double pt[size],RAAcharged5[size],RAAD5[size],RAAB5[size],RAAcharged2[size],RAAD2[size],RAAB2[size];
  double RAAcharged[size],RAAD[size],RAAB[size],RAAchargedErr[size],RAADErr[size],RAABErr[size];
  double zero[size];
  double width[size];
  
  int counter2=0;
  while(fscanf(fp2,"%lf %lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f,&g)!=EOF) 
    {
      pt[counter2]=a;
      RAAcharged5[counter2]=b;
      RAAD5[counter2]=c;
      RAAB5[counter2]=d;
      RAAcharged2[counter2]=e;
      RAAD2[counter2]=f;
      RAAB2[counter2]=g;
      zero[counter2]=0.;
      width[counter2]=0.25;

      RAAcharged[counter2] = (RAAcharged5[counter2]+RAAcharged2[counter2])/2.;
      RAAchargedErr[counter2] = abs(RAAcharged5[counter2]-RAAcharged2[counter2])/2.;
      RAAD[counter2] = (RAAD5[counter2]+RAAD2[counter2])/2.;
      RAADErr[counter2] = abs(RAAD5[counter2]-RAAD2[counter2])/2.;
      RAAB[counter2] = (RAAB5[counter2]+RAAB2[counter2])/2.;
      RAABErr[counter2] = abs(RAAB5[counter2]-RAAB2[counter2])/2.;

    }
  
  fclose(fp);  
  
  
  TGraphAsymmErrors* gRAApion5TeV = new TGraphAsymmErrors(size,pt,RAAcharged5,width,width,zero,zero);
  gRAApion5TeV->SetName("gRAApion5TeV");
  gRAApion5TeV->SetMarkerStyle(20);
  gRAApion5TeV->SetMarkerSize(0.8);

  TGraphAsymmErrors* gRAADmeson5TeV = new TGraphAsymmErrors(size,pt,RAAD5,width,width,zero,zero);
  gRAADmeson5TeV->SetName("gRAADmeson5TeV");
  gRAADmeson5TeV->SetMarkerStyle(20);
  gRAADmeson5TeV->SetMarkerSize(0.8);

  TGraphAsymmErrors* gRAABmeson5TeV = new TGraphAsymmErrors(size,pt,RAAB5,width,width,zero,zero);
  gRAABmeson5TeV->SetName("gRAABmeson5TeV");
  gRAABmeson5TeV->SetMarkerStyle(20);
  gRAABmeson5TeV->SetMarkerSize(0.8);

  gRAApion5TeV->SetLineColor(1);
  gRAApion5TeV->SetMarkerColor(1);
  gRAADmeson5TeV->SetLineColor(2);
  gRAADmeson5TeV->SetMarkerColor(2);
  gRAABmeson5TeV->SetLineColor(4);
  gRAABmeson5TeV->SetMarkerColor(4);

    
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
  gRAApion5TeV->Draw("psame");
  gRAADmeson5TeV->Draw("psame");
  gRAABmeson5TeV->Draw("psame");
    
  TFile*foutput=new TFile(output.Data(),"recreate");
  foutput->cd();
  gRAApion5TeV->Write();
  gRAADmeson5TeV->Write();
  gRAABmeson5TeV->Write();
  foutput->Close();


  
}
