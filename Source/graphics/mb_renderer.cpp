#include "mb_renderer.h"
#include "../utils/mb_utils.h"

#define MAX_BATCH_SIZE 1000

Renderer::Renderer(GLFWwindow *window)
{
  if(!gladLoadGL())
  {
    LOG("ERROR::RENDERER::Failed to init renderer ... \n");
    return ;
  }
  LOG("DEBUG::RENDERER::Managed to init renderer ... \n");
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_BATCH_SIZE, nullptr, GL_DYNAMIC_DRAW); // reserve space

  // Setup vertex attributes
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

}

void Renderer::begin_frame()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Optional: customize bg color
  glClear(GL_COLOR_BUFFER_BIT);
  m_batch.clear();
}

void Renderer::draw_quad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color)
{
  float width = size.x;
  float height = size.y;
  Vertex v0;
  v0.position = {pos.x -width/2.f , pos.y - height/2};
  v0.color = color;
  Vertex v1;
  v1.position = {pos.x +width/2.f , pos.y - height/2};
  v1.color = color;
  Vertex v2;
  v2.position = {pos.x +width/2.f , pos.y + height/2};
  v2.color = color;
  Vertex v3;
  v3.position = {pos.x -width/2.f , pos.y - height/2};
  v3.color = color;
  Vertex v4;
  v4.position = {pos.x +width/2.f , pos.y + height/2};
  v4.color = color;
  Vertex v5;
  v5.position = {pos.x -width/2.f , pos.y + height/2};
  v5.color = color;
  m_batch.push_back(v0);
  m_batch.push_back(v1);
  m_batch.push_back(v2);
  m_batch.push_back(v3);
  m_batch.push_back(v4);
  m_batch.push_back(v5);
}

void Renderer::end_frame()
{
  if (m_batch.empty()) {
    LOG("INFO::GRAPHICS::RENDERER::Nothing in the vertex batch ...\n");
    return;
  }
  if(m_shader.find("main") != m_shader.end())
  {
    m_shader["main"].add_mat4("u_Projection", m_projection);
  }
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_batch.size() * sizeof(Vertex), m_batch.data());

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, m_batch.size());
  glBindVertexArray(0);
}

Renderer::~Renderer()
{
}

void Renderer::pass_shader(Shader shader, std::string shaderName)
{
  m_shader[shaderName] = shader;
}

void Renderer::select_shader(std::string ShaderName)
{
  m_shader[ShaderName].use();
}

void Renderer::select_shader(Shader shader)
{
  shader.use();
}

void Renderer::set_projection(glm::mat4 &matrix)
{
  m_projection = matrix;
}
