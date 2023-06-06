#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <TH1F.h>
#include <TGraphErrors.h>

class projection
{
public:
  projection(std::string input, float xw = -1, bool logx = false);
  TH1F *hstat;
  TGraphErrors *gsyst;
  std::vector<float> ax, axmin, axmax, axe, ay, aystat, aysyst;
  int n;
private:
  std::string input_;
};

projection::projection(std::string input, float xw, bool logx) :
  input_(input)
{
  std::ifstream getdata(input_.c_str());

  while(true)
    {
      std::string line = "";
      std::getline(getdata, line);
      if(line=="") break;
      if(line[0] == '#') continue;

      std::istringstream iss(line);
      float xx, xmin, xmax, yy, statl, stath, systl=0, systh=0, temp;
      iss >> xx >> xmin >> xmax;
      if(xmax < xmin) std::swap(xmin, xmax);
      iss >> yy >> stath >> statl;
      if(stath < statl) std::swap(statl, stath);
      iss >> systh >> systl;
      if(systh < systl) std::swap(systl, systh);

      float xe = (xmax - xmin)/2.,
        xes = logx?xx*xw:xw;
      ax.push_back(xx);
      axe.push_back((xw>=0?xes:xe));
      axmin.push_back(xmin);
      axmax.push_back(xmax);
      ay.push_back(yy);
      aystat.push_back(fabs(stath));
      aysyst.push_back(fabs(systh));
    }
  n = ax.size();
  axmin.push_back(axmax[n-1]);

  hstat = new TH1F(Form("hstat_%s", input_.c_str()), "", n, axmin.data());
  for(int i=0; i<n; i++)
    {
      hstat->SetBinContent(i+1, ay[i]);
      hstat->SetBinError(i+1, aystat[i]);
    }
  gsyst = new TGraphErrors(n, ax.data(), ay.data(), axe.data(), aysyst.data());
  gsyst->SetName(Form("gsyst_%s", input_.c_str()));
}

namespace project
{
  void scale(TH1F* h_after, TGraphErrors* g_after,
             float wlumi_MB, float wlumi_Trigger, float threshold,
             float minsyst)
  {
    for(int i=0; i<h_after->GetXaxis()->GetNbins(); i++)
      {
        float weight = h_after->GetBinCenter(i+1)<threshold?wlumi_MB:wlumi_Trigger;
        h_after->SetBinError(i+1, h_after->GetBinError(i+1) / weight);
        float syst = std::max((float)g_after->GetErrorY(i) / weight, (float)h_after->GetBinContent(i+1)*minsyst);
        g_after->SetPointError(i, g_after->GetErrorX(i), syst);
      }
  }
}
