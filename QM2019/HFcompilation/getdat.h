#include "xjjrootuti.h"
#include <fstream>
#include <string>
#include <vector>
#include <TGraphErrors.h>

namespace exps
{
  class getdat
  {
  public:
    getdat(std::string filename, int color, std::string line1, std::string line2, Style_t mstyle, float xw=0.5, const char* opt="linear"); // linear, log
    void draw() { fgrsyst->Draw("2 same"); fgrstat->Draw("pe same"); }
    void setxw(float xw) { fxw = xw; for(int i=0;i<fn;i++) { fgrsyst->SetPointError(i, fxw, fysyst[i]); } }
    TGraphErrors* grsyst() { return fgrsyst; }
    TGraphErrors* grstat() { return fgrstat; }
    const char* line1() { return fline1.data(); }
    const char* line2() { return fline2.data(); }
  private:
    TGraphErrors *fgrstat, *fgrsyst;
    int fn, fcolor;
    float fxw;
    Style_t fmstyle;
    std::string fline1, fline2;
    std::string fopt;
  std::vector<float> fx, fxstat, fxsyst, fy, fystat, fysyst;
  };
}

exps::getdat::getdat(std::string filename, int color, std::string line1, std::string line2, Style_t mstyle, float xw, const char* opt) : 
  fcolor(color), 
  fmstyle(mstyle),
  fline1(line1),
  fline2(line2),
  fxw(xw),
  fopt(opt)
{
  std::ifstream getdata(filename.c_str());
  fn = 0;
  while(true)
    {
      float xx, yy, stat, syst, temp;
      getdata >> xx;
      if(getdata.eof()) break;
      getdata >> yy
              >> temp >> stat
              >> temp >> syst;
      fx.push_back(xx);
      fxstat.push_back(0);
      fxsyst.push_back(fxw);
      fy.push_back(yy);
      fystat.push_back(fabs(stat-yy));
      fysyst.push_back(fabs(syst-yy));
      fn++;
    }
  fgrstat = new TGraphErrors(fn, fx.data(), fy.data(), fxstat.data(), fystat.data());
  fgrstat->SetName(Form("grstat_%s", filename.c_str()));
  xjjroot::setthgrstyle(fgrstat, fcolor, fmstyle, 1.2, fcolor, 1, 2);
  fgrsyst = new TGraphErrors(fn, fx.data(), fy.data(), fxsyst.data(), fysyst.data());
  fgrsyst->SetName(Form("grsyst_%s", filename.c_str()));
  // xjjroot::setthgrstyle(fgrsyst, fcolor, fmstyle, 1.2, fcolor, 1, 2, fcolor, 0.3, 1001, 1);
  xjjroot::setthgrstyle(fgrsyst, fcolor, fmstyle, 1.2, fcolor, 1, 2, fcolor, 0.3, 1001, 0.1);
}
