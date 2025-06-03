#pragma once

#include "mb_shader.h"
#include "mb_texture.h"
#include <GLFW/glfw3.h>
#include <array>

struct Vertex{
  glm::vec2 position;
  glm::vec2 text_coords;
  float texID;
  glm::vec3 color;
};


struct RenderData
{
  std::vector<Vertex> vertices;
};

struct InstanceData {
    glm::mat4 model;
    glm::vec3 color;
    float texID;
};

static constexpr unsigned int MAX_TEXTURES = 16;

class Renderer {
public:
    Renderer(GLFWwindow* window);
    ~Renderer();
    void pass_shader(Shader &shader , std::string shaderName);
    void select_shader(std::string ShaderName);
    void select_shader(Shader &shader);

    void set_projection(glm::mat4& matrix);

    void begin_frame();
    void draw_quad(const glm::vec2& pos, const glm::vec2& size, glm::vec3& color);
    void draw_quad(const glm::vec2& pos, float rotation , const glm::vec2& size, glm::vec3& color , Texture2D& texture);
    void end_frame();

private:
    std::unordered_map<std::string , Shader> m_shader;
    std::array<Texture2D*, MAX_TEXTURES> m_textureSlots;
    bool is_instancing=true;
    unsigned int m_textureSlotIndex =1;
    Shader m_selectedShader;
    unsigned int m_VAO, m_VBO;
    unsigned int m_instanceVBO;
    std::vector<InstanceData> m_instances;
    std::vector<Vertex> m_batch;
    glm::mat4 m_projection;
};