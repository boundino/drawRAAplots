#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <TH1F.h>
#include <TFile.h>

namespace djt
{
  class theoryCCNU
  {
  public:
    theoryCCNU(std::string data) : fdata(data), nhist(0) { init(); }
    ~theoryCCNU() { ; }
    void draw(int opt, int iptbin, float tsize, float xx, float yy, float xxwidoff=0);
    void drawratiopp(int iptbin, TH1F* hdatapp, float tsize=0, float xx=0, float yy=0, float xxwidoff=0);
    // TH1F* gethpp(int iptbin) { return htheory[0*2+iptbin]; }
    // TH1F* gethPbPb(int iptbin) { return htheory[1*2+iptbin]; }
    // TH1F* gethratio(int iptbin) { return htheory[2*2+iptbin]; }

  private:
    std::string fdata;
    const std::vector<int> parse = {5, 5, 4, 4, 6}; // !!
    const int nparse = parse.size();
    std::vector<TH1F*> htheory;
    int nhist;
    std::vector<Color_t> colorlist = {kAzure-3, kRed-3, kOrange+7}; 
    void drawline(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Color_t lcolor=kBlack, Style_t lstyle=6, Width_t lwidth=6);
    void setleg(TLegend* leg, Float_t tsize=0.04);
    template<class T> void drawleg(T* h, float tsize, float xx, float yy, int opt, float xxwidoff=0, const char* legopt="l");
    void init();
    void sethistsytle();
  };
}

void djt::theoryCCNU::init()
{
  std::ifstream inf(fdata.c_str());
  std::string line; float xmaxnow;
  for(int p=0; p<nparse; p++)
    {
      int nn = parse[p], nh = nn-3;
      std::vector<std::vector<float>> yval(nh);
      std::vector<std::vector<float>> xval(nh);
      while(std::getline(inf, line)) 
        {
          if(line.empty() || line.length() <= 1) break;
          if(line.front() == '#') continue;

          std::istringstream ss(line);
          for(int j=0; j<nn; j++)
            { 
              float vv; ss >> vv;
              if(j==0) 
                {
                  for(int h=0; h<nh; h++) 
                    { xval[h].push_back(vv); }
                }
              if(j==1) xmaxnow = vv;
              if(j > 2)
                { yval[j-3].push_back(vv); }
            }
          line.clear();
        }
      for(int h=0; h<nh; h++)
        { 
          xval[h].push_back(xmaxnow); 
          htheory.push_back(new TH1F(Form("htheoryCCNU_%d", nhist), "", xval[h].size()-1, xval[h].data())); nhist++;
          for(int b=0; b<xval[h].size()-1; b++)
            { 
              htheory[nhist-1]->SetBinContent(b+1, yval[h][b]); 
              htheory[nhist-1]->SetBinError(b+1, 0); 
            }
        }
    }
  inf.close();

  sethistsytle();
}

template<class T>
void djt::theoryCCNU::drawleg(T* h, float tsize, float xx, float yy, int opt, float xxwidoff, const char* legopt)
{
  // if(legopt > htheory.size()+1 || legopt < 0) return;
  // float right = 0.65, left = 0.20;
  // std::vector<float> xx = {right,  right,  right, right, left, left, right,  right};
  // std::vector<float> yy = {0.10, 0.10+tsize+0.01, 0.40,  0.40+tsize+0.01,   0.70,  0.70,  0.20, 0.60};
  // std::vector<bool> supr = {false, false, false, false, true, true, false, false};
  std::vector<std::string> title = {"pp (SHERPA)", "PbPb", "CCNU"};  

  TLegend* leg = new TLegend(xx, yy, xx+tsize*5+xxwidoff, yy+tsize);
  setleg(leg, tsize);
  leg->AddEntry(h, std::string(""+title[opt]).c_str(), legopt);
  leg->Draw();
}

void djt::theoryCCNU::sethistsytle()
{
  int hh = 0;
  for(auto& pp : parse)
    {
      int nh = pp-3;
      for(int h=0; h<nh; h++)
        {
          htheory[hh]->SetFillStyle(0);
          htheory[hh]->SetLineStyle(6);
          htheory[hh]->SetLineWidth(6);
          htheory[hh]->SetLineColor(colorlist[h]);
          if(nh == 1) 
            {
              htheory[hh]->SetLineColor(colorlist[2]);
              htheory[hh]->SetMinimum(1);
            }
          hh++;
        }
    }
}

void djt::theoryCCNU::draw(int opt, int iptbin, float tsize, float xx, float yy, float xxwidoff)
{
  std::string drawopt[] = {"hist same", "hist same", "hist same"};
  if(opt <= 2)
    {
      int hh = -1;
      if(opt < 2) { hh = iptbin*2 + opt; }
      if(opt == 2) { hh = opt*2 + iptbin; }

      if(hh >= nhist || hh < 0) { std::cout<<__FUNCTION__<<": error: invalid [opt] [iptbin] "<<opt<<" "<<iptbin<<std::endl; return; }
      if(opt < 2) htheory[hh]->Draw(drawopt[opt].c_str());
      else 
        {
          float lasty = 1;
          for(int b=0; b<htheory[hh]->GetNbinsX(); b++)
            {
              drawline(htheory[hh]->GetBinCenter(b+1)-htheory[hh]->GetBinWidth(b+1)/2., htheory[hh]->GetBinContent(b+1), 
                       htheory[hh]->GetBinCenter(b+1)+htheory[hh]->GetBinWidth(b+1)/2., htheory[hh]->GetBinContent(b+1), colorlist[opt]);
              if(b) drawline(htheory[hh]->GetBinCenter(b+1)-htheory[hh]->GetBinWidth(b+1)/2., lasty, 
                             htheory[hh]->GetBinCenter(b+1)-htheory[hh]->GetBinWidth(b+1)/2., htheory[hh]->GetBinContent(b+1), colorlist[opt]);
              lasty = htheory[hh]->GetBinContent(b+1);
            }
        }
      drawleg(htheory[hh], tsize, xx, yy, opt, xxwidoff);
    }
}

void djt::theoryCCNU::drawratiopp(int iptbin, TH1F* hdatapp, float tsize, float xx, float yy, float xxwidoff)
{
  int opt = 0;
  int hh = iptbin*2;
  TH1F* hratio = (TH1F*)(htheory[hh]->Clone(Form("hratio-%d-%s", iptbin, hdatapp->GetName())));
  hratio->Divide(hdatapp);
  xjjroot::setthgrstyle(hratio, colorlist[opt], 20, 1.1, colorlist[opt], 1, 1);
  int nn = hratio->GetNbinsX();
  std::vector<float> vxx(nn), evxx(nn), vyy(nn), evyy(nn);
  float lasty = 1;
  for(int b=0; b<nn; b++)
    {
      float xbinl = hratio->GetBinCenter(b+1)-hratio->GetBinWidth(b+1)/2., xbinh = hratio->GetBinCenter(b+1)+hratio->GetBinWidth(b+1)/2.;
      float ybin = hratio->GetBinContent(b+1), eybin = ybin * djtsyst::getsyst(iptbin, b, "pp");
      xjjroot::drawbox(xbinl, ybin-eybin, xbinh, ybin+eybin, colorlist[opt], 0.3);
      drawline(xbinl, ybin, 
               xbinh, ybin, colorlist[opt]);
      if(b) drawline(xbinl, lasty, 
                     xbinl, ybin, colorlist[opt]);
      lasty = ybin;
      vxx[b] = hratio->GetBinCenter(b+1);
      evxx[b] =  hratio->GetBinCenter(b+1)-hratio->GetBinWidth(b+1)/2.;
      vyy[b] = hratio->GetBinContent(b+1);
      evyy[b] = eybin;
    }
  TGraphErrors* gsyst = new TGraphErrors(nn, vxx.data(), vyy.data(), evxx.data(), evyy.data());
  gsyst->SetName(Form("gsyst-%d-%s", iptbin, hdatapp->GetName()));
  // xjjroot::setthgrstyle(gsyst, colorlist[opt], 20, 1.1, colorlist[opt], 6, 6, colorlist[opt], 0.3, 1001);
  xjjroot::setthgrstyle(gsyst, colorlist[opt], 20, 1.1, 0, 0, 0, colorlist[opt], 0.3, 1001);
  hratio->Draw("pe same");
  // delete hratio;
  if(tsize)
    {
      drawleg(gsyst, tsize, xx, yy, opt, xxwidoff, "pf");
    }
}


void djt::theoryCCNU::drawline(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Color_t lcolor/*=kBlack*/, Style_t lstyle/*=6*/, Width_t lwidth/*=6*/)
{
  TLine* l = new TLine(x1, y1, x2, y2);
  l->SetLineColor(lcolor);
  l->SetLineStyle(lstyle);
  l->SetLineWidth(lwidth);
  l->Draw();
}

void djt::theoryCCNU::setleg(TLegend* leg, Float_t tsize/*=0.04*/)
{
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(tsize);
}
