#pragma once
#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>

class Texture2D
{
private:
  unsigned char* m_texture_data;
  int m_width , m_height , m_nrchannels;
  unsigned int m_textureID;
public:
  Texture2D(std::string path);
  void use_texture(unsigned int slot=0);
  ~Texture2D();
};