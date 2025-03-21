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

  void set1Int(const char *name, int value);
private:
  unsigned int id;

  void getLinkInfo();
};
