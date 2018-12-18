#include <iostream>
#include <fstream>

void printout()
{
  std::ifstream getdata("datapoints.dat");
  double ax[] = {2., 3., 4., 5., 6., 7., 8., 10., 12., 20., 40., 60., 100.};
  const int nax = sizeof(ax)/sizeof(ax[0]) - 1;

  double axcenter[nax], ex[nax], ay[nax], eystat[nax], eysyst[nax];
  for(int i=0;i<nax;i++)
    {
      double temp;
      getdata>>temp>>ay[i]>>temp>>eystat[i]>>temp>>eysyst[i];
      axcenter[i] = (ax[i+1]+ax[i])/2;
      ex[i] = axcenter[i]*0.08;
      eystat[i] = eystat[i] - ay[i];
      eysyst[i] = eysyst[i] - ay[i];
    }
  std::cout<<"Double_t gNuclearModification_fx3002["<<nax<<"] = {";
  for(int i=0;i<nax;i++) { std::cout<<axcenter[i]<<(i==nax-1?"};":", "); }
  std::cout<<std::endl;
  std::cout<<"Double_t gNuclearModification_fy3002["<<nax<<"] = {";
  for(int i=0;i<nax;i++) { std::cout<<ay[i]<<(i==nax-1?"};":", "); }
  std::cout<<std::endl;
  std::cout<<"Double_t gNuclearModification_felx3002["<<nax<<"] = {";
  for(int i=0;i<nax;i++) { std::cout<<ex[i]<<(i==nax-1?"};":", "); }
  std::cout<<std::endl;
  std::cout<<"Double_t gNuclearModification_fehx3002["<<nax<<"] = {";
  for(int i=0;i<nax;i++) { std::cout<<ex[i]<<(i==nax-1?"};":", "); }
  std::cout<<std::endl;
  std::cout<<"Double_t gNuclearModification_fely3002["<<nax<<"] = {";
  for(int i=0;i<nax;i++) { std::cout<<eysyst[i]<<(i==nax-1?"};":", "); }
  std::cout<<std::endl;  
  std::cout<<"Double_t gNuclearModification_fehy3002["<<nax<<"] = {";
  for(int i=0;i<nax;i++) { std::cout<<eysyst[i]<<(i==nax-1?"};":", "); }
  std::cout<<std::endl;

  std::cout<<std::endl;
  for(int i=0;i<nax;i++) { std::cout<<"hNuclearModification2->SetBinContent("<<i+1<<","<<ay[i]<<");"<<std::endl; }
  for(int i=0;i<nax;i++) { std::cout<<"hNuclearModification2->SetBinError("<<i+1<<","<<eystat[i]<<");"<<std::endl; }
  std::cout<<std::endl;

}

int main()
{
  printout(); return 0;
}
