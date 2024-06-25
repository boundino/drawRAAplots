#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "hfdata.h"
#include "xjjcuti.h"
#include "xjjrootuti.h"

#include "cvt.h"

class item
{
public:
  item(std::map<std::string, std::string>& a);
  std::string operator[](std::string key) { return fa[key]; }
private:
  std::map<std::string, std::string> fa;
  std::vector<std::string> fva = {"inputfile", "ref",
                                  "obs", "xtitle", "particle", 
                                  "system", "energy", "collab", 
                                  "kinea", "kineb", 
                                  "link", "update"};
  void print(std::vector<std::string> ignore = {"inputfile", "link", "tag"});
  int width(std::string a)
  {
    if(a=="ref") return 23;
    else if(a=="particle") return 20;
    else if(a=="kinea") return 24;
    else if(a=="kineb") return 22;
    else return 8;
  }
};

int getjs(std::string input)
{
  xjjroot::mkdir("js/x");
  std::vector<std::string> a = xjjc::str_divide(input, "[]");
  for(auto& ia : a) { ia = xjjc::str_trim(ia); }
  std::map<std::string, std::string> b;
  //
  b["inputfile"] = a[0]; // inputfile
  b["ref"] = a[1]; // ref
  b["link"] = a[2];
  b["update"] = a[3];
  std::string name = xjjc::str_erasestar(a[0], "*/");
  name = xjjc::str_erasestar(name, ".*");
  std::vector<std::string> vn = xjjc::str_divide(name, "_");
  b["particle"] = cvt::parseparticle(vn[0]); // particle
  b["obs"] = vn[1]; // obs
  b["xtitle"] = vn[2]; // xtitle
  b["system"] = cvt::parsesystem(vn[3]); // system
  b["energy"] = cvt::parseenergy(vn[4], b["system"]); // energy
  b["collab"] = vn[5]; // collab
  b["kinea"] = cvt::parsekine(vn[6]);
  b["kineb"] = cvt::parsekine(vn[7]);
  item it(b);
  exps::hfdata* dat = new exps::hfdata(it["inputfile"], kBlack, "", "", 20);

  std::ofstream fout(Form("js/%s.js", it["tag"].c_str()));
  fout << "dataset[\"" << it["tag"] << "\"] = {" << std::endl;
  fout << "    reference : \"" << it["ref"] << "\"," << std::endl;
  fout << "    link : \"" << it["link"] << "\"," << std::endl;
  fout << "    update : \"" << it["update"] << "\"," << std::endl;
  fout << "    observable : \"" << it["obs"] << "\"," << std::endl;
  fout << "    xtitle : \"" << it["xtitle"] << "\"," << std::endl;
  fout << "    particle : \"" << it["particle"] << "\"," << std::endl;
  fout << "    collision : \"" << it["system"] << "\"," << std::endl;
  fout << "    energy : \"" << it["energy"] << "\"," << std::endl;
  fout << "    collab : \"" << it["collab"] << "\"," << std::endl;
  fout << "    kinea : \"" << it["kinea"] << "\"," << std::endl;
  fout << "    kineb : \"" << it["kineb"] << "\"," << std::endl;
  fout << "    data : [" << std::endl;
  for(int i=0; i<dat->n(); i++)
    {
      double x, y;
      dat->grstat()->GetPoint(i, x, y);
      fout << "        {\"x\": " << x
           << ", \"xl\": " << x - dat->grstat()->GetErrorXlow(i)
           << ", \"xh\": " << x + dat->grstat()->GetErrorXhigh(i)
           << ", \"y\": " << y
           << ", \"stath\": " << dat->grstat()->GetErrorYhigh(i)
           << ", \"statl\": " << dat->grstat()->GetErrorYlow(i)
           << ", \"systh\": " << dat->grsyst()->GetErrorYhigh(i)
           << ", \"systl\": " << dat->grsyst()->GetErrorYlow(i)
           << "}," << std::endl;
    }

  fout << "    ]" << std::endl << "};" << std::endl;
  fout.close();
  std::cout << std::endl;
  return 0;
}

int main(int argc, char* argv[])
{
  return getjs(argv[1]);
}

item::item(std::map<std::string, std::string>& a)
{
  for(int i=0; i<fva.size(); i++)
    fa[fva[i]] = a[fva[i]]; 

  fva.insert(fva.begin(), "tag");
  fa["tag"] = xjjc::str_erasestar(a["inputfile"], "*/");
  fa["tag"] = xjjc::str_erasestar(fa["tag"], ".*");

  print();
}

void item::print(std::vector<std::string> ignore)
{
  int wline = 1;
  for(auto& a : fva)
    if(std::find(ignore.begin(), ignore.end(), a) == ignore.end()) 
      wline += (width(a)+2);

  // for(auto& a : fva)
  //   if(std::find(ignore.begin(), ignore.end(), a) == ignore.end()) 
  //     std::cout << "| " << std::left << std::setw(width(a)) << a;
  // std::cout<<"|"<<std::endl; xjjc::prt_divider("\e[0m", wline);

  
  // xjjc::prt_divider("\e[0m", wline);
  std::cout << "\e[40;1m";
  for(auto& a : fva)
    if(std::find(ignore.begin(), ignore.end(), a) == ignore.end())
      std::cout << "| " << std::left << std::setw(width(a)) << fa[a];
  std::cout << "|\e[0m" << std::endl;
  std::cout << "\e[32m ==> " << fa["tag"] << "\e[0m " << std::endl;
  // xjjc::prt_divider("\e[0m", wline);
}
