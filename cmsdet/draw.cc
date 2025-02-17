#include "xjjrootuti.h"

#include <TCanvas.h>
#include <TH2F.h>

#include <map>

struct det {
  std::string name;
  float order;
  float accept_min;
  float accept_max;
  int cc;
  float alpha;

  det(std::string _name, float _order, float _accept_min, float _accept_max, int _cc, float _alpha = 1) :
    name(_name), order(_order), accept_min(_accept_min), accept_max(_accept_max), cc(_cc), alpha(_alpha) {}
};

bool name_in_vec(std::vector<det>& dets, std::string name) {
  for (const auto& d : dets) {
    if (d.name == name) return true;
  }
  return false;
}

void draw_det_name(det& d, int cc) {
  float tsize = 0.065;
  if (d.name == "HGCAL") {
    xjjroot::drawtexnum(d.accept_max - tsize*0.5, d.order+0.5, "HG", tsize, 32, 42, kWhite);
    xjjroot::drawtexnum(d.accept_max + tsize*0.5, d.order+0.5, "CAL", tsize, 12, 42, kBlack);
    xjjroot::drawtexnum(- d.accept_max - tsize*0.5, d.order+0.5, "HGC", tsize, 32, 42, kBlack);
    xjjroot::drawtexnum(- d.accept_max + tsize*0.5, d.order+0.5, "AL", tsize, 12, 42, kWhite);
  }
  else {
    if (d.accept_min > 0) {
      xjjroot::drawtexnum((d.accept_min+d.accept_max)/2., d.order+0.5, d.name.c_str(), tsize, 22, 42, cc);
      xjjroot::drawtexnum(-(d.accept_min+d.accept_max)/2., d.order+0.5, d.name.c_str(), tsize, 22, 42, cc);
    } else {
      xjjroot::drawtexnum(0, d.order+0.5, d.name.c_str(), tsize, 22, 42, cc);
    }
  }
}

// const float xmin = 0.01, xmax = M_PI/2.-0.01;
const float xmin = -11, xmax = 11;

int macro() {
  std::vector<det> dets;
  dets.push_back( det( "Muon", 5., 0., 2.4, kGray, 0.4 ) );
  dets.push_back( det( "HCAL", 4, 0, 5.2, kGray, 0.6 ) ); // EH 1.5-3, HF 3-5.2
  dets.push_back( det( "ZDC", 4, 8.3, xmax, kGray, 0.6) );
  dets.push_back( det( "ECAL", 3, 0, 3, kGray, 0.8 ) );
  dets.push_back( det( "Tracking", 2, 0, 2.4, kGray, 1 ) );

  auto h = new TH2F("h", ";#eta;", 10, xmin, xmax, 10, 0, 6);
  xjjroot::sethempty(h, -0.4);
  h->GetYaxis()->SetNdivisions(0);
  h->GetYaxis()->SetAxisColor(0, 0);
  h->GetXaxis()->SetNdivisions(112);
  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleSize(0.1);

  std::vector<det> dets_up;
  auto cc_up = TColor::GetColor("#006EB8");
  dets_up.push_back( det("", 5., 2.4, 2.8, cc_up) ); // muon
  dets_up.push_back( det("HGCAL", 4, 1.5, 3., cc_up) ); // EH 1.5-3, HF 3-5.2
  dets_up.push_back( det("ZDC", 4, 8.3, xmax, cc_up) );  
  dets_up.push_back( det("MTD", 1, 0, 3, cc_up) );
  dets_up.push_back( det("PPS", 2, 9., xmax, cc_up) );
  dets_up.push_back( det("", 2, 2.4, 4, cc_up) ); // tracking
  // auto f = new TF1("f","0.5*atan(exp(x))", xmin, xmax);
  // auto ax = new TGaxis(xmin, 1, xmax, 1, "f");
  // ax->SetLabelSize(0.03);

  xjjroot::setgstyle();
  gStyle->SetPadLeftMargin(xjjroot::margin_pad_right);
  gStyle->SetPadBottomMargin(xjjroot::margin_pad_bottom * 1.5);
  
  auto c = new TCanvas("c", "", 800, 450);
  c->SetFrameLineWidth(0);
  h->Draw("AXIS");
  for (auto& d : dets) {
    xjjroot::drawbox(0-d.accept_max, d.order, 0-d.accept_min, d.order+1, d.cc, d.alpha);
    xjjroot::drawbox(d.accept_min, d.order, d.accept_max, d.order+1, d.cc, d.alpha);
    draw_det_name(d, kBlack);
  }
  // ax->Draw();
  c->SaveAs("cmsdet.pdf");
  for (auto& d : dets_up) {
    xjjroot::drawbox(0-d.accept_max, d.order, 0-d.accept_min, d.order+1, d.cc, d.alpha);
    xjjroot::drawbox(d.accept_min, d.order, d.accept_max, d.order+1, d.cc, d.alpha);
    draw_det_name(d, kWhite);
  }
  // ax->Draw();
  c->SaveAs("cmsdet_up.pdf");
  

  return 0;
}

int main(int argc, char* argv[]) {
  return macro();
}
