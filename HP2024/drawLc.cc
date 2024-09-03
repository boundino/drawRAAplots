#include <fstream>
#include <sstream>

#include "xjjrootuti.h"
#include "xjjmypdf.h"

#include "TH2F.h"

class line_to_graph {
public:
  line_to_graph(std::string line) : cc_(0) {
    std::istringstream iss(line);
    float xx[1], yy[1],
      xstat[1] = {0}, statl[1], stath[1],
      xsyst[1], systl[1], systh[1];
    Size_t msyst, mstat;
    iss >> xx[0] >> yy[0] >> stath[0] >> statl[0] >> systh[0] >> systl[0]
        >> msyst >> mstat;
    xsyst[0] = xx[0] * 0.1;
    gstat = new TGraphAsymmErrors(1, xx, yy, xstat, xstat, statl, stath);
    gsyst = new TGraphAsymmErrors(1, xx, yy, xsyst, xsyst, systl, systh);
    xjjroot::setthgrstyle(gsyst, kBlack, msyst, 2.2,
                          kBlack, 1, 1,
                          0, 0, 0);
    xjjroot::setthgrstyle(gstat, kBlack, mstat, 2.2,
                          kBlack, 1, 1);
  }
  TGraphAsymmErrors *gstat, *gsyst;
  void setcolor(int cc) {
    xjjroot::setthgrstyle(gsyst, cc, -1, -1,
                          cc, -1, -1);
    // cc, 0.5, 1001);
    cc_ = cc;
  }
  int getcolor() { return cc_; }
  // void setmarker(Style_t msyst, Style_t mstat) {
  //   gstat->SetMarkerStyle(mstat);
  //   gsyst->SetMarkerStyle(msyst);
  // }
  void draw() {
    gsyst->Draw("p5 same");
    gstat->Draw("pe same");
  }
private:
  int cc_;
};

std::vector<TGraphAsymmErrors*> macro(std::string filename, xjjroot::mypdf* pdf, std::vector<int> vc={},
                                      std::vector<int> vleg={}) {
  std::ifstream getdata(filename.c_str());
  if(!getdata.is_open())
    std::cout<<"\e[31;1m error: invalid input file: \e[0m\e[41m"<<filename<<"\e[0m"<<std::endl;
  std::vector<line_to_graph*> grs;
  while(true)
    {
      std::string line = "";
      std::getline(getdata, line);
      if(line=="") break;
      if(line[0] == '#') continue;

      auto ltg = new line_to_graph(line);
      grs.push_back(ltg);
    }
  for (int i=0; i<grs.size(); i++) {
    if (i >= vc.size()) {
      grs[i]->setcolor(0);
      continue;
    }
    grs[i]->setcolor(vc[i]);
  }

  if (pdf) {
    for (auto& g : grs)
      if (g->getcolor())
        g->draw();
  }

  std::vector<TGraphAsymmErrors*> grs_leg;
  for (auto& i : vleg) {
    auto gleg = (TGraphAsymmErrors*)grs[i]->gstat->Clone(Form("gleg%d", i));
    grs_leg.push_back(gleg);
  }
  return grs_leg;
}

TH2F* hempty;
TLegend *leg1, *leg2;
float l1x = 0.24, ly = 0.80, l2x = 0.48, dlx = 0.015;

void drawframe() {
  hempty->Draw("AXIS");
  xjjroot::drawline(1, 0.11, 5, 0.11, kBlack, 6, 2);
  leg1->Draw();
  xjjroot::drawtex(l1x+dlx, ly+0.02+0.045, "ALICE, V0M", 0.038, 11);
  xjjroot::drawtex(l1x+dlx, ly+0.02, "4 < p_{T} < 6 GeV", 0.038, 11);
  leg2->Draw();
  xjjroot::drawtex(l2x+dlx, ly+0.02+0.045, "CMS, Ntrk + private ext.", 0.038, 11);
  xjjroot::drawtex(l2x+dlx, ly+0.02, "3 < p_{T} < 5 GeV", 0.038, 11);
}

int main() {
  std::string inputfile = "dat/LcToD0_dNdeta_pT-4-6.dat";

  int pp = xjjroot::mycolor_satmiddle["yellow"],
    pa1 = xjjroot::mycolor_satmiddle["cyan"],
    pa2 = xjjroot::mycolor_satmiddle["azure"],
    aa = xjjroot::mycolor_satmiddle["red"],
    r = xjjroot::mycolor_satmiddle["red"],
    b = xjjroot::mycolor_satmiddle["azure"],
    w = 16;

  hempty = new TH2F("hempty", ";#it{N}_{ch}/d#eta_{|#eta|<0.5};#Lambda_{c}^{#pm} / D^{0}", 10, 1, 5000, 10, 0, 1.3);
  xjjroot::sethempty(hempty, 0.1, -0.2);

  auto grleg = macro(inputfile, 0, {}, {0, 3, 12, 4});
  leg1 = new TLegend(l1x, ly-0.045*3, l1x+0.2, ly);
  xjjroot::setleg(leg1, 0.038);
  leg1->AddEntry(grleg[0], "pp 13 TeV", "p"); 
  leg1->AddEntry(grleg[1], "pPb 5.02 TeV", "p"); 
  leg1->AddEntry(grleg[2], "PbPb 5.02 TeV", "p"); 
  leg2 = new TLegend(l2x, ly-0.045*3, l2x+0.2, ly);
  xjjroot::setleg(leg2, 0.038);
  leg2->AddEntry((TObject*)0, "", NULL); 
  leg2->AddEntry(grleg[3], "pPb 8.16 TeV", "p"); 
  leg2->AddEntry((TObject*)0, "", NULL); 
 
  xjjroot::setgstyle();
  auto pdf = new xjjroot::mypdf("plots.pdf", "c", 800, 600);
  pdf->getc()->SetLogx();
  pdf->getc()->SetFrameLineWidth(0);
  //
  pdf->prepare();
  drawframe();
  macro(inputfile, pdf, {pp, pp, pp, // pp,
                         pa1, pa2, pa1, pa2, pa2, pa1, pa2, pa2, pa2,
                         aa, aa});
  pdf->write();

  //
  pdf->prepare();
  drawframe();
  macro(inputfile, pdf, {b, w, r, // pp,
                         0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0});
  pdf->write();
  //
  pdf->prepare();
  drawframe();
  macro(inputfile, pdf, {w, w, w, // pp,
                         b, w, w, w, w, w, w, w, r,
                         0, 0});
  pdf->write();
  //
  pdf->prepare();
  drawframe();
  macro(inputfile, pdf, {w, w, w, // pp,
                         w, w, w, w, w, w, w, w, b,
                         r, 0});
  pdf->write();
  //
  pdf->prepare();
  drawframe();
  macro(inputfile, pdf, {w, w, w, // pp,
                         w, w, w, w, w, w, w, w, w,
                         b, r});
  pdf->write();

  
  pdf->close();

  return 0;
}
