#include <TColor.h>
#include <iostream>
#include <string>
#include "xjjcuti.h"

std::map<std::string, int> precolor = {
  {"kWhite", 0},   
  {"kBlack", 1},   
  {"kGray", 920},
  {"kRed", 632}, 
  {"kGreen", 416}, 
  {"kBlue", 600}, 
  {"kYellow", 400}, 
  {"kMagenta", 616}, 
  {"kCyan", 432},
  {"kOrange", 800}, 
  {"kSpring", 820}, 
  {"kTeal", 840}, 
  {"kAzure", 860}, 
  {"kViolet", 880}, 
  {"kPink", 900}
};

int main(int argc, char* argv[])
{
  std::string cc = "#89b91";
  if(argc > 1) cc = std::string(argv[1]);
  int icol = 0;
  if(xjjc::str_startsby(cc, "#"))
    icol = TColor::GetColor(cc.c_str());
  else
    {
      std::string name = "";
      int prec = 0;
      for(auto& pre : precolor)
        {
          if(xjjc::str_contains(cc, pre.first))
            {
              icol = pre.second;
              int offset = atoi(xjjc::str_eraseall(cc, pre.first).c_str());
              icol += offset;
              break;
            }
        }
    }

  std::cout<<cc<<" => "<<icol<<std::endl;
  return 0;
}
