#include "shader.h"
#include "logger.h"

#include <array>
#include <csignal>
#include <cstdint>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace {

enum class ShaderConstants : std::uint16_t {
  logBufferSize = 1024,
  undefinedGeometryShader = 0
};

struct ShaderIds {
  unsigned int vertex;
  unsigned int fragment;
  unsigned int geometry;
};

void check_compile_errors(unsigned int object, const std::string &type);
unsigned int compile_shader(const char *source, unsigned int &type);
unsigned int create_program(const ShaderIds &shaderIds);

inline void debugBreak() {
#ifdef _MSC_VER
  __debugbreak();
#elif defined(__GNUC__) || defined(__clang__)
  raise(SIGTRAP);
#else
  std::abort(); // fallback
#endif
}

void check_compile_errors(unsigned int object, const std::string &type) {
  int success;
  std::array<char, static_cast<int>(ShaderConstants::logBufferSize)> infoLog;
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
      glGetShaderInfoLog(object,
                         static_cast<int>(ShaderConstants::logBufferSize),
                         nullptr, infoLog.data());
      LOG_ERROR("| ERROR::SHADER: Compile-time error: Type: {}\n{}\n -- "
                "--------------------------------------------------- --",
                type, infoLog.data());
      debugBreak();
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
      glGetProgramInfoLog(object,
                          static_cast<int>(ShaderConstants::logBufferSize),
                          nullptr, infoLog.data());

      LOG_ERROR("| ERROR::SHADER: Link-time error: Type: {}\n{}\n -- "
                "--------------------------------------------------- --",
                type, infoLog.data());
      debugBreak();
    }
  }
}

unsigned int compile_shader(const char *source, unsigned int type) {
  const unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, nullptr);
  glCompileShader(id);

  std::string shaderTypeName;

  switch (type) {
  case GL_VERTEX_SHADER:
    shaderTypeName = "VERTEX";
    break;
  case GL_FRAGMENT_SHADER:
    shaderTypeName = "FRAGMENT";
    break;
  case GL_GEOMETRY_SHADER:
    shaderTypeName = "GEOMETRY";
    break;
  default:
    shaderTypeName = "UNKNOWN";
    break;
  }
  check_compile_errors(id, shaderTypeName);
  return id;
}

unsigned int create_program(const ShaderIds &shaderIds) {
  const unsigned int id = glCreateProgram();
  glAttachShader(id, shaderIds.vertex);
  glAttachShader(id, shaderIds.fragment);
  if (shaderIds.geometry !=
      static_cast<int>(ShaderConstants::undefinedGeometryShader)) {
    glAttachShader(id, shaderIds.geometry);
  }
  glLinkProgram(id);
  check_compile_errors(id, "PROGRAM");
  glDeleteShader(shaderIds.vertex);
  glDeleteShader(shaderIds.fragment);
  if (shaderIds.geometry !=
      static_cast<int>(ShaderConstants::undefinedGeometryShader)) {
    glDeleteShader(shaderIds.geometry);
  }
  return id;
}

} // namespace

void use_shader_program(const ShaderProgram &program) {
  glUseProgram(program.ID);
}

void unbind_shader_program() { glUseProgram(0); }

ShaderProgram compile_shaders(const ShaderSources &sources) {
  unsigned int sVertex;
  unsigned int sFragment;
  unsigned int sGeometry;
  sVertex = compile_shader(sources.vertex, GL_VERTEX_SHADER);
  sFragment = compile_shader(sources.fragment, GL_FRAGMENT_SHADER);

  ShaderProgram program;
  if (sources.geometry != nullptr) {
    sGeometry = compile_shader(sources.geometry, GL_GEOMETRY_SHADER);
    program.ID = create_program(
        {.vertex = sVertex, .fragment = sFragment, .geometry = sGeometry});
  } else {
    program.ID = create_program(
        {.vertex = sVertex, .fragment = sFragment, .geometry = 0});
  }
  return program;
}

void shader_program_set_integer(const ShaderProgram &program, const char *name,
                                int value, bool useShader) {
  if (useShader) {
    use_shader_program(program);
  }
  glUniform1i(glGetUniformLocation(program.ID, name), value);
}

void shader_program_set_vector2f(const ShaderProgram &program, const char *name,
                                 float x, float y, bool useShader) {
  if (useShader) {
    use_shader_program(program);
  }
  glUniform2f(glGetUniformLocation(program.ID, name), x, y);
}

void shader_program_set_vector2f(const ShaderProgram &program, const char *name,
                                 const glm::vec2 &value, bool useShader) {
  if (useShader) {
    use_shader_program(program);
  }
  glUniform2f(glGetUniformLocation(program.ID, name), value.x, value.y);
}

void shader_program_set_vector3f(const ShaderProgram &program, const char *name,
                                 const glm::vec3 &value, bool useShader) {
  if (useShader) {
    use_shader_program(program);
  }
  glUniform3f(glGetUniformLocation(program.ID, name), value.x, value.y,
              value.z);
}

void shader_program_set_vector3f(const ShaderProgram &program, const char *name,
                                 float x, float y, float z, bool useShader) {
  if (useShader) {
    use_shader_program(program);
  }
  glUniform3f(glGetUniformLocation(program.ID, name), x, y, z);
}

void shader_program_set_matrix4(const ShaderProgram &program, const char *name,
                                const glm::mat4 &value, bool useShader) {
  if (useShader) {
    use_shader_program(program);
  }
  glUniformMatrix4fv(glGetUniformLocation(program.ID, name), 1, GL_FALSE,
                     glm::value_ptr(value));
}
