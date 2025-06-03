#include "snake.h"
#include "../utils/mb_utils.h"
mb_snake::mb_snake(GameWorld& world) : mb_object(world)
{
    

    // Head init
    add_internal("head");
    add_transform("head", {m_position, m_rotation, m_scale});
    Sprite sprite_snake_head;
    sprite_snake_head.color = {0.0f,0.0f,0.0f};
    sprite_snake_head.texture = snake_head;
    add_sprite("head", sprite_snake_head);

    // Tail init
    add_internal("tail");
    Sprite sprite_snake_tail;
    sprite_snake_tail.texture = snake_tail;
    // sprite_snake_tail.color = {0.3f, 0.4f, 0.7f};
    add_sprite("tail", sprite_snake_tail);

    add_internal("body0");
    Sprite sprite_snake_body;
    sprite_snake_body.texture = snake_body;
    add_sprite("body0", sprite_snake_body);

    // Head goes at front of history
    m_position_history.push_front(m_position);

    m_window = world.get_window();
    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, key_callback);
}
void mb_snake::move()
{
  LOG("Instance address: %p\n", this);

    m_stepTimer += 0.016f; // simulate ~60FPS

    if (m_stepTimer >= m_stepDelay)
    {
        m_stepTimer = 0.0f;

        // Move head
        m_position += m_direction * m_scale;
        add_transform("head", {m_position, m_rotation, m_scale});
        // LOG(m_rotation);
        // Save current head position
        m_position_history.push_front(m_position);

        // Max segments count (excluding head)
        constexpr int segment_count = 4;

        // Ensure we don’t overflow
        while (m_position_history.size() > segment_count + 1)
            m_position_history.pop_back();

        // Ensure body entities exist (body0, body1, ...)
        for (int i = 0; i < segment_count; ++i)
        {
            std::string name = "body" + std::to_string(i);

            add_internal(name);
            Sprite sprite;
            sprite.texture = snake_body;
            add_sprite(name, sprite);

            // Make sure we have enough history to place it
            if (i + 1 < m_position_history.size())
            {
                add_transform(name, {m_position_history[i + 1], m_rotation, m_scale});
            }
        }
    }
}




void mb_snake::handle_input(int key, int scancode, int action, int mods)
{
  LOG("Instance address: %p\n", this);

  glm::vec2 old_direction = m_direction;
  if(!m_wasAnyPressed) m_wasAnyPressed=true;
  if(action==GLFW_PRESS)
  {
    if(key == GLFW_KEY_W && old_direction.y != -1.0f)
    {
      m_direction = glm::vec2(0.0f, 1.0f);
      m_rotation = 90.0f;
    }
    else if(key == GLFW_KEY_S && old_direction.y != 1.0f)
    {
      m_direction = glm::vec2(0.0f, -1.0f);
      m_rotation = 270.0f;
    }
    else if(key == GLFW_KEY_D && old_direction.x != -1.0f)
    {
      m_direction = glm::vec2(1.0f, 0.0f);
      m_rotation = 0.0f;
    }
    else if(key == GLFW_KEY_A && old_direction.x != 1.0f)
    {
      m_direction = glm::vec2(-1.0f, 0.0f);
      m_rotation = 180.0f;
    }
  }
  LOG("ANGLE(input): ", m_rotation,'\n');
}

mb_snake::~mb_snake()
{
}

void mb_snake::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  mb_snake* instance = static_cast<mb_snake*>(glfwGetWindowUserPointer(window));
  if(instance)
  {
    instance->handle_input(key,scancode ,action , mods);
  }
}
