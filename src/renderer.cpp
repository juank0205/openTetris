#include "renderer.h"
#include "element_buffer_object.h"
#include "program.h"
#include "shader.h"
#include "vertex_array_object.h"
#include "vertex_buffer_object.h"

#include "open_gl_calls.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::setup() {
  Program program;
  {
    Shader vertex("res/shaders/vertex.vert", SHADER_TYPE_VERTEX);
    Shader fragment("res/shaders/fragment.frag", SHADER_TYPE_FRAGMENT);

    program.attachShader(vertex.getId());
    program.attachShader(fragment.getId());

    program.linkShaders();
  }

  VAO vao;
  vao.bind();

  float vertices[] = {-0.5f, -0.5f, 0.0f, -0.5f, 0.5f,  0.0f,
                      0.5f,  0.5f,  0.0f, 0.5f,  -0.5f, 0.0f};
  VBO vbo(vertices, sizeof(vertices));
  vbo.bind();

  unsigned int indices[] = {0, 1, 2, 0, 2, 3};
  EBO ebo(indices, sizeof(indices));
  ebo.bind();

  glCall(vao.enable(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
  program.useProgram();
}

void Renderer::render() { glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)); }
