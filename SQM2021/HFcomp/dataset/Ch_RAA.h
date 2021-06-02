#include <TGraph.h>
#include <string>

namespace exps
{
  class Ch_RAA
  {
  public:
    Ch_RAA(std::string input);
    void Draw() { fgg->Draw("c same"); }
  private:
    TGraph* fgg;
  };

}

exps::Ch_RAA::Ch_RAA(std::string input)
{
  fgg = new TGraph(input.c_str());
  xjjroot::setthgrstyle(fgg, 17, 1, 20, 17, 1, 4);
}
