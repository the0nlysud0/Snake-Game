#include "mb_world.h"

class mb_object
{
private:
  mb_object* m_parent;
  GameWorld& m_game_world;
  std::string m_object_name;
  glm::vec2 m_obj_direction;
  std::unordered_map<std::string , Entity> m_internals;
  unsigned int m_entity_count=0;
public:
  mb_object(GameWorld& world);
  void add_internal(std::string internalName);
  void add_transform(std::string internal , Transform transform);
  void add_sprite(std::string internal , Sprite& sprite);
  // Basically update the origin's positon
  void update();

  ~mb_object();
};
