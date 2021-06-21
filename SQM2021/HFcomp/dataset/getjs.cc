#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "hfdata.h"
#include "xjjcuti.h"

class item
{
public:
  item(std::vector<std::string> a);
  std::string operator[](std::string key) { return fa[key]; }
private:
  std::map<std::string, std::string> fa;
  std::vector<std::string> fva = {"inputfile", "ref",
                                  "obs", "xtitle", "particle", 
                                  "system", "energy", "collab", 
                                  "kinea", "kineb", "kinec", 
                                  "link"};
  void print();
  int width(std::string a)
  {
    if(a=="ref") return 23;
    else if(a=="tag") return 30;
    else if(a=="xtitle") return 14;
    else if(a=="inputfile") return 40;
    else if(a=="particle") return 14;
    else return 10;
  }
};

int getjs(item it)
{
  exps::hfdata* dat = new exps::hfdata(it["inputfile"], kBlack, "", "", 20);

  std::ofstream fout(Form("js/%s.js", it["tag"].c_str()));
  fout << "dataset[\"" << it["tag"] << "\"] = {" << std::endl;
  fout << "    reference : \"" << it["ref"] << "\"," << std::endl;
  fout << "    link : \"" << it["link"] << "\"," << std::endl;
  fout << "    observable : \"" << it["obs"] << "\"," << std::endl;
  fout << "    xtitle : \"" << it["xtitle"] << "\"," << std::endl;
  fout << "    particle : \"" << it["particle"] << "\"," << std::endl;
  fout << "    collision : \"" << it["system"] << "\"," << std::endl;
  fout << "    energy : \"" << it["energy"] << "\"," << std::endl;
  fout << "    collab : \"" << it["collab"] << "\"," << std::endl;
  fout << "    kinea : \"" << it["kinea"] << "\"," << std::endl;
  fout << "    kineb : \"" << it["kineb"] << "\"," << std::endl;
  fout << "    kinec : \"" << it["kinec"] << "\"," << std::endl;
  fout << "    data : [" << std::endl;

  for(int i=0; i<dat->n(); i++)
    {
      double x, y;
      dat->grstat()->GetPoint(i, x, y);
      fout << "        {\"x\": " << x
           << ", \"y\": " << y
           << ", \"stath\": " << dat->grstat()->GetErrorYhigh(i)
           << ", \"statl\": " << dat->grstat()->GetErrorYlow(i)
           << ", \"systh\": " << dat->grsyst()->GetErrorYhigh(i)
           << ", \"systl\": " << dat->grsyst()->GetErrorYlow(i)
           << "}," << std::endl;
    }

  fout << "    ]" << std::endl << "};" << std::endl;
  fout.close();

  return 0;
}

int main(int argc, char* argv[])
{
  std::vector<std::string> a = xjjc::str_divide(argv[1], "[]");
  item arg(a);
  return getjs(arg);
}

item::item(std::vector<std::string> a)
{
  for(int i=0; i<fva.size(); i++)
    fa[fva[i]] = a[i]; 

  fva.insert(fva.begin(), "tag");
  fa["tag"] = xjjc::str_erasestar(a[0], "*/");
  fa["tag"] = xjjc::str_erasestar(fa["tag"], ".*");

  print();
}

void item::print()
{
  int wline = 178;
  xjjc::prt_divider("\e[0m", wline);
  for(auto& a : fva)
    {
      if(a=="inputfile" || a=="link") continue;
      std::cout << "| " << std::left << std::setw(width(a)) << a;
    }
  std::cout<<"|"<<std::endl; xjjc::prt_divider("\e[0m", wline);
  for(auto& a : fva)
    {
      if(a=="inputfile" || a=="link") continue;
      std::cout << "| " << std::left << std::setw(width(a)) << fa[a];
    }
  std::cout<<"| "<<std::endl; xjjc::prt_divider("\e[0m", wline);
}
