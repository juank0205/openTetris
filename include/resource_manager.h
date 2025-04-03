#pragma once

#include "program.h"

#include <string>
#include <unordered_map>
#include <vector>

class ResourceManager {
public:
  ResourceManager();
  ~ResourceManager();

  inline float *getVerticesData(const char *name) {
    return m_vertices.at(name).data();
  }
  inline size_t getVerticesSize(const char *name) {
    return m_vertices.at(name).size();
  }
  inline Program &getProgram(const char *name) { return m_programs.at(name); }
  inline std::unordered_map<std::string, Program> &getPrograms() {
    return m_programs;
  }

private:
  std::unordered_map<std::string, Program> m_programs;
  std::unordered_map<std::string, std::vector<float>> m_vertices;

  void createProgram(const char *vertexFile, const char *fragmentFile,
                     const char *name);
  void loadShaders();
  void loadVertices();
};
