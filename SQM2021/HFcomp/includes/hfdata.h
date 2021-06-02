#include "xjjrootuti.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <TGraphAsymmErrors.h>

namespace exps
{
  class hfdata
  {
  public:
    hfdata(std::string filename, int color, std::string line1, std::string line2, Style_t mstyle, float xw=0.5, const char* opt="linear"); // linear, log
    void draw(std::string opt="pf") { if(xjjc::str_contains(opt, "f")) { fgrsyst->Draw("5 same"); }
      if(xjjc::str_contains(opt, "p")) { fgrstat->Draw("pe same"); } }
    void setxw(float xw);
    void setmarkersize(Size_t ms) { fgrstat->SetMarkerSize(ms); fgrsyst->SetMarkerSize(ms); }
    TGraphAsymmErrors* grsyst() { return fgrsyst; }
    TGraphAsymmErrors* grstat() { return fgrstat; }
    const char* line1() { return fline1.data(); }
    const char* line2() { return fline2.data(); }
  private:
    void makegr_manual(std::string filename);
    void makegr_hepdata(std::string filename);
    TGraphAsymmErrors *fgrstat, *fgrsyst;
    int fn, fcolor;
    float fxw;
    Style_t fmstyle;
    bool flinear;
    std::string fline1, fline2;
    std::string fopt;
    std::vector<float> fx, fxstat, fxsyst, fy, fystatl, fystath, fysystl, fysysth;
  };
}

exps::hfdata::hfdata(std::string filename, int color, std::string line1, std::string line2, Style_t mstyle, float xw, const char* opt) : 
  fcolor(color), 
  fmstyle(mstyle),
  fline1(line1),
  fline2(line2),
  fxw(xw),
  fopt(opt)
{
  flinear = (fopt=="linear");

  if(xjjc::str_contains(filename, ".csv")) makegr_hepdata(filename);
  else makegr_manual(filename);

  xjjroot::setthgrstyle(fgrstat, fcolor, fmstyle, 1.4, fcolor, 1, 2);
  xjjroot::setthgrstyle(fgrsyst, fcolor, fmstyle, 1.4, fcolor, 1, 2, fcolor, 0.4, 1001, 0.6);
}

void exps::hfdata::makegr_hepdata(std::string filename)
{
  std::cout<<filename<<std::endl;

  std::ifstream getdata(filename.c_str());
  fn = 0;
  while(true)
    {
      std::string line = "";
      std::getline(getdata, line);
      if(line=="") break;
      if(line[0] == '#') continue;

      std::istringstream iss(line);
      float xx, yy, statl, stath, systl, systh, temp;
      iss >> xx >> yy
          >> stath >> statl
          >> systh >> systl;

      if(stath < 0) std::swap(statl, stath);
      if(systh < 0) std::swap(systl, systh);
      std::cout<<xx<<" "<<yy<<" "<<stath<<" "<<statl<<" "<<systh<<" "<<systl<<std::endl;
      
      fx.push_back(xx);
      fxstat.push_back(0);
      fxsyst.push_back(flinear?fxw:(fxw*xx));
      fy.push_back(yy);
      fystatl.push_back(fabs(statl));
      fystath.push_back(fabs(stath));
      fysystl.push_back(fabs(systl));
      fysysth.push_back(fabs(systh));
      fn++;
    }
  fgrstat = new TGraphAsymmErrors(fn, fx.data(), fy.data(), fxstat.data(), fxstat.data(), fystatl.data(), fystath.data());
  fgrstat->SetName(Form("grstat_%s", filename.c_str()));
  fgrsyst = new TGraphAsymmErrors(fn, fx.data(), fy.data(), fxsyst.data(), fxsyst.data(), fysystl.data(), fysysth.data());
  fgrsyst->SetName(Form("grsyst_%s", filename.c_str()));
}

void exps::hfdata::makegr_manual(std::string filename)
{
  std::ifstream getdata(filename.c_str());
  fn = 0;
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
      fxsyst.push_back(flinear?fxw:(fxw*xx));
      fy.push_back(yy);
      fystatl.push_back(fabs(stat-yy));
      fystath.push_back(fabs(stat-yy));
      fysystl.push_back(fabs(systl-yy));
      fysysth.push_back(fabs(systh-yy));
      fn++;
    }
  fgrstat = new TGraphAsymmErrors(fn, fx.data(), fy.data(), fxstat.data(), fxstat.data(), fystatl.data(), fystath.data());
  fgrstat->SetName(Form("grstat_%s", filename.c_str()));
  fgrsyst = new TGraphAsymmErrors(fn, fx.data(), fy.data(), fxsyst.data(), fxsyst.data(), fysystl.data(), fysysth.data());
  fgrsyst->SetName(Form("grsyst_%s", filename.c_str()));
}

void exps::hfdata::setxw(float xw)
{
  fxw = xw;
  for(int i=0;i<fn;i++)
    {
      double thisxw = flinear?fxw:(fxw*fx[i]);
      fgrsyst->SetPointError(i, thisxw, thisxw, fysystl[i], fysysth[i]);
    }
}
