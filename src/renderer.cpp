#include "renderer.h"
#include "program.h"
#include "shader.h"
#include "vertex_array_object.h"
#include "vertex_buffer_object.h"

#include <glad/glad.h>

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

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  VBO vbo(vertices, 9);
  vbo.bind();

  vao.enable(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  program.useProgram();
}

void Renderer::render() { glDrawArrays(GL_TRIANGLES, 0, 3); }
