#include <fstream>

#include "xjjrootuti.h"
#include "xjjanauti.h"

#include "TH1F.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

const int nbin = 12;
class key_to_graph {
public:
  key_to_graph(std::ifstream& getdata, std::string key, int cc=1, int ngroup=1);
  void draw_int();
  void draw();
  TGraphErrors* getgint() { return gint; }
  TH1F* gethint() { return hint; }
  
private:
  int cc_;
  TH1F *horg, *hint, *h;
  TGraphErrors *g, *gint;
  void integrate(TH1F* h);
  void get_rebin(int ngroup=1);
};


key_to_graph::key_to_graph(std::ifstream& getdata, std::string key, int cc, int ngroup) : cc_(cc) {

  std::vector<std::string> archives;
  horg = new TH1F(Form("horg_%s", key.c_str()), ";Publication;", 12*nbin, 0, 12*nbin);
  getdata.clear();
  getdata.seekg(0);
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

      int bin = (atoi(year.c_str()) - (25-nbin))*12 + atoi(month.c_str());
      if (bin < 0 || bin >= 12*nbin) continue;

      if (std::find(archives.begin(), archives.end(), arxiv) != archives.end()) continue;
      archives.push_back(arxiv);

      horg->Fill(bin);
    }

  get_rebin(ngroup);
  xjjroot::setthgrstyle(hint, cc_, 21, 1, cc_, 1, 2);
  xjjroot::setthgrstyle(h, cc_, 21, 1, cc_, 6, 2);
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
  hint->Draw("same l");
}

void key_to_graph::draw() {
  h->Draw("same l");
}

int main() {
  std::ifstream getdata("dat/HFref.csv");
  // if(!getdata.is_open()) {
  //   std::cout<<"\e[31;1m error: invalid input file: \e[0m\e[41m"<<"dat/HFref.csv"<<"\e[0m"<<std::endl;
  //   return 1;
  // }
  
  auto g_had = new key_to_graph(getdata, "had", xjjroot::mycolor_satmiddle["red"]);
  auto g_eloss = new key_to_graph(getdata, "eloss", xjjroot::mycolor_satmiddle["azure"]);
  auto g_corr = new key_to_graph(getdata, "corr", xjjroot::mycolor_satmiddle["cyan"]);
  auto g_npdf = new key_to_graph(getdata, "npdf", xjjroot::mycolor_satmiddle["yellow"]);
  auto g_qqbar = new key_to_graph(getdata, "qqbar", xjjroot::mycolor_satmiddle["green"]);

  auto leg = new TLegend(0.25, 0.8-0.045*4, 0.25+0.25, 0.80);
  xjjroot::setleg(leg, 0.038);
  leg->AddEntry(g_had->gethint(), "Hadronization", "l");
  leg->AddEntry(g_eloss->gethint(), "Energy loss", "l");
  leg->AddEntry(g_corr->gethint(), "Correlation", "l");
  leg->AddEntry(g_npdf->gethint(), "nPDF", "l");
 
  auto hempty = new TH2F("hempty", ";;Publication", nbin, 0, 12*nbin, 10, 0, 58);
  xjjroot::sethempty(hempty, 0.1, 0, 1.1, 0.8);
  hempty->GetXaxis()->SetLabelOffset(0.04);
  hempty->GetXaxis()->SetNdivisions(0-nbin);
  for (int i=0; i<nbin; i++) {
    hempty->GetXaxis()->SetBinLabel(i+1, Form("20%d", 25-nbin+i));
    hempty->GetXaxis()->ChangeLabel(i+1, 90);
  }

  xjjroot::setgstyle();
  auto c = new TCanvas("c", "", 600, 600);
  c->SetFrameLineWidth(0);
  hempty->Draw("AXIS");
  leg->Draw();
  xjjroot::drawtex(0.55, 0.88, "Open heavy flavor experimental publication", 0.035, 22);

  g_eloss->draw_int();
  g_corr->draw_int();
  g_npdf->draw_int();
  // g_qqbar->draw_int();
  g_had->draw_int();

  
  c->SaveAs("publication.pdf");

  return 0;
}

