#pragma once

#include <iostream>
#include <filesystem>

class FileManager
{
private:

public:
  FileManager(/* args */);
  ~FileManager();
};


std::filesystem::path HomePath()
{
  return std::filesystem::path();
}