#include "xjjrootuti.h"
#include "xjjcuti.h"
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
    hfdata(std::string filename, int color, std::string line1, std::string line2, Style_t mstyle); // filename is "input:opt"
    void draw(std::string opt="pf") { if(xjjc::str_contains(opt, "f")) { fgrsyst->Draw("5 same"); }
      if(xjjc::str_contains(opt, "p")) { fgrstat->Draw("pe same"); } }
    void setxw(float xw, bool logx);
    void setmarkersize(Size_t ms) { fgrstat->SetMarkerSize(ms); fgrsyst->SetMarkerSize(ms); }
    TGraphAsymmErrors* grsyst() { return fgrsyst; }
    TGraphAsymmErrors* grstat() { return fgrstat; }
    const char* line1() { return fline1.data(); }
    const char* line2() { return fline2.data(); }
    int n() { return fn; }
  private:
    std::string fopt;
    void makegr_manual(std::string filename);
    void makegr_hepdata(std::string filename);
    TGraphAsymmErrors *fgrstat, *fgrsyst;
    int fn, fcolor;
    float fxw;
    Style_t fmstyle;
    std::string fline1, fline2;
    std::vector<float> fx, fxstat, fxsyst, fy, fystatl, fystath, fysystl, fysysth;
    std::vector<Style_t> msmall = {27, 28, 33, 34, 44, 45, 46, 47, 48, 49};
    std::vector<Style_t> mmiddle = {20, 22, 23, 24, 26, 29, 30, 32};
    bool ismsmall() { return std::find(msmall.begin(), msmall.end(), fmstyle) != msmall.end(); }
    bool ismmiddle() { return std::find(mmiddle.begin(), mmiddle.end(), fmstyle) != mmiddle.end(); }
    bool fopt_xboundary;
    int fopt_moresyst;
  };
}

exps::hfdata::hfdata(std::string filename, int color, std::string line1, std::string line2, Style_t mstyle) :
  fcolor(color), 
  fmstyle(mstyle),
  fline1(line1),
  fline2(line2)
{
  fopt = "";
  auto pfile = xjjc::str_divide(filename, ":");
  filename = pfile[0];
  if(pfile.size() > 1) fopt = pfile[1];

  fxw = 0.1;

  // parse fopt
  fopt_xboundary = xjjc::str_contains(fopt, "B");
  size_t findS = fopt.find("S");
  if(findS == std::string::npos) fopt_moresyst = 0;
  else
    fopt_moresyst = atoi(std::string(1, fopt[fopt.find("S")+1]).c_str());

  std::cout<<"\e[32;1m <== "<<filename<<"\e[0m"<<std::endl;
  if(xjjc::str_contains(filename, ".csv")) 
    makegr_hepdata(filename);
  else makegr_manual(filename);

  Size_t msize = 1.3;
  if(ismmiddle()) msize = 1.4;
  if(ismsmall()) msize = 1.6;

  xjjroot::setthgrstyle(fgrstat, fcolor, fmstyle, msize, fcolor, 1, 2);
  xjjroot::setthgrstyle(fgrsyst, fcolor, fmstyle, msize, fcolor, 1, 2, fcolor, 0.4, 1001, 0.6);
}

void exps::hfdata::makegr_hepdata(std::string filename)
{
  std::ifstream getdata(filename.c_str());
  if(!getdata.is_open()) 
    std::cout<<"\e[31;1m error: invalid input file.\e[0m"<<std::endl;
  fn = 0;
  while(true)
    {
      std::string line = "";
      std::getline(getdata, line);
      if(line=="") break;
      if(line[0] == '#') continue;

      std::istringstream iss(line);
      float xx, yy, statl, stath, systl, systh, temp;
      iss >> xx;
      if(fopt_xboundary)
        iss >> temp >> temp;
      iss >> yy 
          >> stath >> statl
          >> systh >> systl;
      for(int s = 0; s < fopt_moresyst; s++)
        iss >> temp;

      if(stath < 0) std::swap(statl, stath);
      if(systh < 0) std::swap(systl, systh);
      
      fx.push_back(xx);
      fxstat.push_back(0);
      fxsyst.push_back(fxw);
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
  if(!getdata.is_open()) 
    std::cout<<"\e[31;1m error: invalid input file.\e[0m"<<std::endl;
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
      if(systl > systh) std::swap(systl, systh);
      fx.push_back(xx);
      fxstat.push_back(0);
      fxsyst.push_back(fxw);
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

void exps::hfdata::setxw(float xw, bool logx)
{
  fxw = xw;
  for(int i=0;i<fn;i++)
    {
      double thisxw = logx?(fxw*fx[i]):fxw;
      fgrsyst->SetPointError(i, thisxw, thisxw, fysystl[i], fysysth[i]);
    }
}
