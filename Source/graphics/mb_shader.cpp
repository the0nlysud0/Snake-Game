#include "mb_shader.h"
#include "../utils/mb_utils.h"
#include "../utils/mb_files.h"
#include <glm/gtc/type_ptr.hpp>
Shader::Shader()
{
  m_ShaderID = glCreateProgram();
}

void Shader::add_shader(std::string path, GLenum type)
{
  std::string sourceShader;
  ReadFile(path , sourceShader);
  const char* Source = sourceShader.c_str();
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader , 1 , &Source , nullptr);
  glCompileShader(shader);
  int success;
  char infoLog[512];
  glGetShaderiv(shader , GL_COMPILE_STATUS , &success);
  if(!success)
  {
    glGetShaderInfoLog(shader , 512 , nullptr , infoLog);
    LOG(infoLog, '\n');
    return ;
  }
  LOG("INFO::GRAPHICS::SHADER::Compilation resulted in success");
  glAttachShader(m_ShaderID , shader);
  glDeleteShader(shader);
}

void Shader::link_program()
{
  glLinkProgram(m_ShaderID);
    int success;
  char infoLog[512];
  glGetProgramiv(m_ShaderID , GL_LINK_STATUS , &success);
  if(!success)
  {
    glGetProgramInfoLog(m_ShaderID , 512 , nullptr , infoLog);
    LOG(infoLog, '\n');
    return ;
  }
  LOG("INFO::GRAPHICS::SHADER::Linking resulted in success");
}

void Shader::use() const
{
  glUseProgram(m_ShaderID);
}

void Shader::add_mat4(std::string UniformName, glm::mat4 &matrix)
{
  unsigned int location = glGetUniformLocation(m_ShaderID , UniformName.c_str());
  glUniformMatrix4fv(location , 1 ,GL_FALSE,glm::value_ptr(matrix));
}

void Shader::add_vec4(std::string UniformName, glm::vec4 &p_vector)
{
  unsigned int location = glGetUniformLocation(m_ShaderID , UniformName.c_str());
  LOG("Uniform location for ", UniformName, ": ", location, '\n');
  glUniformMatrix4fv(location , 1 ,GL_FALSE,glm::value_ptr(p_vector));
}

Shader::~Shader()
{
  // glDeleteProgram(m_ShaderID);
}
