
namespace cvt
{
  std::map<std::string, std::string> mapp = {
    {"(b&rarr;) ", "bTO"},
    {"(c&rarr;) ", "cTO"},
    {"(c,b&rarr;) ", "cbTO"},
    {"Prompt ", "apr"},
    {"Inclusive ", "inc"},
    {"Light ", "Light"},
    {"&#8304;", "0"},
    {"J/", "J"},
    {"(1S)", "1S"},
    {"(2S)", "2S"},
    {"(3S)", "3S"},
  };
  std::vector<std::string> vtgreek = {
    "psi", "mu", "Upsilon", "eta", "plusmn"
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
    str = xjjc::str_replaceall(str, p.second, p.first);
  for(auto p : vtgreek)
    str = xjjc::str_replaceall(str, p, "&"+p+";");
  return str;
}

std::string cvt::parseenergy(std::string str)
{
  str = xjjc::str_replaceall(str, "GeV", " GeV");
  str = xjjc::str_replaceall(str, "TeV", " TeV");
  return str;
}

std::string cvt::parsekine(std::string str)
{
  auto vstr = xjjc::str_divide(str, "-");
  if(vstr.size() != 3) return str;
  auto var = vstr[0];
  if(var == "cent") 
    return vstr[1]+"-"+vstr[2]+"%";
  if(xjjc::str_contains(var, "pT"))
    var = xjjc::str_replaceall(var, "pT", "p&#7451;");
  if(xjjc::str_startsby(var, "abs"))
    var = xjjc::str_replaceall(var, "abs", "|") + "|";
  for(auto p : vtgreek)
    var = xjjc::str_replaceall(var, p, "&"+p+";");

  auto xmin = vstr[1], xmax = vstr[2];
  if(xmin == "lt")
      return var + " < " + xjjc::number_remove_zero(xjjc::string_to_number(xmax));
  if(xmin == "gt")
      return var + " > " + xjjc::number_remove_zero(xjjc::string_to_number(xmax));
  return xjjc::number_remove_zero(xjjc::string_to_number(xmin)) + " < " + var + " < " + xjjc::number_remove_zero(xjjc::string_to_number(xmax));
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
