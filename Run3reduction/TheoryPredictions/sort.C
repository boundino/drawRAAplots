#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

void sortdata(std::string inputname)
{
  std::ifstream getdata(inputname.c_str());
  std::map<float, float> dataset;
  std::vector<float> datavec;
  while(true)
    {
      float x, y;
      getdata>>x;
      if(getdata.eof()) { break; }
      getdata>>y;
      dataset.insert(std::pair<float,float>(x, y));      
      datavec.push_back(x);
    }
  std::sort(datavec.begin(), datavec.end());
  for(auto& it : datavec) { std::cout<<it<<" "<<dataset[it]<<std::endl; }
}

int main(int argc, char* argv[])
{
  if(argc==2) { sortdata(argv[1]); return 0; }
  return 1;
}
