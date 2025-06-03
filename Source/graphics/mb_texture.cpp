#include "mb_texture.h"
#include "../utils/mb_utils.h"
Texture2D::Texture2D(std::string path)
{
  stbi_set_flip_vertically_on_load(true);
  m_texture_data = stbi_load(path.c_str(),&m_width , &m_height , &m_nrchannels , 0);
  glGenTextures(1,&m_textureID);
  glBindTexture(GL_TEXTURE_2D , m_textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  if(m_texture_data)
  {
    LOG("Loaded texture: ", path, " size: ", m_width, "x", m_height,'\n');
    GLenum format = (m_nrchannels == 4) ? GL_RGBA : GL_RGB;
    LOG("Channels: ", m_nrchannels, '\n');
    for(int i=0;i<100; ++i)
    {
      LOG("Byte ",i , ":", (int)m_texture_data[i],"\n");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format ,GL_UNSIGNED_BYTE, m_texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else{
    LOG("ERROR::GRAPHICS::TEXTURES::Failed to load texture from image ...\n");
  }

  // stbi_image_free(m_texture_data);
}

void Texture2D::use_texture(unsigned int slot)
{
  glActiveTexture(GL_TEXTURE0 + slot); // activate the texture unit first before binding texture
  glBindTexture(GL_TEXTURE_2D, m_textureID);
}

Texture2D::~Texture2D()
{
  glDeleteTextures(1, &m_textureID);
}
