#pragma once

#include <glm/glm.hpp>

struct ShaderProgram {
  unsigned int ID;
};

struct ShaderSources {
  const char *vertex;
  const char *fragment;
  const char *geometry = nullptr; // optional
};

void use_shader_program(const ShaderProgram &program);
void unbind_shader_program();
ShaderProgram compile_shaders(const ShaderSources &sources);

void shader_program_set_integer(const ShaderProgram &program, const char *name, int value,
                                bool useShader = false);

void shader_program_set_vector2f(const ShaderProgram &program, const char *name, float x, float y,
                                 bool useShader = false);
void shader_program_set_vector2f(const ShaderProgram &program, const char *name, const glm::vec2 &value,
                                 bool useShader = false);

void shader_program_set_vector3f(const ShaderProgram &program, const char *name, float x, float y, float z,
                                 bool useShader = false);
void shader_program_set_vector3f(const ShaderProgram &program, const char *name, const glm::vec3 &value,
                                 bool useShader = false);

void shader_program_set_matrix4(const ShaderProgram &program, const char *name, const glm::mat4 &value,
                 bool useShader = false);

