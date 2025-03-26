#include "scene_manager.h"
#include "open_gl_calls.h"
#include "program.h"
#include "shader.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::setupScene() {
  Program program;

  {
    Shader vertex("res/shaders/vertex.vert", SHADER_TYPE_VERTEX);
    Shader fragment("res/shaders/fragment.frag", SHADER_TYPE_FRAGMENT);

    program.attachShader(vertex.getId());
    program.attachShader(fragment.getId());

    program.linkShaders();
  }

  float vertices[] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //
      0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, //
  };

  unsigned int indices[] = {0, 1, 2, 0, 2, 3};

  m_gameObjects.emplace_back(vertices, sizeof(vertices), indices,
                             sizeof(indices), "res/textures/mortis.png", PNG,
                             program);
  m_gameObjects[0].vao.bind();

  Texture text2("res/textures/awesomeface.png", PNG);

  m_gameObjects[0].vbo.bind();
  m_gameObjects[0].ebo.bind();

  m_gameObjects[0].texture.activate(0);
  text2.activate(1);

  glCall(m_gameObjects[0].vao.enable(0, 3, GL_FLOAT, GL_FALSE,
                                     8 * sizeof(float), 0));
  glCall(m_gameObjects[0].vao.enable(1, 3, GL_FLOAT, GL_FALSE,
                                     8 * sizeof(float), 3 * sizeof(float)));
  glCall(m_gameObjects[0].vao.enable(2, 2, GL_FLOAT, GL_FALSE,
                                     8 * sizeof(float), 6 * sizeof(float)));
  program.useProgram();
  program.set1Int("texture1", 0);
  program.set1Int("texture2", 1);
}
