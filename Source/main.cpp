#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Utils Includes
#include "utils/mb_utils.h"
#include <string>
#include "graphics/mb_shader.h"
#include "graphics/mb_renderer.h"
#include "logic/snake.h"
#include <random>

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
  #endif
  GLFWwindow* window =glfwCreateWindow(800 , 600 , "Snake Game" ,NULL , NULL);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  gladLoadGL();
  Shader shader;
  shader.add_shader("../Assets/Shaders/basic.vs.glsl" , GL_VERTEX_SHADER);
  shader.add_shader("../Assets/Shaders/basic.fs.glsl" , GL_FRAGMENT_SHADER);
  shader.link_program();
  std::random_device rd;              // Random seed
  std::mt19937 gen(rd());             // Mersenne Twister engine
  std::uniform_real_distribution<> dist(-1.0f, 1.0f);
  Renderer renderer(window);
  renderer.pass_shader(shader, "main");
  // ? Asset loading

  Texture2D apple_("/Users/mehdi/Documents/GitHub/Snake-Game/Assets/Textures/apple.png");

  LOG("OpenGL Version: ", glGetString(GL_VERSION), '\n');
  LOG("GLSL Version: ", glGetString(GL_SHADING_LANGUAGE_VERSION), '\n');
  GameWorld world;
  world.attach_renderer(renderer);
  world.attach_window(window);

  mb_snake snake(world);

  mb_object apple(world);
  apple.add_internal("apple");
  apple.add_transform("apple" , {glm::vec2(dist(gen),dist(gen)) , 0.0f,glm::vec2(0.2f,0.2f)});
  Sprite sprite_apple;
  sprite_apple.texture = &apple_;
  apple.add_sprite("apple",sprite_apple);

  while(!glfwWindowShouldClose(window))
  {
    renderer.select_shader(shader);
    snake.move();
    world.update(0.1666f);
    world.render();
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  glfwTerminate();
}