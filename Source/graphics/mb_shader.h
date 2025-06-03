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
  void add_vec3(std::string UniformName , glm::vec3& p_vector);
  void add_vec4(std::string UniformName , glm::vec4& p_vector);
  void add_float(std::string UniformName , float& p_float);
  void add_int_array(std::string UniformName , int* p_array, int size);
  ~Shader();
};