#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

void sortdata(std::string inputname)
{
  std::ifstream getdata(inputname.c_str());
  std::vector<float> vx1, vx2, vy1, vy2;
  while(true)
    {
      float x, y1, y2;
      getdata>>x;
      if(getdata.eof()) { break; }
      getdata>>y1>>y2;
      vx1.push_back(x);
      vy1.push_back(y1);
      vx2.push_back(x);
      vy2.push_back(y2);
    }
  std::reverse(vx2.begin(), vx2.end());
  std::reverse(vy2.begin(), vy2.end());
  for(int i=0; i<vx1.size(); i++)
    std::cout<<vx1[i]<<" "<<vy1[i]<<std::endl;
  for(int i=0; i<vx2.size(); i++)
    std::cout<<vx2[i]<<" "<<vy2[i]<<std::endl;
}

int main(int argc, char* argv[])
{
  if(argc==2) { sortdata(argv[1]); return 0; }
  return 1;
}
