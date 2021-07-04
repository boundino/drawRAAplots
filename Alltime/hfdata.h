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
    int fopt_nsyst;
    std::vector<int> fopt_iremovesyst;
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
  std::string topt(fopt);
  // fopt --> B
  fopt_xboundary = xjjc::str_contains(topt, "B");
  topt = xjjc::str_replaceall(topt, "B", "");
  // fopt --> Sx
  size_t findSx = topt.find("Sx");
  if(findSx != std::string::npos)
    {
      while(findSx < topt.length())
        {
          if(!isdigit(topt[findSx+2])) break;
          fopt_iremovesyst.push_back(atoi(std::string(1, topt[findSx+2]).c_str())-1);
          topt.erase(findSx+2, 1);
        }
    }
  topt = xjjc::str_replaceall(topt, "Sx", "");
  // fopt --> S
  fopt_nsyst = 1;
  size_t findS = topt.find("S");
  if(findS != std::string::npos)
    fopt_nsyst = atoi(std::string(1, topt[findS+1]).c_str());
  topt = xjjc::str_replaceall(topt, "S", "");

  std::cout<<"\e[32;2m <== "<<filename<<"\e[0m"<<std::endl;
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
    std::cout<<"\e[31;1m error: invalid input file: \e[0m\e[41m"<<filename<<"\e[0m"<<std::endl;
  fn = 0;
  while(true)
    {
      std::string line = "";
      std::getline(getdata, line);
      if(line=="") break;
      if(line[0] == '#') continue;

      std::istringstream iss(line);
      float xx, yy, statl, stath, systl=0, systh=0, temp;
      iss >> xx;
      if(fopt_xboundary)
        iss >> temp >> temp;
      iss >> yy 
          >> stath >> statl;
      if(stath < statl) std::swap(statl, stath);

      for(int s = 0; s < fopt_nsyst; s++)
        {
          std::string tsh, tsl; float sh, sl;
          iss  >> tsh >> tsl;
          if(tsh.back() == '%') 
            sh = atof(xjjc::str_replaceall(tsh, "%", "").c_str()) / 100. * yy;
          else
            sh = atof(tsh.c_str());
          if(tsl.back() == '%') 
            sl = atof(xjjc::str_replaceall(tsl, "%", "").c_str()) / 100. * yy;
          else
            sl = atof(tsl.c_str());
          if(sh < sl) std::swap(systl, systh);
          if(std::find(fopt_iremovesyst.begin(), fopt_iremovesyst.end(), s) == fopt_iremovesyst.end())
            {
              systl += sl*sl;
              systh += sh*sh;
            }
        }
      systl = std::sqrt(systl);
      systh = std::sqrt(systh);
      
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
    std::cout<<"\e[31;1m error: invalid input file: \e[0m"<<filename<<std::endl;
  fn = 0;
  while(true)
    {
      float xx, yy, stat, systl=0, systh=0, temp;
      getdata >> xx;
      if(getdata.eof()) break;
      if(fopt_xboundary)
        getdata >> temp >> temp;
      getdata >> yy >> temp;
      if(fopt_xboundary)
        getdata >> temp >> temp;
      getdata >> stat;
      stat = fabs(stat-yy);
      for(int s = 0; s < fopt_nsyst; s++)
        {
          float sh, sl;
          getdata >> temp;
          if(fopt_xboundary)
            getdata >> temp >> temp;
          getdata >> sl >> temp;
          if(fopt_xboundary)
            getdata >> temp >> temp;
          getdata >> sh;
          if(sl > sh) std::swap(sl, sh);
          if(std::find(fopt_iremovesyst.begin(), fopt_iremovesyst.end(), s) == fopt_iremovesyst.end())
            {
              systl += fabs(sl-yy)*fabs(sl-yy);
              systh += fabs(sh-yy)*fabs(sh-yy);
            }
        }
      systl = std::sqrt(systl);
      systh = std::sqrt(systh);

      fx.push_back(xx);
      fxstat.push_back(0);
      fxsyst.push_back(fxw);
      fy.push_back(yy);
      fystatl.push_back(stat);
      fystath.push_back(stat);
      fysystl.push_back(systl);
      fysysth.push_back(systh);
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
