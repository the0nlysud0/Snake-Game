#include "mb_object.h"

struct Segment
{
  std::string name;
  glm::vec2 position;
};

class mb_snake: mb_object
{
private:
  Texture2D* snake_head = new Texture2D("/Users/mehdi/Documents/GitHub/Snake-Game/Assets/Textures/better-snake-head.png");
  Texture2D* snake_body = new Texture2D("/Users/mehdi/Documents/GitHub/Snake-Game/Assets/Textures/snake-body.png");
  Texture2D* snake_tail = new Texture2D("/Users/mehdi/Documents/GitHub/Snake-Game/Assets/Textures/snake-tail.png");
  GLFWwindow* m_window;
  std::vector<glm::vec2> m_past_positions;
  int counter=0;

  std::deque<glm::vec2> m_position_history;
  std::vector<Segment> m_body;

  float m_stepTimer = 0.0f;
  float m_stepDelay = 0.2f; 
  bool m_wasAnyPressed=false;
  glm::vec2 m_direction = {0.0f , -1.0f};
  float m_rotation =270.0f;
  glm::vec2 m_position = {0.34f, 0.6f};
  glm::vec2 m_scale = {0.1f,0.1f};
  float m_velocity = 0.03f;
  float m_acceleration = 0.001f;
public:
  mb_snake(GameWorld& world);
  void move();
  void handle_input(int key, int scancode, int action, int mods);
  ~mb_snake();
private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};