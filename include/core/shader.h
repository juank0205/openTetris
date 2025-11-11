#pragma once

#include <glm/glm.hpp>
#include <string>

class ShaderProgram {
public:
  unsigned int ID;
  ShaderProgram() {}
  ShaderProgram &Use();
  void Compile(const char *vertexSource, const char *fragmentSource,
               const char *geometrySource = nullptr);
  // Set uniform methods
  void SetInteger(const char *name, int value, bool useShader = false);

  void SetVector2f(const char *name, float x, float y, bool useShader = false);
  void SetVector2f(const char *name, const glm::vec2 &value,
                   bool useShader = false);

  void SetVector3f(const char *name, float x, float y, float z, bool useShader = false);
  void SetVector3f(const char *name, const glm::vec3 &value, bool useShader = false);

  void SetMatrix4f(const char *name, const glm::mat4 &value,
                   bool useShader = false);

private:
  void checkCompileErrors(unsigned int object, std::string type);
  unsigned int compileShader(const char *source, unsigned int type);
  void createProgram(unsigned int vertexShader, unsigned int fragmentShader,
                     unsigned int geometryShader);
  void createProgram(unsigned int vertexShader, unsigned int fragmentShader);
};
