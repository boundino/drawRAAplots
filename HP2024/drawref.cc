#include <fstream>

#include "xjjrootuti.h"
#include "xjjanauti.h"
#include "xjjmypdf.h"

#include "TH1F.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

const int nbin = 13;
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
  horg = new TH1F(Form("horg_%s", key.c_str()), ";Publication;", 12*nbin-3, 0, 12*nbin-3);
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

      int bin = (atoi(year.c_str()) - (25-nbin))*12 + atoi(month.c_str()) - 1;
      if (bin < 0 || bin >= 12*nbin) continue;

      // if (bin==8) std::cout<<line<<std::endl;

      if (std::find(archives.begin(), archives.end(), arxiv) != archives.end()) continue;
      archives.push_back(arxiv);

      horg->Fill(bin);
    }

  get_rebin(ngroup);
  xjjroot::setthgrstyle(hint, cc_, 53, 1, cc_, 1, 3);
  xjjroot::setthgrstyle(h, cc_, 53, 1, cc_, 6, 3);
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
  hint->Draw("same p");
  hint->Draw("same l");
}

void key_to_graph::draw() {
  h->Draw("same p");
  h->Draw("same l");
}

std::map<std::string, key_to_graph*> gg;
std::map<std::string, std::string> labels {
                                           {"init", "Initial production"},
                                           {"npdf", "nPDF"},
                                           {"eloss", "Energy loss"},
                                           {"corr", "Correlation"},
                                           {"small", "Medium effect in small syst"},
                                           {"had", "Hadronization"},
                                           {"sub", "HF jet substructure"},
                                           {"qqbar", "Quarkonia"},
};
int draw_list(std::vector<std::string> list, TH2F* hempty, xjjroot::mypdf* pdf) {
  auto n = list.size();
  float x0 = 0.23, y0 = 0.82, dy = 0.033, ty0 = 0.89;
  auto leg = new TLegend(x0, y0-(dy+0.001)*n, x0+0.25, y0);
  xjjroot::setleg(leg, dy);
  for (auto& kk : list) {
    leg->AddEntry(gg[kk]->gethint(), labels[kk].c_str(), "pl");
  }

  //
  pdf->prepare();

  hempty->Draw("AXIS");
  leg->Draw();
  xjjroot::drawtex(0.56, ty0, "Open heavy flavors in heavy-ion collisions", 0.032, 22, 62);
  xjjroot::drawtex(0.56, ty0-dy, "Experimental results", 0.032, 22, 62);
  for (auto& kk : list) {
    gg[kk]->draw_int();
  }

  pdf->write("", "Q");
  return 0;
}

TH2F* make_hempty(float ymax) {
  auto hempty = new TH2F(Form("hempty%s", xjjc::currenttime().c_str()), ";;Publication", nbin, 0, 12*nbin, 10, 0, ymax);
  xjjroot::sethempty(hempty, 0.1, 0, 1.1, 0.8);
  hempty->GetXaxis()->SetLabelOffset(0.04);
  hempty->GetXaxis()->SetNdivisions(0-nbin);
  for (int i=0; i<nbin; i++) {
    hempty->GetXaxis()->SetBinLabel(i+1, Form("20%02d", 25-nbin+i));
    hempty->GetXaxis()->ChangeLabel(i+1, 90);
  }
  return hempty;
}

int main() {
  std::ifstream getdata("dat/HFref.csv");

  gg["init"] = new key_to_graph(getdata, "init", xjjroot::mycolor_satmiddle["orange"]);
  gg["npdf"] = new key_to_graph(getdata, "npdf", xjjroot::mycolor_satmiddle["yellow"]);
  gg["eloss"] = new key_to_graph(getdata, "eloss", xjjroot::mycolor_satmiddle["azure"]);
  gg["corr"] = new key_to_graph(getdata, "corr", xjjroot::mycolor_satmiddle["cyan"]);
  gg["small"] = new key_to_graph(getdata, "small", xjjroot::mycolor_satmiddle["olive"]);
  gg["had"] = new key_to_graph(getdata, "had", xjjroot::mycolor_satmiddle["red"]);
  gg["sub"] = new key_to_graph(getdata, "sub", xjjroot::mycolor_satmiddle["violet"]);
  gg["qqbar"] = new key_to_graph(getdata, "qqbar", xjjroot::mycolor_satmiddle["pink"]);

  auto hempty = make_hempty(61), hempty_qqbar = make_hempty(91);

  xjjroot::setgstyle();
  auto pdf = new xjjroot::mypdf("publication.pdf", "c", 600, 600);
  pdf->getc()->SetFrameLineWidth(0);

  draw_list({}, hempty, pdf);
  draw_list({"init", "npdf"}, hempty, pdf);
  draw_list({"init", "npdf", "eloss", "corr", "small"}, hempty, pdf);
  draw_list({"init", "npdf", "eloss", "corr", "small", "had"}, hempty, pdf);
  draw_list({"init", "npdf", "eloss", "corr", "small", "had", "sub"}, hempty, pdf);
  draw_list({"init", "npdf", "eloss", "corr", "small", "had", "sub", "qqbar"}, hempty_qqbar, pdf);

  pdf->close();

  return 0;
}

