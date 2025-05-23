#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
class Shader
{
private:
  unsigned int m_ShaderID;
public:
  Shader();
  void add_shader(std::string path ,GLenum type);
  void link_program();
  void use() const;
  void add_mat4(std::string UniformName , glm::mat4& matrix);
  void add_vec4(std::string UniformName , glm::vec4& p_vector);
  ~Shader();
};