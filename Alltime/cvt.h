
namespace cvt
{
  std::map<std::string, std::string> mapp = {
    {"(c,b&rarr;) ", "cbTO"},
    {"(b&rarr;) ", "bTO"},
    {"(c&rarr;) ", "cTO"},
    {"Prompt ", "apr"},
    {"Inclusive ", "inc"},
    {"Light ", "Light"},
    {"<sup>0</sup>", "0"},
    {"J/", "J"},
    {"<sup>*</sup>", "star"},
    {" / ", "To"},
    {"(1S)", "1S"},
    {"(2S)", "2S"},
    {"(3S)", "3S"},
    {"<sub>s</sub>", "subs"},
    {"<sup>&plusmn;</sup>", "plusmn"},
    {"<sup>&plus;</sup>", "plus"},
    {"ambda<sub>c</sub>", "ambdac"},
    {"ambda<sub>b</sub>", "ambdab"}, 
    {"&Xi;<sub>c</sub>", "Xic"},
    {"<sub>c</sub>", "subc"},
    {"&#772;", "bar"},
  };
  std::vector<std::string> vtgreek = {
    "psi", "mu", "Upsilon", "eta", "Lambda", "Delta", "pi"
  };

  std::string parseparticle(std::string str);
  std::string parseenergy(std::string str);
  std::string parsekine(std::string str);
  std::string parsekine_back(std::string str);
  std::string parseenergy_back(std::string str);
  std::string parsevar_back(std::string str);
}

std::string cvt::parseparticle(std::string str)
{
  for(auto p : mapp)
    if(!(xjjc::str_contains(str, "cbTO") && p.second=="bTO") && 
       !(xjjc::str_contains(str, "plusmn") && p.second=="plus"))
      str = xjjc::str_replaceall(str, p.second, p.first);
  for(auto p : vtgreek)
    if(!(xjjc::str_contains(str, "Upsilon") && p=="psi"))
      str = xjjc::str_replaceall(str, p, "&"+p+";");
  return str;
}

std::string cvt::parseenergy(std::string str)
{
  str = xjjc::str_replaceall(str, "GeV", " GeV");
  str = xjjc::str_replaceall(str, "8TeV", "8p16TeV");
  str = xjjc::str_replaceall(str, "5TeV", "5p02TeV");
  str = xjjc::str_replaceall(str, "TeV", " TeV");
  auto vstr = xjjc::str_divide(str, " ");
  str = xjjc::number_remove_zero(xjjc::string_to_number(vstr[0])) + " " + vstr[1];
  return str;
}

std::string cvt::parsekine(std::string str)
{
  auto vstr = xjjc::str_divide(str, "-");
  if(vstr.size() != 3) return str;
  for(auto& v : vstr)
    {
      v = xjjc::str_replaceall(v, "L", "(");
      v = xjjc::str_replaceall(v, "R", ")");
    }

  auto var = vstr[0];
  // cent
  if(var == "cent") 
    return vstr[1]+"-"+vstr[2]+"%";

  // others
  if(xjjc::str_contains(var, "pT"))
    var = xjjc::str_replaceall(var, "pT", "p<sub>T</sub>");
  if(xjjc::str_contains(var, "ycm"))
    var = xjjc::str_replaceall(var, "ycm", "y<sub>cm</sub>");
  if(xjjc::str_contains(var, "Ntrk"))
    var = xjjc::str_replaceall(var, "Ntrk", "N<sub>trk</sub>");
  if(xjjc::str_contains(var, "abs"))
    var = xjjc::str_replaceall(var, "abs", "|") + "|";
  for(auto p : vtgreek)
    var = xjjc::str_replaceall(var, p, "&"+p+";");

  auto xmin = vstr[1], xmax = vstr[2];
  auto xmax_num = xjjc::str_replaceall(xmax, "(", "");
  xmax_num = xjjc::str_replaceall(xmax_num, ")", "");
  auto xmin_num = xjjc::str_replaceall(xmin, "(", "");
  xmin_num = xjjc::str_replaceall(xmin_num, ")", "");
  xmax =  xjjc::str_replaceall(xmax, xmax_num, xjjc::number_remove_zero(xjjc::string_to_number(xmax_num)));
  if(xmin != "lt" && xmin != "gt")
    xmin =  xjjc::str_replaceall(xmin, xmin_num, xjjc::number_remove_zero(xjjc::string_to_number(xmin_num)));

  std::string result;
  if(xmin == "lt")
    result = var + " < " + xmax;
  else if(xmin == "gt")
    result = var + " > " + xmax;
  else
    result = xmin + " < " + var + " < " + xmax;
  result = xjjc::str_replaceall(result, " )", ") ");
  result = xjjc::str_replaceall(result, "( ", " (");

  if(vstr[0] == "pT")
    result += " GeV";

  return result;
}

std::string cvt::parsekine_back(std::string str)
{
  std::string result(str);
  if(str.back() == '%')
    {
      result.erase(result.end()-1);
      result = "cent-" + result;
    }
  std::vector<std::string> results = xjjc::str_divide(str, " < ");
  auto nr = results.size();
  if(nr == 3)
    {
      auto xmin = results[0], var = parsevar_back(results[1]), xmax = results[2];
      result = var + "-" + xjjc::number_to_string(atof(xmin.c_str())) 
        + "-" + xjjc::number_to_string(atof(xmax.c_str()));
    }
  if(nr == 2)
    {
      auto var = parsevar_back(results[0]), xmax = results[1];
      result = var + "-" + "lt"
        + "-" + xjjc::number_to_string(atof(xmax.c_str()));
    }
  return result;
}

std::string cvt::parsevar_back(std::string str)
{
  std::string result = xjjc::str_replaceall(str, "&#7451;", "T");
  if(str.front() == '|' && str.back() == '|')
    result = "abs" + result;
  result = xjjc::str_replaceallspecial(result, "");
  return result;
}

std::string cvt::parseenergy_back(std::string str)
{
  std::string result = xjjc::str_replaceall(str, " ", "");
  result = xjjc::str_replaceall(result, ".", "p");
  return result;
}
