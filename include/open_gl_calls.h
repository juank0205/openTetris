#pragma once

#include <glad/glad.h>


#ifdef DEBUG
#define glCall(x)                                                              \
  do {                                                                         \
    x;                                                                         \
    glCheckError(__FILE__, __LINE__);                                         \
  } while (0)
void glCheckError(const char *file, int line);
#else
#define glCall(x) x
#endif // DEBUG
