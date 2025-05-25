#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Utils Includes
#include "utils/mb_utils.h"
#include <string>
#include "graphics/mb_shader.h"
#include "graphics/mb_renderer.h"
#include <glm/gtc/matrix_transform.hpp>


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
  gladLoadGL();
  Shader shader;
  shader.add_shader("../Assets/Shaders/basic.vs.glsl" , GL_VERTEX_SHADER);
  shader.add_shader("../Assets/Shaders/basic.fs.glsl" , GL_FRAGMENT_SHADER);
  shader.link_program();

  Renderer renderer(window);
  renderer.pass_shader(shader, "main");

  LOG("OpenGL Version: ", glGetString(GL_VERSION), '\n');
  LOG("GLSL Version: ", glGetString(GL_SHADING_LANGUAGE_VERSION), '\n');
  // Try VAOs
  unsigned int VAO ,VBO;
  glGenVertexArrays(1,&VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glm::mat4 proj = glm::mat4(1.0f);
  float square[] = {
    -0.50f , -.50f,
      .50f , -.50f,
      .50f ,  .50f,

    - .50f , -.50f,
      .50f ,  .50f,
     -.50f ,  .50f,
  };
  glBindBuffer(GL_ARRAY_BUFFER , VBO);
  glBufferData(GL_ARRAY_BUFFER , 6*2*2 *sizeof(float) ,square,GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  proj = glm::ortho(-200.0f , 200.0f , -100.0f ,100.0f);
  shader.use();
  shader.add_mat4("projection" , proj);
  glBindVertexArray(0);
  while(!glfwWindowShouldClose(window))
  {
    renderer.begin_frame();
    proj = glm::ortho(-200.0f , 200.0f , -100.0f ,100.0f);
    renderer.draw_quad(glm::vec2(0.0f,0.0f), glm::vec2(0.5f,0.5f) , glm::vec4(1.0f,1.0f,1.0f,1.0f));
    renderer.draw_quad(glm::vec2(-.50f,0.0f), glm::vec2(0.5f,0.5f) , glm::vec4(1.0f,1.0f,1.0f,1.0f));
    renderer.set_projection(proj);
    renderer.select_shader(shader);
    glfwPollEvents();
    if(glfwGetKey(window,GLFW_KEY_O)==GLFW_PRESS)
    {
      std::string FileOpened = mb_OpenFileDialog();
      LOG(FileOpened , '\n');
      std::string Balls;
      ReadFile(FileOpened ,Balls);
    }
    renderer.end_frame();
    glfwSwapBuffers(window);
  }
  glfwTerminate();
}