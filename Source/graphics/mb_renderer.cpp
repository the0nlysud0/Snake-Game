#include "mb_renderer.h"
#include "../utils/mb_utils.h"
#include <glm/gtc/matrix_transform.hpp>

#define MAX_BATCH_SIZE 1000

Renderer::Renderer(GLFWwindow *window)
{
  if(!gladLoadGL())
  {
    LOG("ERROR::RENDERER::Failed to init renderer ... \n");
    return ;
  }
  LOG("DEBUG::RENDERER::Managed to init renderer ... \n");
  if(is_instancing)
  {
    glm::vec2 quadVerts[6] = {
    {-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f},
    {-0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

    // attrib 0: position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceData) * MAX_BATCH_SIZE, nullptr, GL_DYNAMIC_DRAW);

    // attribs 1–4: mat4 (4 vec4s)
    for (int i = 0; i < 4; i++) {
        glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(glm::vec4) * i));
        glEnableVertexAttribArray(1 + i);
        glVertexAttribDivisor(1 + i, 1); // Per-instance
    }
    // attrib 5: vec3 color
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(glm::mat4)));
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(5, 1);
    // attrib 6: float texID
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(glm::mat4) + sizeof(glm::vec3)));
    glEnableVertexAttribArray(6);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);


  }
  else{
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_BATCH_SIZE, nullptr, GL_DYNAMIC_DRAW); // reserve space

  // Setup vertex attributes
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex , text_coords));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texID));
  glEnableVertexAttribArray(2);

  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
  glEnableVertexAttribArray(3);

  glBindVertexArray(0);
  }
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::begin_frame()
{
  glClearColor(1.f, 1.f, 1.f, 1.0f); // Optional: customize bg color
  glClear(GL_COLOR_BUFFER_BIT);
  m_batch.clear();
  m_instances.clear();
  m_textureSlotIndex = 1;
  m_textureSlots.fill(nullptr);
}

void Renderer::draw_quad(const glm::vec2 &pos, const glm::vec2 &size, glm::vec3 &color)
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
  m_selectedShader.use();
  m_selectedShader.add_vec3("entity_color" , color);
}

void Renderer::draw_quad(const glm::vec2& pos, float rotation , const glm::vec2& size, glm::vec3& color , Texture2D& texture)
{
  if(is_instancing)
  {
    if(m_instances.size()>= MAX_BATCH_SIZE)
    {
      end_frame();
      begin_frame();
    }
    float texID=0.0f;
    for (unsigned int i = 1; i < m_textureSlotIndex; ++i) {
        if (m_textureSlots[i] == &texture) {
            texID = (float)i;
            break;
        }
    }
    if (texID == 0.0f) {
        if (m_textureSlotIndex >= MAX_TEXTURES) {
            end_frame();
            begin_frame();
        }
        m_textureSlots[m_textureSlotIndex] = &texture;
        texID = (float)m_textureSlotIndex;
        m_textureSlotIndex++;
    }
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::rotate(model,glm::radians(rotation), {0.0f,0.0f,1.0f});
    // LOG("ANGLE(renderer): ", rotation,'\n');
    model = glm::scale(model, glm::vec3(size, 1.0f));
    m_selectedShader.use();
    m_selectedShader.add_mat4("model", model);
    // float rad_rotation = glm::radians(rotation);
    // m_selectedShader.add_float("rotation",rad_rotation);

    m_instances.push_back({model, color, texID});
  }
  else{
    if (m_batch.size() + 6 >= MAX_BATCH_SIZE) {
      end_frame();
      begin_frame();
    }
    float texID = 0.0f;
    for(unsigned int i=1;i<m_textureSlotIndex;++i)
    {
      if(m_textureSlots[i]==&texture)
      {
        texID = (float)i;
        break;
      }
    }
    if(texID ==0.0f)
    {
      if(m_textureSlotIndex >=MAX_TEXTURES)
      {
        end_frame();
        begin_frame();
      }
      m_textureSlots[m_textureSlotIndex] = &texture;
      texID = (float)m_textureSlotIndex;
      m_textureSlotIndex++;
    }
    // Unit quad centered at origin (-0.5 to 0.5 range)
    glm::vec2 half = {0.5f, 0.5f};
    glm::vec2 p0 = -half;
    glm::vec2 p1 = { half.x, -half.y};
    glm::vec2 p2 = half;
    glm::vec2 p3 = {-half.x, half.y};

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::rotate(model,glm::radians(rotation), {0.0f,0.0f,1.0f});
    model = glm::scale(model, glm::vec3(size, 1.0f));
    glm::vec2 uv0 = {0.0f, 0.0f};
    glm::vec2 uv1 = {1.0f, 0.0f};
    glm::vec2 uv2 = {1.0f, 1.0f};
    glm::vec2 uv3 = {0.0f, 1.0f};

    m_selectedShader.use();
    m_selectedShader.add_mat4("model", model);
    float rad_rotation = glm::radians(rotation);
    m_selectedShader.add_float("rotation",rad_rotation);
    // m_selectedShader.add_vec3("entity_color", color);

    m_batch.push_back({p0, uv0, texID, color});
    m_batch.push_back({p1, uv1, texID, color});
    m_batch.push_back({p2, uv2, texID, color});
    m_batch.push_back({p0, uv0, texID, color});
    m_batch.push_back({p2, uv2, texID, color});
    m_batch.push_back({p3, uv3, texID, color});
  } 
}

void Renderer::end_frame()
{
  if(is_instancing)
  {
    m_selectedShader.use();
    for (unsigned int i = 1; i < m_textureSlots.size(); ++i) {
      if (m_textureSlots[i]) {
        m_textureSlots[i]->use_texture(i);
      }
    }
    int samplers[16];
    for (int i = 0; i < 16; ++i) samplers[i] = i;
    m_selectedShader.add_int_array("textures", samplers, 16);
    if (m_instances.empty()) {
      LOG("INFO::GRAPHICS::RENDERER::Nothing in the vertex batch ...\n");
      return;
    }
    m_selectedShader.add_mat4("projection", m_projection);

    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_instances.size() * sizeof(InstanceData), m_instances.data());

    glBindVertexArray(m_VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_instances.size());
    glBindVertexArray(0);
  }
  else{
    m_selectedShader.use();
    for (unsigned int i = 1; i < m_textureSlots.size(); ++i) {
      if (m_textureSlots[i]) {
        m_textureSlots[i]->use_texture(i);
      }
    }
    int samplers[16];
    for (int i = 0; i < 16; ++i) samplers[i] = i;
    m_selectedShader.add_int_array("textures", samplers, 16);
    if (m_batch.empty()) {
      LOG("INFO::GRAPHICS::RENDERER::Nothing in the vertex batch ...\n");
      return;
    }

    m_selectedShader.add_mat4("projection", m_projection);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_batch.size() * sizeof(Vertex), m_batch.data());
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_batch.size());
    glBindVertexArray(0);
  }
}

Renderer::~Renderer()
{
}

void Renderer::pass_shader(Shader &shader, std::string shaderName)
{
  m_shader[shaderName] = shader;
}

void Renderer::select_shader(std::string ShaderName)
{
  m_shader[ShaderName].use();
  m_selectedShader = m_shader[ShaderName];
}

void Renderer::select_shader(Shader &shader)
{
  shader.use();
  m_selectedShader = shader;
}
void Renderer::set_projection(glm::mat4 &matrix)
{
  m_projection = matrix;
}
