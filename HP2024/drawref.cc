#include <fstream>

#include "xjjrootuti.h"
#include "xjjanauti.h"

#include "TH1F.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

class key_to_graph {
public:
  key_to_graph(std::ifstream& getdata, std::string key, int ngroup=1);
  void draw_int();
  
private:
  const int nbin = 11;
  TH1F *horg, *hint, *h;
  TGraphErrors *g, *gint;
  void integrate(TH1F* h);
  void get_rebin(int ngroup=1);
};


key_to_graph::key_to_graph(std::ifstream& getdata, std::string key, int ngroup) {

  h = new TH1F(Form("h_%s", key.c_str()), ";Publication;", 12*nbin, 0, 12*nbin);
  
  while(true)
    {
      std::string line = "";
      std::getline(getdata, line);
      if(line=="") break;
      if(line[0] == '#') continue;

      auto parse_line = xjjc::str_divide(line, ",");
      auto arxiv = parse_line[7];
      if (arxiv.length() < 4) continue;
      auto year = arxiv.substr(0, 2), month = arxiv.substr(2, 2);
      if (!xjjc::str_isinteger(year) || !xjjc::str_isinteger(month)) continue;
      auto keys = parse_line[11];
      if (!xjjc::str_contains(keys, key)) continue;

      int bin = (atoi(year.c_str()) - 14)*12 + atoi(month.c_str());
      if (bin < 0 || bin >= 12*nbin) continue;
      h->Fill(bin);
    }
  std::cout<<"test"<<std::endl;
  get_rebin(ngroup);
}

void key_to_graph::integrate(TH1F* hh) {
  hint = (TH1F*)hh->Clone("hint");
  float nnow = 0;
  for (int i=0; i<hh->GetNbinsX(); i++) {
    nnow += hh->GetBinContent(i+1);
    hint->SetBinContent(i+1, nnow);
  }
}

void key_to_graph::get_rebin(int ngroup) {
  h = (TH1F*)horg->Rebin(ngroup, "hrebin");
  integrate(h);
  g = xjjana::shifthistcenter(h, "g", -1);
  gint = xjjana::shifthistcenter(hint, "gint", -1);
}

void key_to_graph::draw_int() {
  xjjroot::setthgrstyle(hint, xjjroot::mycolor_satmiddle["azure"], 21, 1, xjjroot::mycolor_satmiddle["azure"], 1, 2);
  hint->Draw("same l");
}

int main() {
  std::ifstream getdata("dat/HFref.csv");
  // if(!getdata.is_open()) {
  //   std::cout<<"\e[31;1m error: invalid input file: \e[0m\e[41m"<<"dat/HFref.csv"<<"\e[0m"<<std::endl;
  //   return 1;
  // }
  
  auto g_had = new key_to_graph(getdata, "had");

  auto hempty = new TH2F("hempty", ";;Publication", 12*11, 0, 12*11, 10, 0, 40);
  xjjroot::sethempty(hempty, 0.1, -0.2);

  xjjroot::setgstyle();
  auto c = new TCanvas("c", "", 800, 600);
  c->SetFrameLineWidth(0);
  hempty->Draw("AXIS");

  g_had->draw_int();

  c->SaveAs("publication.pdf");

  return 0;
}

