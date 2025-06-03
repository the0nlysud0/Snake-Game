#include <map>

#include "../graphics/mb_renderer.h"

typedef unsigned int Entity;

struct Transform
{
  glm::vec2 position;
  float rotation;
  glm::vec2 scale;
};

struct Sprite
{
  glm::vec3 color;
  Texture2D* texture;
};

class GameWorld
{
private:
  std::map<std::string,Entity> m_entities;
  std::unordered_map<Entity , Transform> m_transforms;
  std::unordered_map<Entity , Sprite> m_sprites;
  unsigned int m_entity_count=0;
  Renderer* m_renderer;
  GLFWwindow* m_window;
public:
  GameWorld();
  void attach_renderer(Renderer& p_renderer);
  void attach_window(GLFWwindow* window);
  GLFWwindow* get_window() const { return m_window; }

  Entity make_entity(const std::string& entity_name);
  Entity get_entity(const std::string& entity_name) const;
  std::string get_entity(Entity id);

  Transform& get_transform(Entity id);
  Sprite& get_sprite(Entity id);

  bool check_collision_quad(Entity a , Entity b);
  void update(float deltaTime);
  void render();

  void destroy_entity(Entity id);
  void destroy_last();

  ~GameWorld();
};