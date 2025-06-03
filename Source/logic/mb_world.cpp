#include "mb_world.h"
#include "../utils/mb_utils.h"
#include <glm/gtc/matrix_transform.hpp>

GameWorld::GameWorld()
{
}

void GameWorld::attach_renderer(Renderer &p_renderer)
{
  m_renderer = &p_renderer;
}

void GameWorld::attach_window(GLFWwindow *window)
{
  m_window = window;
}

Entity GameWorld::make_entity(const std::string &entity_name)
{
  m_entities[entity_name]=m_entity_count++;
  m_transforms[m_entities[entity_name]] = Transform{};
  m_sprites[m_entities[entity_name]] = Sprite{};
  LOG("DEBUG::GAME::LOGIC::ENTITY::Created entity : " , entity_name , " reference: " , m_entity_count);
  return m_entities[entity_name];
}

Entity GameWorld::get_entity(const std::string &entity_name) const
{
  auto it = m_entities.find(entity_name);
  return (it != m_entities.end()) ? it->second : -1;
}

std::string GameWorld::get_entity(Entity id)
{
  for(const auto& [name , eid] : m_entities)
  {
    if(eid == id)
    {
      return name;
    }
  }
  return "Unknown Entity";
}

Transform &GameWorld::get_transform(Entity id)
{
  return m_transforms.at(id);
}

Sprite &GameWorld::get_sprite(Entity id)
{
  return m_sprites.at(id);
}

bool GameWorld::check_collision_quad(Entity a, Entity b)
{
  auto& tA = m_transforms[a];
  auto& tB = m_transforms[b];
  
  glm::vec2 minA = tA.position - tA.scale *0.5f;
  glm::vec2 minB = tB.position - tB.scale *0.5f;
  glm::vec2 maxA = tA.position + tA.scale *0.5f;
  glm::vec2 maxB = tB.position + tB.scale *0.5f;
  bool collisionX = minA.x>minB.x && maxA.x>maxB.x;
  bool collisionY = minA.y>minB.y && maxA.y>maxB.y;
  return collisionX&&collisionY;
}

void GameWorld::update(float deltaTime)
{
  if(!m_window)
  {
    float aspect_ratio = 800 / (float)600;
    glm::mat4 projection = glm::ortho(-aspect_ratio , aspect_ratio , -1.0f,1.0f);
  }
  int height,width;
  glfwGetWindowSize(m_window , &width , &height);
  float aspect_ratio = width / (float)height;
  glm::mat4 projection = glm::ortho(-aspect_ratio , aspect_ratio , -1.0f,1.0f);
  m_renderer->set_projection(projection);
}

void GameWorld::render()
{
  if(!m_renderer) return;
  m_renderer->begin_frame();
  for(const auto& [name, id] : m_entities)
  {
    const auto& transform = m_transforms[id];
    auto& sprite = m_sprites[id];
    m_renderer->draw_quad(transform.position , transform.rotation , transform.scale , sprite.color , *sprite.texture);
  }

  m_renderer->end_frame();
}

void GameWorld::destroy_entity(Entity id)
{
  m_transforms.erase(id);
  m_sprites.erase(id);
  m_entities.erase(get_entity(id));
}

void GameWorld::destroy_last()
{
  if(m_entity_count>0)
  {
  m_transforms.erase(m_entity_count-1);
  m_sprites.erase(m_entity_count-1);
  m_entities.erase(get_entity(m_entity_count-1));
  m_entity_count--;
  }
}

GameWorld::~GameWorld()
{
}
