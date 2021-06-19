#include "xjjrootuti.h"
#include <fstream>
#include <string>
#include <vector>
#include <TGraphAsymmErrors.h>

namespace exps
{
  class getdat
  {
  public:
    getdat(std::string filename, int color, std::string line1, std::string line2, Style_t mstyle, float xw=0.5, const char* opt="linear"); // linear, log
    void draw(std::string opt="pf") { if(xjjc::str_contains(opt, "f")) { fgrsyst->Draw("5 same"); }
      if(xjjc::str_contains(opt, "p")) { fgrstat->Draw("pe same"); } }
    void setxw(float xw);
    void setmarkersize(Size_t ms) { fgrstat->SetMarkerSize(ms); fgrsyst->SetMarkerSize(ms); }
    TGraphAsymmErrors* grsyst() { return fgrsyst; }
    TGraphAsymmErrors* grstat() { return fgrstat; }
    const char* line1() { return fline1.data(); }
    const char* line2() { return fline2.data(); }
  private:
    TGraphAsymmErrors *fgrstat, *fgrsyst;
    int fn, fcolor;
    float fxw;
    Style_t fmstyle;
    std::string fline1, fline2;
    std::string fopt;
    std::vector<float> fx, fxstat, fxsyst, fy, fystat, fysystl, fysysth;
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
  bool linear = (fopt=="linear");
  while(true)
    {
      float xx, yy, stat, systl, systh, temp;
      getdata >> xx;
      if(getdata.eof()) break;
      getdata >> yy
              >> temp >> stat
              >> temp >> systl
      >> temp >> systh;
      fx.push_back(xx);
      fxstat.push_back(0);
      fxsyst.push_back(linear?fxw:(fxw*xx));
      fy.push_back(yy);
      fystat.push_back(fabs(stat-yy));
      fysystl.push_back(fabs(systl-yy));
      fysysth.push_back(fabs(systh-yy));
      fn++;
    }
  fgrstat = new TGraphAsymmErrors(fn, fx.data(), fy.data(), fxstat.data(), fxstat.data(), fystat.data(), fystat.data());
  fgrstat->SetName(Form("grstat_%s", filename.c_str()));
  xjjroot::setthgrstyle(fgrstat, fcolor, fmstyle, 1.5, fcolor, 1, 2);
  fgrsyst = new TGraphAsymmErrors(fn, fx.data(), fy.data(), fxsyst.data(), fxsyst.data(), fysystl.data(), fysysth.data());
  fgrsyst->SetName(Form("grsyst_%s", filename.c_str()));
  // xjjroot::setthgrstyle(fgrsyst, fcolor, fmstyle, 1.2, fcolor, 1, 2, fcolor, 0.3, 1001, 1);
  xjjroot::setthgrstyle(fgrsyst, fcolor, fmstyle, 1.5, fcolor, 1, 1, fcolor, 0.4, 1001, 0.6);
}

void exps::getdat::setxw(float xw)
{
  fxw = xw;
  for(int i=0;i<fn;i++)
    {
      double thisxw = fopt=="linear"?fxw:(fxw*fx[i]);
      fgrsyst->SetPointError(i, thisxw, thisxw, fysystl[i], fysysth[i]);
    }
}
