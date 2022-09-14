#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

void sortdata(std::string inputname)
{
  std::ifstream getdata(inputname.c_str());
  std::vector<float> vx1, vy1;
  while(true)
    {
      float x, y1;
      getdata>>x;
      if(getdata.eof()) { break; }
      getdata>>y1;
      vx1.push_back(x);
      vy1.push_back(y1);
    }
  std::reverse(vx1.begin(), vx1.end());
  std::reverse(vy1.begin(), vy1.end());
  for(int i=0; i<vx1.size(); i++)
    std::cout<<vx1[i]<<" "<<vy1[i]<<std::endl;
}

int main(int argc, char* argv[])
{
  if(argc==2) { sortdata(argv[1]); return 0; }
  return 1;
}
