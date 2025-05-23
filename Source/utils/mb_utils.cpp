#include "mb_utils.h"
#include <fstream>
#include <sstream>

std::string mb_WindowsOpenFileDialog()
{
  
}

void ReadFile(std::string &path, std::string &file_text)
{
  std::ifstream file(path);
  std::stringstream ss;
  if(!file.is_open())
  {
    LOG("ERROR::FILE::IO::Failed to open file : " , path , '\n');
    return;
  }
  ss << file.rdbuf();
  LOG("DEBUG::FILE::IO::Sucess opening file : " , path , '\n');
  // LOG(ss.str());
  file_text = ss.str();
}
