#include <fstream>
#include <iostream>
#include <vector>
#include "xjjcuti.h"
#include "cvt.h"

int convert(std::string inputname = "cleanup.txt")
{
  std::ifstream getdat(inputname.c_str());
  std::ofstream outcp("outcp.sh");
  std::ofstream runjs("../run_getjs2.sh");

  while(true)
    {
      std::string line;
      std::getline(getdat, line);
      if(getdat.eof()) break;
      std::vector<std::string> pars = xjjc::str_divide(line, "[]");
      for(auto& p : pars) { p = xjjc::str_erasetwospace(p); }
      
      auto ilocationold = xjjc::str_erasestar(pars[0], ":*");

      // 0      
      auto idir = xjjc::str_erasestar(pars[0], "/*");
      auto ifiletype = xjjc::str_erasestar(pars[0], "*.");
      std::vector<std::string> vfiletype = xjjc::str_divide(ifiletype, ":");
      ifiletype = vfiletype[0];
      auto iopt = vfiletype.size()>1?vfiletype[1]:"";
      // 1
      auto ireference = pars[1];
      std::cout << ireference << ", ";
      // 2
      auto iobservable = pars[2];
      // 3
      auto ixtitle = pars[3];
      // 4
      auto iparticle = pars[4];
      for(auto i : cvt::mapp)
          iparticle = xjjc::str_replaceall(iparticle, i.first, i.second);
      iparticle = xjjc::str_replaceallspecial(iparticle, "");
      // 5
      auto icollision = pars[5];
      // 6
      auto ienergy = pars[6];
      ienergy = cvt::parseenergy_back(ienergy);
      // 7
      auto icollab = pars[7];
      // 8
      auto ikinea = pars[8];
      ikinea = cvt::parsekine_back(ikinea);
      // 9
      auto ikineb = pars[9];
      ikineb = cvt::parsekine_back(ikineb);
      // 11
      auto ilink = pars[11];

      std::string inewname = iparticle
                + "_" + iobservable
                + "_" + ixtitle
                + "_" + icollision
                + "_" + ienergy
                + "_" + icollab
                + "_" + ikinea
                + "_" + ikineb;

      std::cout << inewname << ", " << ilink;
      std::cout << std::endl;

      inewname = idir + "/" + inewname + "." + ifiletype;

      outcp << "mv " << ilocationold << " " << inewname << " -v" << std::endl;
      runjs << "\"" << inewname << ":" << iopt << "[]" << ireference << "[]" << ilink << "\"" << std::endl;
    }

  return 0;
}

int main(int argc, char* argv[])
{
  return convert();
}

