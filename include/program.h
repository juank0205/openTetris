#pragma once

class Program {
public:
  Program();
  ~Program();

  void useProgram();
  void attachShader(unsigned int shaderId);
  void linkShaders();
private:
  unsigned int id;

  void getLinkInfo();
};
