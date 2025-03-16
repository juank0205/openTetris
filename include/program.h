#pragma once

class Program {
public:
  Program();
  ~Program();

  void useProgram();
  void attachShader(unsigned int shaderId);
  void linkShaders();

  inline unsigned int getId() const {
    return id;
  }
private:
  unsigned int id;

  void getLinkInfo();
};
