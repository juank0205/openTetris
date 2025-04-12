#include "resource_manager.h"
#include "shader.h"

ResourceManager::ResourceManager() {
  loadVertices();
  loadShaders();
}

ResourceManager::~ResourceManager() {}

void ResourceManager::createProgram(const char *vertexFile,
                                    const char *fragmentFile,
                                    const char *name) {
  Shader vertexShader(vertexFile, SHADER_TYPE_VERTEX);
  Shader fragmentShader(fragmentFile, SHADER_TYPE_FRAGMENT);

  Program &program = m_programs[name];

  program.attachShader(vertexShader.getId());
  program.attachShader(fragmentShader.getId());
  program.linkShaders();
}

void ResourceManager::loadShaders() {
  createProgram("res/shaders/vertex.vert", "res/shaders/fragment.frag", "cubo");
  createProgram("res/shaders/vertex.vert", "res/shaders/lightingFragment.frag",
                "lighting");
}

void ResourceManager::loadVertices() {
  m_vertices["cubo"] = {-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //
                      0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //
                      0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
                      0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
                      -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
                      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //

                      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f, //
                      0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f, //
                      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //
                      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //
                      -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //
                      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f, //

                      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f, //
                      -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f, //
                      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, //
                      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, //
                      -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f, //
                      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f, //

                      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //
                      0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f, //
                      0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, //
                      0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, //
                      0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f, //
                      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //

                      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //
                      0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //
                      0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
                      0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
                      -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
                      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //

                      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f, //
                      0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f, //
                      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
                      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
                      -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
                      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};
}
