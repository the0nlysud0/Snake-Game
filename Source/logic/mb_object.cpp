#include "mb_object.h"

mb_object::mb_object(GameWorld &world):m_game_world(world)
{
}

void mb_object::add_internal(std::string internalName)
{
  m_internals[internalName] = m_game_world.make_entity(internalName);
}

void mb_object::add_transform(std::string internal, Transform transform)
{
  m_game_world.get_transform(m_internals[internal]).position = transform.position;
  m_game_world.get_transform(m_internals[internal]).scale = transform.scale;
}

void mb_object::add_sprite(std::string internal, Sprite &sprite)
{
  m_game_world.get_sprite(m_internals[internal]).color = sprite.color;
  m_game_world.get_sprite(m_internals[internal]).texture = sprite.texture;
}

void mb_object::update()
{
  
}

mb_object::~mb_object()
{
}
