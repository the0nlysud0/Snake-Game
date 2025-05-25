#pragma once

#include "mb_shader.h"
#include <GLFW/glfw3.h>

struct Vertex{
  glm::vec2 position;
  glm::vec3 color;
  glm::vec2 text_coords;
};

struct RenderData
{
  std::vector<Vertex> vertices;
};

struct Entity
{
  unsigned int VAO;
  unsigned int VBO;
};
class Renderer {
public:
    Renderer(GLFWwindow* window);
    ~Renderer();
    void pass_shader(Shader &shader , std::string shaderName);
    void select_shader(std::string ShaderName);
    void select_shader(Shader &shader);

    void set_projection(glm::mat4& matrix);

    void begin_frame();
    void draw_quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    void end_frame();

private:
    std::unordered_map<std::string , Shader> m_shader;
    Shader m_selectedShader;
    unsigned int m_VAO, m_VBO;
    std::vector<Vertex> m_batch;
    glm::mat4 m_projection;
};