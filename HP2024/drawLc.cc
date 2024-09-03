#include <fstream>
#include <sstream>

#include "xjjrootuti.h"
#include "xjjmypdf.h"

#include "TH2F.h"

class line_to_graph {
public:
  line_to_graph(std::string line) {
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
    xjjroot::setthgrstyle(gsyst, kBlack, msyst, 2.3,
                          kBlack, 1, 1,
                          0, 0, 0);
    xjjroot::setthgrstyle(gstat, kBlack, mstat, 2.3,
                          kBlack, 1, 1);
  }
  TGraphAsymmErrors *gstat, *gsyst;
  void setcolor(int cc) {
    xjjroot::setthgrstyle(gsyst, cc, -1, -1,
                          cc, -1, -1);
                          // cc, 0.5, 1001);
  }
  // void setmarker(Style_t msyst, Style_t mstat) {
  //   gstat->SetMarkerStyle(mstat);
  //   gsyst->SetMarkerStyle(msyst);
  // }
  void draw() {
    gsyst->Draw("p5 same");
    gstat->Draw("pe same");
  }
};

int macro(std::string filename, xjjroot::mypdf* pdf, std::vector<int> vc) {
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
  for (int i=0; i<vc.size(); i++) {
    grs[i]->setcolor(vc[i]);
  }
  
  for (auto& g : grs) {
    g->draw();
  }
  
  return 0;
}

int main() {
  std::string inputfile = "dat/LcToD0_dNdeta_pT-4-6.dat";

  int r = xjjroot::mycolor_satmiddle["red"],
    g = xjjroot::mycolor_satmiddle["green"],
    b = xjjroot::mycolor_satmiddle["azure"];

  auto hempty = new TH2F("hempty", ";#langled#it{N}_{ch}/d#eta#rangle_{|#eta|<0.5};#Lambda_{c}^{+} / D^{0}", 10, 1, 5000, 10, 0, 1.5);
  xjjroot::sethempty(hempty, 0, -0.1);

  xjjroot::setgstyle();
  auto pdf = new xjjroot::mypdf("plots.pdf", "c", 800, 500);
  pdf->getc()->SetLogx();
  pdf->prepare();
  hempty->Draw("AXIS");

  macro(inputfile, pdf, {b, g, g, b, g, g, b, g, b, g, g, g, g, r, r});
  
  pdf->write();
  pdf->close();

  return 0;
}
