#include <fstream>
#include <string>
#include <iostream>
#include <vector>

void ctv(std::string inputname)
{
  std::vector<float> vx, vxmin, vxmax, vy1, vy2, vye1, vye2;
  std::ifstream inf(inputname.c_str());
  while(true)
    {
      float xmin, xmax, y1, ye1, y2, ye2;
      inf >> xmin;
      if(inf.eof()) break;
      inf >> xmax
          >> y1 >> ye1 
          >> y2 >> ye2;
      vx.push_back((xmin+xmax)/2.);
      vxmin.push_back(xmin);
      vxmax.push_back(xmax);
      vy1.push_back(y1);
      vye1.push_back(ye1);
      vy2.push_back(y2);
      vye2.push_back(ye2);
    }

  std::cout<<"1.5 TO 4.0"<<std::endl;
  for(int i=0; i<vx.size(); i++)
    {
      std::cout << vx[i] << "  "
                << vxmin[i] << "  " << vxmax[i] << "  "
                << vy1[i] << "  +" << vye1[i] << "  -" << vye1[i] <<"  "
                << "0  0" << std::endl;
    }

  std::cout<<"-5.0 TO -2.5"<<std::endl;
  for(int i=0; i<vx.size(); i++)
    {
      std::cout << vx[i] << "  "
                << vxmin[i] << "  " << vxmax[i] << "  "
                << vy2[i] << "  +" << vye2[i] << "  -" << vye2[i] <<"  "
                << "0  0" << std::endl;
    }
}

int main(int argc, char* argv[])
{
  ctv(argv[1]);
  return 0;
}
