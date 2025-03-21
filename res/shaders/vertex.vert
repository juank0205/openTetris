#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec3 myColor;
out vec2 texCoord;
void main() {
  gl_Position = vec4(aPos, 1.0f);
  myColor = aCol;
  texCoord = aTexCoord;
}
