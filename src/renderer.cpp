#include "renderer.h"
#include "element_buffer_object.h"
#include "program.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array_object.h"
#include "vertex_buffer_object.h"

#include "open_gl_calls.h"
#include <GLFW/glfw3.h>

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::setup() {
  {
    Shader vertex("res/shaders/vertex.vert", SHADER_TYPE_VERTEX);
    Shader fragment("res/shaders/fragment.frag", SHADER_TYPE_FRAGMENT);

    program.attachShader(vertex.getId());
    program.attachShader(fragment.getId());

    program.linkShaders();
  }

  VAO vao;
  vao.bind();

  float vertices[] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,//
      0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,//
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,//
  };

  VBO vbo(vertices, sizeof(vertices));
  vbo.bind();

  unsigned int indices[] = {0, 1, 2, 0, 2, 3};
  EBO ebo(indices, sizeof(indices));
  ebo.bind();
  
  Texture text("res/textures/mortis.png", PNG);
  Texture text2("res/textures/awesomeface.png", PNG);
  text.activate(0);
  text2.activate(1);


  glCall(vao.enable(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0));
  glCall(vao.enable(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                    3 * sizeof(float)));
  glCall(vao.enable(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                    6 * sizeof(float)));
  program.useProgram();
  program.set1Int("texture1", 0);
  program.set1Int("texture2", 1);
}

void Renderer::render() {
  glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}
